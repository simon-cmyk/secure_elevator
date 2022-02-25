#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "stdbool.h"

typedef struct{
    struct timeval start_time;
    int end_time;
} timer_st;

void timer_restart(timer_st* timer_obj, int new_end_time);

// [delete] hvordan få til å bli konst? 
bool timer_done_counting(timer_st timer_obj);