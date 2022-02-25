#include "timer_control.h"



// sets new start and end time of timer object
void timer_restart(timer_st *timer_obj){
    time_t time_now;
    timer_obj->start_time = time(&time_now);
    timer_obj->is_active = TRUE; 
}

// checks if timer object is done counting
// [delete] Husk å endre int til int_8 eller hva det var...
int timer_done_counting(timer_st timer_obj) {
    time_t time_now;
    time_now = time(&time_now);
    double time_elapsed = difftime(time_now, timer_obj.start_time);
    printf("time_elapsed: %g \n", time_elapsed);
    return time_elapsed >= TIMER_SECONDS_BEFORE_DONE;
}

// [delete] kan slette denne funksjonen før innlevering, men kan være grei å ha
double get_elapsed_time(struct timeval begin){
    struct timeval end;
    gettimeofday(&end, TIME_UTC);
    int seconds = end.tv_sec - begin.tv_sec;
    long mseconds = (end.tv_usec - begin.tv_usec)/1000;
    double elapsed = seconds + mseconds*1e-3;
    return elapsed;
}