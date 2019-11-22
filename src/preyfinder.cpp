//
// Created by german on 11/22/19.
//

#include "preyfinder.h"

Prey_finder::Prey_finder() {
    gettimeofday( &_last_detection , NULL);
    _pixy.init();
    _update_thread = std::thread(_update_, std::ref(*this));
    _active = true;
}

double Prey_finder::get_prey(int &a) {
    a = angle;
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
            pf.angle = ((double)pf._pixy.ccc.blocks[0].m_x) / 320 * 60 - 30;
            gettimeofday( &pf._last_detection , NULL);
        }
    }
}

Prey_finder::~Prey_finder() {
    _active = false;
    _update_thread.join();
}
