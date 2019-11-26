#include <iostream>
#include <stdio.h>
#include <zconf.h>
#include "preyfinder.h"
#include <gcomm.h>

using namespace std;
using namespace gcomm;

struct data {
    int16_t v[3];
};

int main(int argc, char *argv[])
{
    GUartBuffers serial(GUart::Baudrate::b57600);
    GBufferConnector conn(serial.rx_buffer, serial.tx_buffer);
    GComm<data,data> comm(conn);
    Prey_finder pf;
    double angle,size;
    bool active = true;
    data d;
    while(active) {
        double age = pf.get_prey(angle, size);
        if (age<3){
            if (size>6000) {
                d.v[0] = 2; // caught
                d.v[1] = 0;
            } else {
                d.v[0] = 1; //found
                d.v[1] = 0;
                d.v[2] = angle;
            }
        } else {
            d.v[0] = 0; // lost contact
            d.v[1] = 0;
            d.v[2] = 0;
        }
        for (int i=0;i<3;i++)
            cout << (int) d.v[i] << " ";
        cout << endl;
        comm.write_object(d);
        usleep(1000000);
    }
}