#include "elevator_control.h"
#include "driver/elevio.h"
#include <stdio.h>
#include <stdlib.h>

int m_current_floor; 
int m_destination_floor;

m_elevator_fsm_states_et current_elevator_state = AT_REST_CLOSED_DOOR;

void set_elevator_to_start_floor(int startfloor){
    m_current_floor = startfloor;
}

 // TODO: check if old floorlamps is still on.
void run_elevator(int floor){
    if(floor > 0 & floor <= N_FLOORS){
        m_current_floor = floor;
        //TODO: spør studass om det er ein grei måte o gjøre det på . 
        elevio_floorIndicator(m_current_floor);
    }
    // printf("floor: %d, %d \n",floor, m_current_floor);

    switch (current_elevator_state)
    {
    case AT_REST_CLOSED_DOOR:
        current_elevator_state = AT_REST_OPEN_DOOR;
        // start_travel_up();
        current_elevator_state = TRAVELING_UP;
        // start_travel_down();
        current_elevator_state = TRAVELING_DOWN;
        break;
    case AT_REST_OPEN_DOOR:
        
        current_elevator_state = AT_REST_CLOSED_DOOR;

        //TODO: implement get_order_from_queue
        //get_order_from_queue()
        break;
    case TRAVELING_UP:
        if (m_current_floor == m_destination_floor){current_elevator_state = AT_REST_CLOSED_DOOR;}
        //TODO: create update queue_object function
        // update_queue_object();
        break;
    case TRAVELING_DOWN:
        if (m_current_floor == m_destination_floor){current_elevator_state = AT_REST_CLOSED_DOOR;}
        // update_queue_object();
        break;
    default:
        break;
    }
}