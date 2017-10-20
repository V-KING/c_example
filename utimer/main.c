#include "./uttimer.h"
#include <stdio.h>

void print_handle (void *arg){
	int var = *((int *)arg);
	printf("var = %d\n", var);
}


int main(int argc, const char *argv[])
{
    
    int arg = 1234;
    printf("arg = %d\n", arg);
    
    
    
    uttimer_head_def *pUttimer_head = uttimer_init(1);
    uttimer_event_Def *ptimer1 = uttimer_create(print_handle, &arg, 1);
    uttimer_start(pUttimer_head, ptimer1, 1000);
    while(1);
    
//     uttimer_head_def *pUttimer_head = uttimer_max_construct(1);
//     uttimer_event_Def *ptimer1 = uttimer_create(print_handle, &arg, 1);
//     uttimer_start(pUttimer_head, ptimer1, 1000);
//     while(1);
    
    return 0;
}

