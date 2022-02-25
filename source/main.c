#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "elevator_control.h"
#include "queue_control.h"

void initialize_elevator_to_start_floor();


int main(){
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");
    elevio_init();
    
    // Set elevator to floor at start. 
    initialize_elevator_to_start_floor();

    elevio_motorDirection(DIRN_UP);
    
    //Check if elevator have arrived to new floor or if new buttons are pressed.
    while(1){
        int floor = elevio_floorSensor();
        printf("floor: %d \n", floor);
        if(floor != IN_BETWEEN_FLOORS){
            elevator_control_set_floor(floor);
            run_elevator();
        }
        //TODO: check if floor indicator is working
        
        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
                if (btnPressed == 1)
                {
                    //queue_object_add_order(f, b);
                }
                
            }
        }

        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
        break;
        }
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }


    
    return 0;
}

void initialize_elevator_to_start_floor(){
    while (1)
    {
        int start_floor = elevio_floorSensor();
        if(start_floor > -1 && start_floor <= N_FLOORS){
            elevator_control_set_floor(start_floor);    
            break; 
        }
    }
}