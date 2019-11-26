//
// Created by german on 11/22/19.
//

#include "preyfinder.h"
#include <iostream>
#include <zconf.h>

using namespace std;

Prey_finder::Prey_finder() {
    gettimeofday( &_last_detection , NULL);
    _pixy.init();
    _update_thread = std::thread(_update_, std::ref(*this));
    _active = true;
}

double Prey_finder::get_prey(double &a, double &d) {
    a = angle;
    d = size;
    struct timeval prev = _last_detection;
    struct timeval now;
    gettimeofday( &now , NULL);
    double x_ms , y_ms , diff;
    x_ms = (double)prev.tv_sec*1000000 + (double)prev.tv_usec;
    y_ms = (double)now.tv_sec*1000000 + (double)now.tv_usec;

    diff = (double)y_ms - (double)x_ms;
    return diff/1000000;
}

void Prey_finder::_update_(Prey_finder &pf) {
    while (pf._active)
    {
        pf._pixy.ccc.getBlocks();
        if (pf._pixy.ccc.numBlocks){
            int f = -1;
            for (int i=0; i < pf._pixy.ccc.numBlocks; i++) {
                if (pf._pixy.ccc.blocks[i].m_signature==1){
                    for (int j=0; j < pf._pixy.ccc.numBlocks; j++) {
                        if (pf._pixy.ccc.blocks[j].m_signature==2){
                            if (pf._pixy.ccc.blocks[j].m_y > pf._pixy.ccc.blocks[i].m_y){
                                if (pf._pixy.ccc.blocks[j].m_x > pf._pixy.ccc.blocks[i].m_x - pf._pixy.ccc.blocks[i].m_width) {
                                    if (pf._pixy.ccc.blocks[j].m_x <
                                        pf._pixy.ccc.blocks[i].m_x + pf._pixy.ccc.blocks[i].m_width) {
                                        f = i;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (f>=0) {
                pf.angle = ((double) pf._pixy.ccc.blocks[f].m_x) / 320.0 * 60.0 - 30.0;
                double new_size = pf._pixy.ccc.blocks[f].m_height * pf._pixy.ccc.blocks[f].m_width;
                pf.size = (pf.size * .9) + (new_size * .1);
                gettimeofday(&pf._last_detection, NULL);
                //pf._pixy.ccc.blocks[f].print();
            }
        }
    }
}

Prey_finder::~Prey_finder() {
    _active = false;
    _update_thread.join();
}
