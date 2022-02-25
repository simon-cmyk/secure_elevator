#pragma once
void run_elevator_control(int floor);
void set_elevator_to_start_floor(int startfloor);
typedef enum { 
    AT_REST_CLOSED_DOOR   = 0,
    AT_REST_OPEN_DOOR = 1,
    TRAVELING_UP = 2,
    TRAVELING_DOWN = 3 
} m_elevator_fsm_states_et;