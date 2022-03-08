/**
 * @file
 * @brief A library for controlling the elevator. 
 */

#pragma once

/**
 * @brief Run finite-state-machine/elevator
 * 
 */
void run_elevator_control_fsm();

/**
 * @brief Set variable @p m_current_floor to @p floor and set correct light on floor panel.
 * 
 * @param floor Floor integer with which to update @p m_current_floor and set ligth on floor panel.
 */
void elevator_control_set_floor(int floor);

/**
 * @brief 
 * 
 * @param floor 
 */
void elevator_control_turn_off_button_lamps(int floor);

void change_state_stop_button_pressed();
void change_state_stop_at_floor();
void change_state_start_travel_up();
void change_state_start_travel_down();
void change_state_open_door();
void change_state_close_door();

typedef enum { 
    AT_REST_CLOSED_DOOR = 0,
    AT_REST_OPEN_DOOR   = 1,
    TRAVELING_UP        = 2,
    TRAVELING_DOWN      = 3 
} elevator_fsm_states_et;
