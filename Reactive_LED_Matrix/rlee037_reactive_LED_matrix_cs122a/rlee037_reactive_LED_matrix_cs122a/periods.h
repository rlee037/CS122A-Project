#ifndef _PERIODS_H_
#define _PERIODS_H_

#include "scheduler.h"

#define GLOBAL_PERIOD     50  //ms
#define SENSOR_PERIOD     100 //ms
#define COORDINATE_PERIOD 100 //ms
#define LED8x8_PERIOD     100 //ms

#define NUM_TASKS 3

task tasks[NUM_TASKS];

#endif