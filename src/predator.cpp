#include <iostream>
#include <stdio.h>
#include <zconf.h>
#include "preyfinder.h"

using namespace std;

int main(int argc, char *argv[])
{
  //gcomm::GMemConnector m(200, gcomm::GMemConnector::mode::master);
  //gcomm::GComm<int,int> c (m);
  Prey_finder pf;
  double angle;

  while (pf.get_prey(angle)<3) {
      cout<< "Angle: " << angle  << endl;
      usleep(300000);
  }
}