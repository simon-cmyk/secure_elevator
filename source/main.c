#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "elevator_control.h"


int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    elevio_motorDirection(DIRN_UP);

    while (1)
    {
        int start_floor = elevio_floorSensor();
        if(start_floor > -1 && start_floor <= N_FLOORS){
            set_elevator_start_floor(start_floor);
        }
    }

    while(1){
        int floor = elevio_floorSensor();
        printf("floor: %d \n",floor);

        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }

        run_elevator_control(floor);

        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }


    
    return 0;
}
