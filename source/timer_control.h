#pragma once
#include <time.h>
#include "elevator_constants.h"

typedef struct{
    time_t start_time;
    int is_active;
} timer_object_st;

void timer_object_restart(timer_object_st* p_timer_obj);
int timer_object_is_done_counting(timer_object_st* p_timer_obj);
void timer_object_set_is_active(timer_object_st* p_timer_obj, int active);
int timer_control_is_done_counting();
int timer_control_is_active();
void timer_control_set_is_active(int active);
void timer_control_restart();