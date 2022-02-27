#pragma once

#define IN_BETWEEN_FLOORS -1
#define ON 1
#define OFF 0


void run_elevator_control();
void elevator_control_set_floor(int floor);
void elevator_control_turn_off_button_lamps(int floor);

typedef enum { 
    AT_REST_CLOSED_DOOR = 0,
    AT_REST_OPEN_DOOR   = 1,
    TRAVELING_UP        = 2,
    TRAVELING_DOWN      = 3 
} m_elevator_fsm_states_et;
