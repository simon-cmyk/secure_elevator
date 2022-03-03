#include "queue_control.h"
#include <stdio.h>
#include "elevator_constants.h"

queue_object_st queue_list = {{NO_ORDER}, {NO_ORDER}, {NO_ORDER}, 0};


void queue_object_add_order(int floor, int button){
    queue_control_place_order_in_queue_object(&queue_list, floor, button);
}

void queue_control_place_order(int floor,  ButtonType button_type){
    queue_control_place_order_in_queue_object(&queue_list, floor, button_type);
}


void queue_control_place_order_in_queue_object(queue_object_st *queue_object, int floor,  ButtonType button_type){
    switch (button_type){
        case BUTTON_HALL_UP: 
            if(queue_object->orders_up_from_hall[floor] == NO_ORDER) {
                queue_object->number_of_active_orders += 1;
                queue_object->orders_up_from_hall[floor] = queue_object->number_of_active_orders;
                
            } break;  
        case BUTTON_HALL_DOWN:
            if(queue_object->orders_down_from_hall[floor] == NO_ORDER) {
                queue_object->number_of_active_orders += 1;
                queue_object->orders_down_from_hall[floor] = queue_object->number_of_active_orders;
            } break;  
        case BUTTON_CAB:
            if(queue_object->orders_from_inside_cab[floor] == NO_ORDER) {
                queue_object->number_of_active_orders += 1;
                queue_object->orders_from_inside_cab[floor] = queue_object->number_of_active_orders;
            } break;
    }
    array_handling_print(queue_object->orders_down_from_hall, N_FLOORS);
    array_handling_print(queue_object->orders_up_from_hall, N_FLOORS);
    array_handling_print(queue_object->orders_from_inside_cab, N_FLOORS);
}

void decrement_priorities(queue_object_st *queue_object, int priority_threshold) {
    int priority = priority_threshold; 
    while (1)
    {
        priority += 1;
        int priority_not_found = TRUE;
        for (int i = 0; i < N_FLOORS; i++)
        {
            if (queue_object->orders_down_from_hall[i] == priority)
            {
                queue_object->orders_down_from_hall[i] -= 1;
                priority_not_found = FALSE;
            } else if (queue_object->orders_up_from_hall[i] == priority){
                queue_object->orders_up_from_hall[i] -= 1;
                priority_not_found = FALSE;
            } else if (queue_object->orders_from_inside_cab[i] == priority){
                queue_object->orders_from_inside_cab[i] -= 1;
                priority_not_found = FALSE;
            }
        }
        if(priority_not_found == TRUE){
                break;
            }
    }
    
}

void queue_object_remove_order(queue_object_st *queue_object, int floor,  ButtonType button_type, int priority){
    switch (button_type){
        case BUTTON_HALL_UP:
            queue_object->orders_up_from_hall[floor] = NO_ORDER; 
            break;  
        case BUTTON_HALL_DOWN:
            queue_object->orders_down_from_hall[floor] = NO_ORDER; 
            break;  
        case BUTTON_CAB:
            queue_object->orders_from_inside_cab[floor] = NO_ORDER; 
            break;
    }
    queue_object->number_of_active_orders -= 1;
    decrement_priorities(queue_object ,priority);
}


int queue_control_get_next_order(){
    for (int i = 0; i < N_FLOORS; i++)
    {
        if(queue_list.orders_from_inside_cab[i] == 1 || queue_list.orders_up_from_hall[i] == 1 || queue_list.orders_down_from_hall[i]  == 1){
            printf("%d \n", i);
            return i;
        }
    }
    return NO_ACTIVE_ORDERS;
}

void queue_control_order_done(int current_floor){
    if(queue_list.orders_up_from_hall[current_floor] != NO_ORDER){
        queue_object_remove_order(&queue_list, current_floor, BUTTON_HALL_UP, queue_list.orders_up_from_hall[current_floor]);
    }
    if(queue_list.orders_down_from_hall[current_floor] != NO_ORDER){
        queue_object_remove_order(&queue_list, current_floor, BUTTON_HALL_DOWN, queue_list.orders_down_from_hall[current_floor]);
    }
    if(queue_list.orders_from_inside_cab[current_floor] != NO_ORDER){
        queue_object_remove_order(&queue_list, current_floor, BUTTON_CAB, queue_list.orders_from_inside_cab[current_floor]);
    }
}

int queue_control_stop_on_way_up(int current_floor, int destination_floor){
    for (int i = current_floor +1; i < destination_floor; i++)
    {
        if (queue_list.orders_up_from_hall[i] != NO_ORDER || queue_list.orders_from_inside_cab[i] != NO_ORDER)
        {
            return i;
        }
    }
    return destination_floor;
}

int queue_control_stop_on_way_down(int current_floor, int destination_floor){
    for (int i = current_floor -1; i > destination_floor; i--)
    {
        if (queue_list.orders_down_from_hall[i] != NO_ORDER || queue_list.orders_from_inside_cab[i] != NO_ORDER)
        {
            return i;
        }
    }
    return destination_floor;
}