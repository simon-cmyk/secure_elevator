#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "elevator_control.h"
#include "elevator_constants.h"

void initialize_elevator_to_start_floor();


int main(){
    printf("=== Elevator start ===\n");
    elevio_init();

    // print arrays test
    
    // Set elevator to floor at start. 
    initialize_elevator_to_start_floor();
    printf("------------------------------\n");
    printf("elevator correctly initialized\n");
    printf("------------------------------\n");
    
    //Check if elevator have arrived to new floor or if new buttons are pressed.
    while(1){
        int floor = elevio_floorSensor();
        //printf("floor: %d \n", floor);
        if(floor != IN_BETWEEN_FLOORS && floor >= 0 && floor <= N_FLOORS){
            elevator_control_set_floor(floor);
        }
        //TODO: check if floor indicator is working
        

        if(elevio_stopButton() == TRUE){
            elevio_stopLamp(ON);
            change_state_stop_button_pressed();
        } else {
            elevio_stopLamp(OFF);
            for(int floor_nr = 0; floor_nr < N_FLOORS; floor_nr++){
                for(int button_nr = 0; button_nr < N_BUTTONS; button_nr++){
                    if (elevio_callButton(floor_nr, button_nr) == ON)
                    {
                        elevio_buttonLamp(floor_nr, button_nr, ON);
                        queue_control_place_order(floor_nr, button_nr);
                    }
                }
            }
        }

        run_elevator_control_fsm();

        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }
    return 0;
}

void initialize_elevator_to_start_floor(){
    for(int floor_nr = 0; floor_nr < N_FLOORS; floor_nr++){
        elevator_control_turn_off_button_lamps(floor_nr);
    }
    elevio_doorOpenLamp(OFF);
    elevio_motorDirection(DIRN_DOWN);
    while (1)
    {
        int start_floor = elevio_floorSensor();
        if(start_floor > -1 && start_floor <= N_FLOORS){
            elevator_control_set_floor(start_floor);
            elevio_motorDirection(DIRN_STOP);    
            break; 
        }
    }
}
