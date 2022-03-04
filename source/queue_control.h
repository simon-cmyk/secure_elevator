#pragma once
#include "driver/elevio.h"
#include "elevator_control.h"
#include "elevator_constants.h"


typedef struct 
{
    int orders_from_inside_cab[N_FLOORS]; 
    int orders_up_from_hall[N_FLOORS];
    int orders_down_from_hall[N_FLOORS];
    int number_of_active_orders;
} queue_object_st;

// husk å endre til queue_control_place_order
void queue_object_place_order_in_queue(queue_object_st *p_queue_object, int floor, ButtonType button_type);
void queue_object_remove_order(queue_object_st *p_queue_object, int floor,  ButtonType button_type, int priority_threshold);
void queue_object_decrement_priorities(queue_object_st *p_queue_object, int priority_threshold);

void queue_control_place_order(int floor,  ButtonType button_type);
int queue_control_get_next_order();
void queue_control_remove_orders_from_floor(int floor);
int queue_control_update_next_destination_up(int current_floor, int destination_floor);
int queue_control_update_next_destination_down(int current_floor, int destination_floor);
