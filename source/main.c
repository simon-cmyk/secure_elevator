#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "elevator_control.h"
#include "queue_control.h"

#define IN_BETWEEN_FLOORS -1

int main(){
    elevio_init();
    
    queue_object_st test = {{0},{0}, {0}};
    printf("test:");
    for (int i = 0; i < sizeof(test.priority); i++)
    {
        printf("test  at i %d, %d",i ,test.priority[i]);
    }
    

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    // Set elevator to floor at start. 
    while (0)
    {
        elevio_motorDirection(DIRN_UP);
        int start_floor = elevio_floorSensor();
        if(start_floor > -1 && start_floor <= N_FLOORS){
            set_elevator_to_start_floor(start_floor);
            break; 
        }
    }

    
    
    //Check if elevator have arrived to new floor or if new buttons are pressed.
    while(1){
        int floor = elevio_floorSensor();
        printf("floor: %d \n", floor);

        if(floor != IN_BETWEEN_FLOORS){
            run_elevator(floor);
        }
        

        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
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
