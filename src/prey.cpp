#include "prey.h"
#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <signal.h>
#include <libpixyusb2.h>
Pixy2  pixy;

static bool  run_flag = true;

void handle_SIGINT(int unused)
{
  // On CTRL+C - abort! //
  run_flag = false;
}

bool exists (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

int main(int argc, char *argv[])
{
  gcomm::GMemConnector m(200, gcomm::GMemConnector::mode::master);
  gcomm::GComm<int,int> c (m);
  signal (SIGINT, handle_SIGINT);

  printf ("Connecting to Pixy2...");
  {
    int Result = pixy.init();
    if (Result < 0){
      printf ("Error\n");
      printf ("pixy.init() returned %d\n", Result);
      return Result;
    }
    printf ("Success\n");
  }
  while (run_flag)
  {
    pixy.ccc.getBlocks();
    if (pixy.ccc.numBlocks){
      int angle = (pixy.ccc.blocks[0].m_x * 60 / 320);
      printf ("Angle: %d\n", angle);
    }
  }
}