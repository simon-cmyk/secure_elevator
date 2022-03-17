/**
 * @file
 * @brief A group of functions for controlling the elevator.  
 */

#pragma once
#include "queue_control.h"
#include "timer_control.h"
#include "driver/elevio.h"
#include "elevator_constants.h"
/**
 * @brief Run finite-state machine/ elevator.
 * this is a switch loop checking the state of the state machine, and making actions/transitions accordingly.
 */
void run_elevator_control_fsm();

/**
 * @brief Set variable @p m_current_floor to @p floor and set correct light on floor panel.
 * 
 * @param[in] floor     Floor integer with which to update @p m_current_floor and set ligth on floor panel.
 */
void elevator_control_set_floor(int floor);

/**
 * @brief Turn off all button lamps in @p floor.
 * 
 * @param[in] floor         Floor in which to turn off button lamps. 
 */

void elevator_control_turn_off_button_lamps(int floor);

/**
 * @brief Change state in finite-state machine to @c AT_REST_CLOSED_DOOR in case stop button is pressed.
 * can be called from all states
 */
void change_state_stop_button_pressed();

/**
 * @brief Change state in finite-state machine to @c AT_REST_CLOSED_DOOR.
 * can be called from @c TRAVELLING_UP and @c TRAVELLING_DOWN
 */
void change_state_stop_at_floor();

/**
 * @brief Change state in finite-state machine to @c TRAVELING_UP.
 * can be called from @c AT_REST_CLOSED_DOOR
 */
void change_state_start_travel_up();

/**
 * @brief Change state in finite-state machine to @c TRAVELING_DOWN.
 * can be called from @c AT_REST_CLOSED_DOOR
 */
void change_state_start_travel_down();

/**
 * @brief Change state in finite-state machine to @c AT_REST_OPEN_DOOR.
 * can be called from @c AT_REST_CLOSED_DOOR and from pushing stop button while at a valid floor.
 */
void change_state_open_door();

/**
 * @brief Change state in finite-state machine to @c AT_REST_CLOSED_DOOR
 * can be called from @c AT_REST_OPEN_DOOR
 */
void change_state_close_door();


/**
 * @enum elevator_fsm_states
 * @brief An enum containing the different states of the finite-state machine
 */
typedef enum { 
    AT_REST_CLOSED_DOOR = 0,    ///<Elevator is not moving and door is closed.
    AT_REST_OPEN_DOOR   = 1,    ///<Elevator is not moving and door is open.
    TRAVELING_UP        = 2,    ///<Elevator is traveling upwards.
    TRAVELING_DOWN      = 3     ///<Elevator is traveling downwards.
} elevator_fsm_states_et;
