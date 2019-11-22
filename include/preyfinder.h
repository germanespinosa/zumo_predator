//
// Created by german on 11/22/19.
//

#ifndef PREY_PREYFINDER_H
#define PREY_PREYFINDER_H
#include <libpixyusb2.h>
#include <thread>
#include <stdio.h>
#include <sys/time.h>

struct Prey_finder {
    Prey_finder();
    ~Prey_finder();
    double get_prey(double &);
    double angle;
private:
    Pixy2  _pixy;
    std::thread _update_thread;
    static void _update_(Prey_finder &);
    struct timeval _last_detection;
    bool _active;
};


#endif //PREY_PREYFINDER_H
