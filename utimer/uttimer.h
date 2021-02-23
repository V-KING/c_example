
#ifndef __UTTIMER_H__
#define __UTTIMER_H__
#define llong long long
#include <pthread.h>
#include <semaphore.h>


typedef void  (* timer_handle_ptr)(void* arg); 

typedef struct tagUTTimerEvent
{
    int					heap_idx;       	/* ��ʱ���ڶ��е�λ�� */    
    unsigned int		trigger_intvl;		/* ��ʱ�������������λms */
    llong				trigger_time;    	/* ��ʱ������ʱ�� */
    int 				is_repeat;			/* �Ƿ��ظ����� */
    timer_handle_ptr	timer_handle;   	/* ��ʱ���¼��ص����� */
    void				*arg;
} uttimer_event_Def;

typedef struct tagUTTimerHead
{
	int max_timer_num;				/* ���ʱ���� */
    int cur_timer_num;				/* ��ǰ���ж�ʱ���� */
    sem_t uttimer_sem;
    pthread_mutex_t heap_mutex;
    pthread_t timer_tid;
    uttimer_event_Def   **heap;     /* ��ָ�� */
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
