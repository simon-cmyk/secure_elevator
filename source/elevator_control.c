#include <stdio.h>
#include <stdlib.h>
#include "elevator_control.h"
#include "queue_control.h"
#include "driver/elevio.h"
#include "timer_control.h"
#include "array_handling.h"
#include <assert.h>


double m_current_floor; 
int m_destination_floor;

m_elevator_fsm_states_et m_current_elevator_state = AT_REST_CLOSED_DOOR;

timer_st m_elevator_timer = {.is_currently_in_use = FALSE};

void elevator_control_set_floor(int floor){
    assert(floor > -1 && floor < N_FLOORS);

    m_current_floor = floor;
    elevio_floorIndicator(m_current_floor);
}

 // TODO: check if old floorlamps is still on.
void run_elevator_control_fsm(){
    switch (m_current_elevator_state)
    {
    case AT_REST_CLOSED_DOOR:
        //printf("rest_closed \n");
        elevio_doorOpenLamp(OFF);
        elevio_motorDirection(DIRN_STOP);
        if (m_elevator_timer.is_currently_in_use == FALSE) 
        {
            timer_restart(&m_elevator_timer);
            m_current_elevator_state = AT_REST_OPEN_DOOR;
        } else {
            
            m_destination_floor = queue_control_get_next_order();
            //printf("dest: %d. Curr: %d \n", m_destination_floor, m_current_floor);
            if(m_destination_floor == NO_ACTIVE_ORDERS){
                printf("No active orders\n");
                break;
            }
            if(m_destination_floor == m_current_floor){
                printf("Equal\n");
                queue_control_order_done(m_destination_floor);
                m_elevator_timer.is_currently_in_use = FALSE; 
                break;
            }
            else if(m_destination_floor > m_current_floor){
                printf("dest > curr\n");
                m_current_elevator_state = TRAVELING_UP;
                elevio_motorDirection(DIRN_UP);
            } else {
                printf("dest < curr\n");
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
            m_elevator_timer.is_currently_in_use = TRUE;
            queue_control_order_done(m_current_floor);
            elevator_control_turn_off_button_lamps(m_current_floor);
        }
        break;
    case TRAVELING_UP:
        printf("dest: %d. Curr: %d \n", m_destination_floor, m_current_floor);
        //printf("up \n");
        if (m_current_floor == m_destination_floor){
            elevator_control_at_dest_floor();        
        } else {
            m_destination_floor = queue_control_stop_on_way_up(m_current_floor, m_destination_floor);
        }
        break;
    case TRAVELING_DOWN:
        //printf("down \n");
        printf("dest: %d. Curr: %g \n", m_destination_floor, m_current_floor);
        if (m_current_floor == m_destination_floor){
            elevator_control_at_dest_floor();
        } else {
            m_destination_floor = queue_control_stop_on_way_down(m_current_floor, m_destination_floor);
        }
        break;
    }
}

void elevator_control_turn_off_button_lamps(int floor){
    for (int button_nr = 0; button_nr < N_BUTTONS; button_nr++)
    {
        elevio_buttonLamp(floor, button_nr, OFF);
    } 
}

void elevator_control_stop_button_pressed(){
    switch (m_current_elevator_state)
    {
    case TRAVELING_UP:
        m_current_floor += 0.5;
        m_elevator_timer.is_currently_in_use = TRUE;
        m_current_elevator_state = AT_REST_CLOSED_DOOR;
        break;
    case TRAVELING_DOWN:
        m_current_floor -= 0.5;
        m_elevator_timer.is_currently_in_use = TRUE;
        m_current_elevator_state = AT_REST_CLOSED_DOOR;
        break;
    case AT_REST_CLOSED_DOOR:
        if(floorf(m_current_floor) == m_current_floor) {
            timer_restart(&m_elevator_timer);
            m_current_elevator_state = AT_REST_OPEN_DOOR;
        }
    case AT_REST_OPEN_DOOR:
        timer_restart(&m_elevator_timer);
    }
    for(int floor = 0; floor < N_FLOORS; floor++){
        queue_control_order_done(floor);
        elevator_control_turn_off_button_lamps(floor);
    }

    
}

void elevator_control_at_dest_floor(){
    elevio_motorDirection(DIRN_STOP);
    m_current_elevator_state = AT_REST_CLOSED_DOOR; 
    m_elevator_timer.is_currently_in_use = FALSE;
    queue_control_order_done(m_current_floor); 
}