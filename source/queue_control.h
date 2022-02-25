#pragma once
#include "elevator_control.h"
#include "driver/elevio.h"
#define TRUE 1
#define FALSE 0

typedef struct 
{
    int orders_from_inside_cab[N_FLOORS]; 
    int orders_up_from_hall[N_FLOORS];
    int orders_down_from_hall[N_FLOORS];
    int order_priority[3*N_FLOORS];
    int number_of_active_orders;
} queue_object_st;


void queue_object_prioritize(queue_object_st *queue_obj, int order_priority_arr_index);
void queue_object_new_order_bottom_priority(queue_object_st *queue_obj, int order_priority_arr_index);
void queue_object_place_order(queue_object_st *queue_object, ButtonType button_type, int floor);
void queue_object_add_order(int button, int floor);

