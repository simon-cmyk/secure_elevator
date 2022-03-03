#pragma once


void run_elevator_control_fsm();
void elevator_control_set_floor(int floor);
void elevator_control_turn_off_button_lamps(int floor);
void elevator_control_stop_button_pressed();
void elevator_control_at_dest_floor();

typedef enum { 
    AT_REST_CLOSED_DOOR = 0,
    AT_REST_OPEN_DOOR   = 1,
    TRAVELING_UP        = 2,
    TRAVELING_DOWN      = 3 
} m_elevator_fsm_states_et;
