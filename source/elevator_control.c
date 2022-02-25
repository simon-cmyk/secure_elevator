#include "elevator_control.h"
#include "driver/elevio.h"
#include <stdio.h>
#include <stdlib.h>
#include "driver/timer_control.h"
#include <assert.h>

int m_current_floor; 
int m_destination_floor = 2;

m_elevator_fsm_states_et; 
m_current_elevator_state = TRAVELING_UP;

timer_st m_elevator_timer = {.is_active=0};

void elevator_control_set_floor(int floor){
    assert(floor > -1 && floor < N_FLOORS);

    m_current_floor = floor;
    elevio_floorIndicator(m_current_floor);
}

 // TODO: check if old floorlamps is still on.
void run_elevator(){
    switch (m_current_elevator_state)
    {
    case AT_REST_CLOSED_DOOR:
        printf("At_rest_closed\n");
        elevio_motorDirection(DIRN_STOP);
        if (m_elevator_timer.is_active == FALSE) 
        {
            printf("start timer\n");
            elevator_control_restart_timer();
            m_current_elevator_state = AT_REST_OPEN_DOOR;
        } else {
            assert(timer_done_counting(m_elevator_timer) == TRUE);
            m_elevator_timer.is_active = FALSE;

            printf("elevator done\n");
            //TODO: implement get_order_from_queue
            //get_order_from_queue()
            //TODO: create update queue_object function
            // update_queue_object();
            //do that order 
            elevio_motorDirection(DIRN_DOWN);
            m_current_elevator_state = TRAVELING_DOWN;
        }    
        break;
    case AT_REST_OPEN_DOOR:
        assert(m_current_floor != IN_BETWEEN_FLOORS);
        if (elevio_obstruction() == TRUE){ elevator_control_restart_timer;}
        if(timer_done_counting(m_elevator_timer) == TRUE){
            m_current_elevator_state = AT_REST_CLOSED_DOOR;
        }
        break;
    case TRAVELING_UP:
        printf("at travelling up\n");
        if (m_current_floor == m_destination_floor){
            m_current_elevator_state = AT_REST_CLOSED_DOOR;
            elevio_motorDirection(DIRN_STOP);           
        }
        break;
    case TRAVELING_DOWN:
        if (m_current_floor == m_destination_floor){
            m_current_elevator_state = AT_REST_CLOSED_DOOR;
            elevio_motorDirection(DIRN_STOP);
        }
        break;
    default:
        break;
    }
}

void elevator_control_restart_timer(){
    timer_restart(&m_elevator_timer);
}