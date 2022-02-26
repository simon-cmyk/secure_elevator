#include "queue_control.h"
#include <stdio.h>

queue_object_st queue_list = {{0}, {0}, {0}, 0};


void queue_object_add_order(int floor, int button){
    queue_object_place_order(&queue_list, floor, button);
}


void queue_object_place_order(queue_object_st *queue_object, int floor,  ButtonType button_type){
    printf("Button %d, floor %d \n", (int) button_type, floor);
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
                printf("Active_orders %d \n", queue_object->number_of_active_orders);
                printf("Active_orders %d \n", queue_object->orders_from_inside_cab[floor]);
                queue_object->orders_from_inside_cab[floor] = queue_object->number_of_active_orders;
            } break;
    }
}

void queue_object_remove_order(queue_object_st *queue_object, int floor,  ButtonType button_type){
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
}

int queue_control_get_next_order(){
    for (int i = 0; i < N_FLOORS; i++)
    {
        if(queue_list.orders_from_inside_cab[i] == 1 || queue_list.orders_up_from_hall[i] == 1 || queue_list.orders_down_from_hall[i]  == 1){
            return i;
        }
    }
    return NO_ACTIVE_ORDERS;
}

void queue_control_order_done(int current_floor){
    if(queue_list.orders_up_from_hall[current_floor] != NO_ORDER){
        queue_object_remove_order(&queue_list, current_floor, BUTTON_HALL_UP);
    }
    if(queue_list.orders_down_from_hall[current_floor] != NO_ORDER){
        queue_object_remove_order(&queue_list, current_floor, BUTTON_HALL_DOWN);
    }
    if(queue_list.orders_from_inside_cab[current_floor] != NO_ORDER){
        queue_object_remove_order(&queue_list, current_floor, BUTTON_CAB);
    }
}