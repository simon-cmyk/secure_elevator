#pragma once
#include "stdbool.h"
#include "elevator_control.h"
#include "elevio.h"

typedef struct 
{
    bool orders_from_inside_elevator[N_FLOORS]; 
    bool orders_up_from_corridor[N_FLOORS-1];
    bool orders_down_from_corridor[N_FLOORS-1];
    int priority[3*N_FLOORS -2]
} queue_object_st;

void set_up_queue_arrays();

// [innenfra/utenfra, opp/ned, etasje, ]