#include "timer_control.h"

static timer_object_st m_timer = {.is_active = FALSE};

void timer_object_restart(timer_object_st * p_timer_obj){
    time_t time_now;
    p_timer_obj->start_time = time(&time_now);
    p_timer_obj->is_active = TRUE; 
}

int timer_object_is_done_counting(timer_object_st *p_timer_obj) {
    time_t time_now;
    time_now = time(&time_now);
    double time_elapsed = difftime(time_now, p_timer_obj->start_time);
    return time_elapsed >= TIMER_SECONDS_BEFORE_DONE;
}

void timer_object_set_is_active(timer_object_st* p_timer_obj, int active){
    p_timer_obj->is_active = active;
}

int timer_control_is_done_counting(){
    return timer_object_is_done_counting(&m_timer);
}

int timer_control_is_active(){
    return m_timer.is_active;
}

void timer_control_set_is_active(int active){
    timer_object_set_is_active(&m_timer, active);
}

void timer_control_restart(){
    timer_object_restart(&m_timer);
}