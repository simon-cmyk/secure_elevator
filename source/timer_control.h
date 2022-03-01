#pragma once
#include <time.h>

#define TIMER_SECONDS_BEFORE_DONE 3
#define TRUE 1
#define FALSE 0

typedef struct{
    time_t start_time;
    int is_currently_in_use;
} timer_st;

void timer_restart(timer_st* timer_obj);

// [delete] hvordan få til å bli konst? 
int timer_done_counting(timer_st timer_obj);