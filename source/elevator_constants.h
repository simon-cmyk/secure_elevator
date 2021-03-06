/** @file
 * @brief A module for constants used in other files, defined as macros.
 * This is to avoid magic numbers (for readability), and make it easier for developer to implement changes.
 */
#pragma once
#include <stdio.h>
#include <stdlib.h>

// Variables that can easily be changed 
#define TIMER_SECONDS_BEFORE_DONE 3.0
#define N_FLOORS 4
#define N_BUTTONS 3

// Set name on magic numbers
#define HIGHEST_PRIORITY 1
#define TRUE 1
#define ON 1
#define SMALL_OFFSET 0.2
#define FALSE 0
#define OFF 0
#define NO_ORDER 0
#define IN_BETWEEN_FLOORS -1
#define NO_ACTIVE_ORDERS -1