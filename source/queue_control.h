#pragma once
#include "driver/elevio.h"
#include "elevator_control.h"
#define TRUE 1
#define FALSE 0
#define NO_ORDER 0
#define NO_ACTIVE_ORDERS -1


typedef struct 
{
    int orders_from_inside_cab[N_FLOORS]; 
    int orders_up_from_hall[N_FLOORS];
    int orders_down_from_hall[N_FLOORS];
    int number_of_active_orders;
} queue_object_st;


void queue_object_prioritize(queue_object_st *queue_obj, int order_priority_arr_index);
void queue_object_new_order_bottom_priority(queue_object_st *queue_obj, int order_priority_arr_index);
void queue_object_place_order(queue_object_st *queue_object, int floor, ButtonType button_type);
void queue_object_remove_order(queue_object_st *queue_object, int floor,  ButtonType button_type, int priority);
void queue_object_add_order(int button, int floor);
int queue_control_get_order();
void queue_control_order_done(int current_floor);
void decrement_priorities(queue_object_st *queue_object, int priority_threshold);
int queue_control_stop_on_way_up(int current_floor, int destination_floor);
int queue_control_stop_on_way_down(int current_floor, int destination_floor);


