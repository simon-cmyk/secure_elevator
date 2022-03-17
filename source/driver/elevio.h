/** @file
 * @brief A module for low-level operations on the motor, lights and buttons.
 */
#pragma once

/**
 * @enum MotorDirection
 * @brief An enum containing the different directions the motor can have.
 */
typedef enum { 
    DIRN_DOWN   = -1,   ///<Motor is working downwards.
    DIRN_STOP   = 0,    ///<Motor is not on.
    DIRN_UP     = 1     ///<Motor is working upwards.
} MotorDirection;

/**
 * @enum ButtonType
 * @brief An enum containing the different types of buttons
 */
typedef enum { 
    BUTTON_HALL_UP      = 0,    ///<Button from corridor pointing upwards.
    BUTTON_HALL_DOWN    = 1,    ///<Button from corridor pointing doqnwards.
    BUTTON_CAB          = 2     ///<Button from cabin (inside the elevator)
} ButtonType;

/**
 * @brief initialize elevator and connect to elevator server
*/
void elevio_init(void);

/**
 * @brief Set the direction of the motor 
 *
 * @param[in] dirn      MotorDirection, used to specify which direction the motor should work in. 
 */
void elevio_motorDirection(MotorDirection dirn);

/**
 * @brief Turn on/off the buttonLamp at floor @p floor, of type @p button , based on the @p value  
 * 
 * @param[in] floor         floor_nr of type integer
 * @param[in] button        button_nr of type @c ButtonType
 * @param[in] value         button_nr of type @c ButtonType       
*/
void elevio_buttonLamp(int floor, ButtonType button, int value);

/**
 * @brief Turn on floorIndicator lamp at @c floor
 * 
 * @param[in] floor                Integer of floor, to specify which floor the elevator currently is in
 */
void elevio_floorIndicator(int floor);

/**
 * @brief Set the door open lamp to on/off, based on @c value 
 * 
 * @param[in] value                Integer (boolean) value, specifying if the door is open or not
 */
void elevio_doorOpenLamp(int value);

/**
 * @brief Set the stop button lamp to on/off, based on @c value 
 * 
 * @param[in] value                Integer (boolean) value, specifying if the stop button is pushed
 */
void elevio_stopLamp(int value);

/**
 * @brief returns if the button on floor_nr @c floor , of type @c button is pushed or not
 * 
 * @param[in] floor          floor number of type int
 * @param[in] button         button type of type @c ButtonType
 * @return 1 if it has been pushed, returns 0 if not
 */
int elevio_callButton(int floor, ButtonType button);

/**
 * @brief gives the floor the elevator is currently on.
 * 
 * @return int of the floor the elevator is on, first floor 0, if the elevator is in beetween floors it returns -1
 */
int elevio_floorSensor(void);

/**
 * @brief says wether or not the stop button has been pushed
 * 
 * @return 1 if it has been pushed, 0 if not.
 */
int elevio_stopButton(void);

/**
 * @brief says wether or not the obstruction is on
 * 
 * @return 1 if it is on, 0 if not
 */
int elevio_obstruction(void);

