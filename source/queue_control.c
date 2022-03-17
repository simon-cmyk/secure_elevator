#include "queue_control.h"

static queue_object_st m_queue_list = {{NO_ORDER}, {NO_ORDER}, {NO_ORDER}, 0};

void queue_control_place_order(int floor,  ButtonType button_type){
    queue_object_place_order_in_queue(&m_queue_list, floor, button_type);
}

void queue_object_place_order_in_queue(queue_object_st *p_queue_object, int floor,  ButtonType button_type){
    switch (button_type){
        case BUTTON_HALL_UP: 
            if(p_queue_object->orders_up_from_hall[floor] == NO_ORDER) {
                p_queue_object->number_of_active_orders += 1;
                p_queue_object->orders_up_from_hall[floor] = p_queue_object->number_of_active_orders;   
            } break;  
        case BUTTON_HALL_DOWN:
            if(p_queue_object->orders_down_from_hall[floor] == NO_ORDER) {
                p_queue_object->number_of_active_orders += 1;
                p_queue_object->orders_down_from_hall[floor] = p_queue_object->number_of_active_orders;
            } break;  
        case BUTTON_CAB:
            if(p_queue_object->orders_from_inside_cab[floor] == NO_ORDER) {
                p_queue_object->number_of_active_orders += 1;
                p_queue_object->orders_from_inside_cab[floor] = p_queue_object->number_of_active_orders;
            } break;
    }
}

void queue_object_decrement_priorities(queue_object_st *p_queue_object, int priority_threshold) { 
    for (int floor_nr = 0; floor_nr < N_FLOORS; floor_nr++)
    {
        if(p_queue_object->orders_down_from_hall[floor_nr] > priority_threshold){
           p_queue_object->orders_down_from_hall[floor_nr] -= 1;
        } 
        if(p_queue_object->orders_up_from_hall[floor_nr] > priority_threshold){
           p_queue_object->orders_up_from_hall[floor_nr] -= 1;
        }
        if(p_queue_object->orders_from_inside_cab[floor_nr] > priority_threshold){
            p_queue_object->orders_from_inside_cab[floor_nr] -= 1;
        }
    }
}

void queue_object_remove_order(queue_object_st *p_queue_object, int floor,  ButtonType button_type, int priority_threshold){
    switch (button_type){
        case BUTTON_HALL_UP:
            p_queue_object->orders_up_from_hall[floor] = NO_ORDER; break;  
        case BUTTON_HALL_DOWN:
            p_queue_object->orders_down_from_hall[floor] = NO_ORDER; break;  
        case BUTTON_CAB:
            p_queue_object->orders_from_inside_cab[floor] = NO_ORDER; break;
    }
    p_queue_object->number_of_active_orders -= 1;
    queue_object_decrement_priorities(p_queue_object, priority_threshold);
}


int queue_control_get_next_order(){
    for (int floor_nr = 0; floor_nr < N_FLOORS; floor_nr++)
    {
        if(m_queue_list.orders_from_inside_cab[floor_nr] == HIGHEST_PRIORITY || m_queue_list.orders_up_from_hall[floor_nr] == HIGHEST_PRIORITY || 
            m_queue_list.orders_down_from_hall[floor_nr]  == HIGHEST_PRIORITY){
            return floor_nr;
        }
    }
    return NO_ACTIVE_ORDERS;
}

void queue_control_remove_orders_from_floor(int floor){
    if(m_queue_list.orders_up_from_hall[floor] != NO_ORDER){
        queue_object_remove_order(&m_queue_list, floor, BUTTON_HALL_UP, m_queue_list.orders_up_from_hall[floor]);
    }
    if(m_queue_list.orders_down_from_hall[floor] != NO_ORDER){
        queue_object_remove_order(&m_queue_list, floor, BUTTON_HALL_DOWN, m_queue_list.orders_down_from_hall[floor]);
    }
    if(m_queue_list.orders_from_inside_cab[floor] != NO_ORDER){
        queue_object_remove_order(&m_queue_list, floor, BUTTON_CAB, m_queue_list.orders_from_inside_cab[floor]);
    }
}

int queue_control_update_next_destination_up(int current_floor, int destination_floor){
    for (int floor_nr = current_floor + 1; floor_nr < destination_floor; floor_nr++)
    {
        if (m_queue_list.orders_up_from_hall[floor_nr] != NO_ORDER || m_queue_list.orders_from_inside_cab[floor_nr] != NO_ORDER)
        {
            return floor_nr;
        }
    }
    return destination_floor;
}

int queue_control_update_next_destination_down(int current_floor, int destination_floor){
    for (int floor_nr = current_floor -1; floor_nr > destination_floor; floor_nr--)
    {
        if (m_queue_list.orders_down_from_hall[floor_nr] != NO_ORDER || m_queue_list.orders_from_inside_cab[floor_nr] != NO_ORDER)
        {
            return floor_nr;
        }
    }
    return destination_floor;
}