#include <iostream>
#include <stdio.h>
#include <zconf.h>
#include "preyfinder.h"
#include <gcomm.h>

using namespace std;
using namespace gcomm;

struct data {
    int16_t state, speed, angle;
};

int main(int argc, char *argv[])
{
    //GUartBuffers serial(GUart::Baudrate::b57600);
    //GBufferConnector conn(serial.rx_buffer, serial.tx_buffer);
    Prey_finder pf;
    double angle,size;
    bool active = true;
    while(active) {
        data d {0,0,0};
        double age = pf.get_prey(angle, size);
        if (age<3){
            if (size>6000) {
                d.state = 2; // caught
                d.speed = 0;
                d.angle = 0;
            } else {
                d.state = 1; //found
                d.speed = 120;
                d.angle = angle * 3;
            }
        } else {
            d.state = 0; // lost contact
            d.speed = 0;
            d.angle = angle >= 0? 100 : -100;
        }
        cout << d.state << " " << d.speed << " " << d.angle << " ";
        cout << endl;
        //conn.write_buffer(&d, sizeof(data));
        usleep(100000);
    }
}