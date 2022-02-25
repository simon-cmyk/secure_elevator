#include "timer_control.h"



// sets new start and end time of timer object
void timer_restart(timer_st *timer_obj){
    struct timeval new_start_time;
    gettimeofday(&new_start_time, TIME_UTC);
    timer_obj->start_time = new_start_time;
    timer_obj->end_time = TIMER_SECONDS_BEFORE_DONE;
    timer_obj->is_active = TRUE; 
}

// checks if timer object is done counting
// [delete] Husk å endre int til int_8 eller hva det var...
int timer_done_counting(timer_st timer_obj) {
    struct timeval curr_time;
    gettimeofday(&curr_time, TIME_UTC);
    int difference_secs = curr_time.tv_sec - timer_obj.start_time.tv_sec;
    int difference_msecs = (curr_time.tv_usec - timer_obj.start_time.tv_usec)/1000;
    double time_elapsed = difference_secs + difference_msecs*1e-3;
    printf("time_elapsed: %g \n", time_elapsed);
    return time_elapsed >= timer_obj.end_time;
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