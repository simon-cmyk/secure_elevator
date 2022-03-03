#pragma once
#include <time.h>
#include "elevator_constants.h"

typedef struct{
    time_t start_time;
    int is_currently_in_use;
} timer_st;

void timer_restart(timer_st* timer_obj);
int timer_done_counting(timer_st timer_obj);