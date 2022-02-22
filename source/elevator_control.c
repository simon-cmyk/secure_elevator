#include "elevator_control.h"
#include "driver/elevio.h"
#include <stdio.h>
#include <stdlib.h>

int m_current_floor; 
m_elevator_fsm_states_et current_elevator_state = AT_REST_CLOSED_DOOR;

void set_elevator_start_floor(int startfloor){
    m_current_floor = startfloor;
}

void run_elevator_control(int floor){
    if(floor > -1 && floor <= N_FLOORS){
        m_current_floor = floor;
    }
    // printf("floor: %d, %d \n",floor, m_current_floor);

    switch (current_elevator_state)
    {
    case AT_REST_CLOSED_DOOR:
        // open_door();
        current_elevator_state = AT_REST_OPEN_DOOR;
        // start_travel_up();
        current_elevator_state = TRAVELING_UP;
        // start_travel_down();
        current_elevator_state = TRAVELING_DOWN;
        break;
    case AT_REST_OPEN_DOOR:
        // close_door();
        current_elevator_state = AT_REST_CLOSED_DOOR;
        break;
    case TRAVELING_UP:
        // stop_at_floor();
        current_elevator_state = AT_REST_CLOSED_DOOR;
        break;
    case TRAVELING_DOWN:
        // stop_at_floor();
        current_elevator_state = AT_REST_CLOSED_DOOR;
        break;
    default:
        break;

    if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
    if(elevio_stopButton()){
        elevio_motorDirection(DIRN_STOP);
        break;
    }
    }
}