#include "queue_control.h"
#define NO_ORDER -1

queue_object_st queue_list = {{0},{0},{-1}, 0};


void queue_object_add_order(int floor, int button){
    queue_object_place_order(&queue_list, floor, button);
}

// sets a given order in order_priority array to highest priority
void queue_object_prioritize(queue_object_st *queue_obj, int order_priority_arr_index){
    int old_order_priority_value = queue_obj->order_priority[order_priority_arr_index];
    int order_priority_arr_size = sizeof(queue_obj->order_priority)/sizeof(queue_obj->order_priority[0]);
    if (queue_obj->order_priority[order_priority_arr_index] == -1){
        for (unsigned int i = 0; i < order_priority_arr_size; i++){
            if (queue_obj->order_priority[i] != -1){
                queue_obj->order_priority[i] += 1;
            }
        }

    } else {
        for (unsigned int i = 0; i < order_priority_arr_size; i++){
            if ((queue_obj->order_priority[i] < old_order_priority_value) & (queue_obj->order_priority[i] != -1)){
                queue_obj->order_priority[i] += 1;
            }
        }
    }
    queue_obj->order_priority[order_priority_arr_index] = 0;
}

// places new order in order_priority and gives it lowest priority
void queue_object_new_order_bottom_priority(queue_object_st *queue_obj, int order_priority_arr_index){
    queue_obj->order_priority[order_priority_arr_index] = array_handling_find_max(queue_obj->order_priority, 12) + 1;
}

// places new order in queue_object. 
void queue_object_place_order(queue_object_st *queue_object, int floor,  ButtonType button_type){
    switch (button_type){
        case 0: 
            if(queue_object->orders_up_from_hall[floor] == 0) {
                queue_object->orders_up_from_hall[floor] = 1;
            } break;  
        case 1:
            if(queue_object->orders_down_from_hall[floor] == 0) {
                queue_object->orders_down_from_hall[floor] = 1;
            } break;  
        case 2:
            if(queue_object->orders_from_inside_cab[floor] == 0) {
                queue_object->orders_from_inside_cab[floor] = 1;
            } break;
    }
        int index_in_order_priority = ((int) button_type + 1) * floor - 1;
        if (queue_object->order_priority[index_in_order_priority] == NO_ORDER)
        {
            queue_object->order_priority[index_in_order_priority] = queue_object->number_of_active_orders;
            queue_object->number_of_active_orders += 1;
        }
    }
}