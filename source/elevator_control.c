#include <stdio.h>
#include <stdlib.h>
#include "elevator_control.h"
#include "queue_control.h"
#include "driver/elevio.h"
#include "driver/timer_control.h"
#include <assert.h>


int m_current_floor; 
int m_destination_floor;

m_elevator_fsm_states_et m_current_elevator_state = AT_REST_CLOSED_DOOR;

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
        //printf("rest_closed \n");
        elevio_doorOpenLamp(OFF);
        elevio_motorDirection(DIRN_STOP);
        if (m_elevator_timer.is_active == FALSE) 
        {
            timer_restart(&m_elevator_timer);
            m_current_elevator_state = AT_REST_OPEN_DOOR;
        } else {
            assert(timer_done_counting(m_elevator_timer) == TRUE);

            m_destination_floor = queue_control_get_next_order();
            if(m_destination_floor == NO_ACTIVE_ORDERS){
                break;
            }
            if(m_destination_floor > m_current_floor){
                m_current_elevator_state = TRAVELING_UP;
                elevio_motorDirection(DIRN_UP);
            } else {
                m_current_elevator_state = TRAVELING_DOWN;
                elevio_motorDirection(DIRN_DOWN);
            }
        }    
        break;
    case AT_REST_OPEN_DOOR:
        //printf("rest_open \n");
        assert(m_current_floor != IN_BETWEEN_FLOORS);
        
        elevio_doorOpenLamp(ON);
        elevator_control_turn_off_button_lamps(m_current_floor);

        if (elevio_obstruction() == TRUE){ timer_restart(&m_elevator_timer);}
        else if(timer_done_counting(m_elevator_timer) == TRUE){
            m_current_elevator_state = AT_REST_CLOSED_DOOR;
        }
        break;
    case TRAVELING_UP:
        //printf("up \n");
        if (m_current_floor == m_destination_floor){
            queue_control_order_done(m_current_floor);
            m_current_elevator_state = AT_REST_CLOSED_DOOR;
            elevio_motorDirection(DIRN_STOP); 
            m_elevator_timer.is_active = FALSE;          
        }
        break;
    case TRAVELING_DOWN:
        //printf("down \n");
        if (m_current_floor == m_destination_floor){
            queue_control_order_done(m_current_floor);
            m_current_elevator_state = AT_REST_CLOSED_DOOR;
            elevio_motorDirection(DIRN_STOP);
            m_elevator_timer.is_active = FALSE;
        }
        break;
    default:
        break;
    }
}

void elevator_control_turn_off_button_lamps(int floor){
    for (int button_nr = 0; button_nr < N_BUTTONS; button_nr++)
    {
        elevio_buttonLamp(floor, button_nr, OFF);
    }
    
}