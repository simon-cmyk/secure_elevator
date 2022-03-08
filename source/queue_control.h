/** @file
 * @brief A library for performing operations on queue module
 */

#pragma once
#include "driver/elevio.h"
#include "elevator_control.h"
#include "elevator_constants.h"

/** 
 * @struct queue_object_st
 * @brief A struct that contains information about elevator orders.
 *  
 */
typedef struct 
{
    int orders_from_inside_cab[N_FLOORS]; 
    int orders_up_from_hall[N_FLOORS];
    int orders_down_from_hall[N_FLOORS];
    int number_of_active_orders;
} queue_object_st;

/**
 * @brief Place elevator order in @p p_queue_object from inside @p p_queue_object.
 * 
 * @param[out] p_queue_object       Queue object in which to place order.
 * @param[in] floor                 Destination floor of order.
 * @param[in] button_type           Type of button pressed to initiate order.
 */
void queue_object_place_order_in_queue(queue_object_st *p_queue_object, int floor, ButtonType button_type);

/**
 * @brief Remove elevator order from @p p_queue_object from inside @p p_queue_object
 * 
 * @param[out] p_queue_object       Queue object from which to remove order.
 * @param[in] floor                 Destination floor of order to be removed. 
 * @param[in] button_type           Type of button when initiating order to be removed
 * @param[in] priority_threshold    Threshold to determine the orders that need to be decremented in order to update priorities of existing orders in @p p_queue_object after order is removed.
 */
void queue_object_remove_order(queue_object_st *p_queue_object, int floor,  ButtonType button_type, int priority_threshold);

/**
 * @brief Decrement queue priorities in @p p_queue_object above a certain priority level, @p priority_threshold. 
 * 
 * @param[out] p_queue_object       Queue object in which to decrement priorities.
 * @param[in] priority_threshold    Priority level threshold above which to decrement all queue order priorities. (High priority number = low priority).
 */
void queue_object_decrement_priorities(queue_object_st *p_queue_object, int priority_threshold);

/**
 * @brief Place elevator order in @p p_queue_object from outside @p p_queue_object.
 * 
 * @param[in] floor                 Destination floor of order.
 * @param[in] button_type           Type of button pressed to initiate order.
 */
void queue_control_place_order(int floor,  ButtonType button_type);

/**
 * @brief Get the elevator order with the highest priority from @p p_queue_object.
 * 
 * @return Destination floor of order with highest priority. @c NO_ACTIVE_ORDERS if there are no active elevator orders
 */
int queue_control_get_next_order();

/**
 * @brief Remove all elevator orders with @floor as destination floor. 
 * 
 * @param[in] floor                 Floor from which to remove all orders. 
 */
void queue_control_remove_orders_from_floor(int floor);

/**
 * @brief Update destination floor of elevator when traveling upwards. Check if there are any orders with destination floor between @p current_floor and @p destination_floor.
 * 
 * @param[in] current_floor         Floor in which elevator currently is.
 * @param[in] destination_floor     Floor to which elevator is headed. 
 * @return Most approximate destination floor in queue between @p current_floor and @p destination_floor. 
 */
int queue_control_update_next_destination_up(int current_floor, int destination_floor);

/**
 * @brief Update destination floor of elevator when traveling downwards. Check if there are any orders with destination floor between @p current_floor and @p destination_floor.
 * 
 * @param[in] current_floor         Floor in which elevator currently is.
 * @param[in] destination_floor     Floor to which elevator is headed. 
 * @return Most approximate destination floor in queue between @p current_floor and @p destination_floor. 
 */
int queue_control_update_next_destination_down(int current_floor, int destination_floor);
