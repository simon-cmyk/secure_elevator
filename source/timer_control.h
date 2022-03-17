/**
 * @file timer_control.h
 * 
 * @brief A group of functions for controlling the timer module.
 * functions with prefix timer_control can be called from other modules, whilst
 * timer_object functions should be internal
 */

#pragma once
#include <time.h>
#include "elevator_constants.h"

/**
 * @struct timer_object_st
 * @brief Struct to function as timer when elevator is running
 * @param start_time                @c time_t object containing time at which timer was initialized or restarted.
 * @param is_active                 Integer to tell whether timer is active (1 if active, 0 otherwise). 
 *                                  Used to determine when we should use the timer. 
 * 
 */
typedef struct{
    time_t start_time;
    int is_active;
} timer_object_st;

/**
 * @brief Restart timer in @p p_timer_obj (inside @p p_timer_obj ).
 * 
 * @param[out] p_timer_obj          Timer object in which to restart timer.
 */
void timer_object_restart(timer_object_st* p_timer_obj);

/**
 * @brief Check if @p p_timer_obj is done counting (inside @p p_timer_obj ).
 * 
 * @param[in, out] p_timer_obj      Timer object in which to check if timer is done counting. 
 * @return TRUE if timer is done counting and FALSE otherwise. 
 */
int timer_object_is_done_counting(timer_object_st* p_timer_obj);

/**
 * @brief Set variable @c is_active in @p p_timer_obj to @p active (inside @p p_timer_obj ).
 * 
 * @param[out] p_timer_obj          Timer object in which to set @c is_active to @p active.
 * @param[in] active                Integer (boolean) value with which to set @c is_active in @p p_timer_obj.
 */
void timer_object_set_is_active(timer_object_st* p_timer_obj, int active);

/**
 * @brief Check if timer is done. Typically used from another module
 * 
 * @param[in, out] p_timer_obj      Timer object in which to check if timer is done counting. 
 * @return TRUE if timer is done counting and FALSE otherwise. 
 */
int timer_control_is_done_counting();

/**
 * @brief checks if the timer is currently active, to decide if one should use it.
 * 
 * @return 1 if it is active, otherwise 0
 */
int timer_control_is_active();

/**
 * @brief Set timer active or not based on the value of @p active 
 *  
 * @param[in] active                Integer (boolean) value with which to set the member variable of a timer
 */
void timer_control_set_is_active(int active);

/**
 * @brief Restart timer, to start counting from start again.
 * 
 */
void timer_control_restart();