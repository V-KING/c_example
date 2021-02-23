
#ifndef __UTTIMER_H__
#define __UTTIMER_H__
#define llong long long
#include <pthread.h>
#include <semaphore.h>


typedef void  (* timer_handle_ptr)(void* arg); 

typedef struct tagUTTimerEvent
{
    int					heap_idx;       	/* 定时器在堆中的位置 */    
    unsigned int		trigger_intvl;		/* 定时器触发间隔，单位ms */
    llong				trigger_time;    	/* 定时器触发时间 */
    int 				is_repeat;			/* 是否重复触发 */
    timer_handle_ptr	timer_handle;   	/* 定时器事件回调函数 */
    void				*arg;
} uttimer_event_Def;

typedef struct tagUTTimerHead
{
	int max_timer_num;				/* 最大定时器数 */
    int cur_timer_num;				/* 当前已有定时器数 */
    sem_t uttimer_sem;
    pthread_mutex_t heap_mutex;
    pthread_t timer_tid;
    uttimer_event_Def   **heap;     /* 堆指针 */
} uttimer_head_def;

llong get_now_ms();
uttimer_head_def *uttimer_init(unsigned int max_timer_num);
void uttimer_uninit(uttimer_head_def *uttimer_head);
uttimer_event_Def *uttimer_create(timer_handle_ptr handle, void *arg, int is_repeat);
void uttimer_destroy(uttimer_head_def *uttimer_head, uttimer_event_Def *uttimer);
void uttimer_start(uttimer_head_def *uttimer_head, uttimer_event_Def *uttimer, unsigned int time_invtl);
void uttimer_stop(uttimer_head_def *uttimer_head, uttimer_event_Def *uttimer);
int is_uttimer_start(uttimer_head_def *uttimer_head, uttimer_event_Def *uttimer);


uttimer_head_def *uttimer_head;

#endif
