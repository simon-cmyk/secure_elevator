#pragma once
#include "stdbool.h"
#include "elevator_control.h"
#include "driver/elevio.h"

typedef struct 
{
    bool orders_from_inside_elevator[N_FLOORS]; 
    bool orders_up_from_corridor[N_FLOORS];
    bool orders_down_from_corridor[N_FLOORS];
    int priority[3*N_FLOORS]
} queue_object_st;

void set_up_queue_arrays();

