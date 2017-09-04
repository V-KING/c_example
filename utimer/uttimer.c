#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>

//#include "../boards2/rfid_types.h"
//#include "../boards2/readeropt.h"
//#include "invglog.h"
#include "uttimer.h"


unsigned int cpu_diff_us( struct timeval *tv )
{
	int retval;
	struct timeval currentv;
	unsigned int timediff = 0;
    	
	retval = gettimeofday( &currentv, NULL );	
	timediff = (currentv.tv_sec-tv->tv_sec)*1000000;
	timediff += (currentv.tv_usec-tv->tv_usec);
	return timediff;
}


int cpu_get_lltimer( struct timeval* tv )
{    	
	int retval;
	retval = gettimeofday( tv, NULL );	
	return retval;
}


llong get_now_ms()
{
	llong millisecond = 0;
	struct timeval  tv;
    gettimeofday(&tv, NULL);
    millisecond = tv.tv_sec;
    millisecond = millisecond * 1000 + tv.tv_usec / 1000;
    return millisecond;
}


static int heap_insert(uttimer_head_def *uttimer_head, uttimer_event_Def *uttimer)
{
    int index = 0;
    int parent_idx  = 0;
    uttimer_event_Def *parent = NULL;
    
	/* �������Ϸ���*/ 
	if(uttimer_head == NULL || uttimer == NULL)
	{
		printf("param error\n");
		return -1;
	}

    if (uttimer_head->cur_timer_num == uttimer_head->max_timer_num)
    {
        printf("heap full\n");
        return -1;
    }

    uttimer_head->cur_timer_num += 1;

    /* �ҵ���ʱ��ʱ������λ�� */
    index = uttimer_head->cur_timer_num;
    while (index > 1)
    {
        parent_idx = index / 2;
        parent = uttimer_head->heap[parent_idx];
        
        /* ��ǰ�ڵ㲻С�ڸ��ڵ㣬��Ϊ���ڵ�ĺ��� */
        if (!(uttimer->trigger_time < parent->trigger_time))
        {
            break;
        }

        /* �ƶ����ڵ� */
        uttimer_head->heap[index]  = parent;
        parent->heap_idx = index;
        uttimer_head->heap[parent_idx] = NULL;
        index = parent_idx;
    }
    uttimer_head->heap[index] = uttimer;
    uttimer->heap_idx = index;

	//INVG_LOG_DBG(DBG_UTTIMER, "add %d, trigger_intvl = %d\n", uttimer->heap_idx, uttimer->trigger_intvl);
    //heap_print(uttimer_head);

    return 0;
}


static uttimer_event_Def *heap_remove(uttimer_head_def *uttimer_head, unsigned int uttimer_id)
{
    int index = 0;
    int last_leaf_idx = 0;
    int lchild_idx = 0;
    int rchild_idx = 0;
    uttimer_event_Def *uttimer = NULL;
    uttimer_event_Def *last_item = NULL;

    /* �������Ϸ���*/ 
	if(uttimer_head == NULL || uttimer_id == 0)
	{
		printf("param error\n");
		return NULL;
	}

    if(uttimer_id > uttimer_head->cur_timer_num)
    {
    	printf("timer %d is larger than cur_timer_num %d\n", uttimer_id, uttimer_head->cur_timer_num);
        return NULL;
    }

	uttimer = uttimer_head->heap[uttimer_id];
    last_item = uttimer_head->heap[uttimer_head->cur_timer_num];
    last_leaf_idx = uttimer_head->cur_timer_num / 2;

	/* �ضѽ�㵽��Ҷ���·�������ý�������Ҷ����ϣ�����·������Сֵ������ԭ��Ҫɾ���Ķѽ���� */
	index = uttimer_id;
    while (index <= last_leaf_idx)
    {
        lchild_idx = index * 2;  		/* ���� */
        rchild_idx = lchild_idx + 1;  	/* �Һ��� */

        /* �ýڵ����Һ��� */
        if (lchild_idx != uttimer_head->cur_timer_num)
        {
            /* �Һ���С�������� */
            if (uttimer_head->heap[rchild_idx]->trigger_time < uttimer_head->heap[lchild_idx]->trigger_time)
            {
                lchild_idx = rchild_idx;
            }
        }

        /* ��ֵ��С�����һ��Ԫ�صģ��˳�ѭ�� */
        if (!(uttimer_head->heap[lchild_idx]->trigger_time < last_item->trigger_time))
        {
            break;
        }
        uttimer_head->heap[index] = uttimer_head->heap[lchild_idx];
        uttimer_head->heap[lchild_idx] = NULL;
        uttimer_head->heap[index]->heap_idx = index;
        index = lchild_idx;
    }
    uttimer_head->heap[index] = last_item;
    uttimer_head->heap[index]->heap_idx = index;
    uttimer_head->cur_timer_num -= 1;

	//INVG_LOG_DBG(DBG_UTTIMER, "remove id %d, heap_id = %d, cur_timer_num = %d\n", 
		//uttimer_id, uttimer->heap_idx, uttimer_head->cur_timer_num);
	//heap_print(uttimer_head);

	uttimer->heap_idx = 0;

    return uttimer;
}


int is_uttimer_start(uttimer_head_def *uttimer_head, uttimer_event_Def *uttimer)
{
	int ret = 0;

	if(uttimer_head == NULL || uttimer == NULL)
	{

		printf("param error\n");
		return 0;
	}

	ret = uttimer->heap_idx;

	return ret;
}


void uttimer_start(uttimer_head_def *uttimer_head, uttimer_event_Def *uttimer, unsigned int time_invtl)
{
	if(uttimer_head == NULL || uttimer == NULL || time_invtl == 0)
	{

		printf("param error\n");
		return;
	}
	
	pthread_mutex_lock(&uttimer_head->heap_mutex);
	if(is_uttimer_start(uttimer_head, uttimer))
	{
		heap_remove(uttimer_head, uttimer->heap_idx);
	}

	uttimer->trigger_intvl = time_invtl;
	uttimer->trigger_time = get_now_ms() + time_invtl;
	heap_insert(uttimer_head, uttimer);

	/* ����Ķ�ʱ���ڶѶ�ʱ�����ź����ö�ʱ�������߳����µ��� */
	if(uttimer->heap_idx == 1)
	{
		/* �Ƚ����ٷ��źţ�������û�ͷŵ��µ����߳������������߳������л� */		
		pthread_mutex_unlock(&uttimer_head->heap_mutex);
		sem_post(&uttimer_head->uttimer_sem);
		return;
	}
	pthread_mutex_unlock(&uttimer_head->heap_mutex);

	return;
}

void uttimer_stop(uttimer_head_def *uttimer_head, uttimer_event_Def *uttimer)
{
	if(uttimer_head == NULL || uttimer == NULL)
	{

		printf("param error\n");
		return;
	}

	pthread_mutex_lock(&uttimer_head->heap_mutex);
	if(is_uttimer_start(uttimer_head, uttimer))
	{
		/* �ܳ�����˵���ö�ʱ��û�������߳�ռ�ã����Բ��÷��ź���֪ͨ */
		heap_remove(uttimer_head, uttimer->heap_idx);
	}
	pthread_mutex_unlock(&uttimer_head->heap_mutex);

	return;
}


void uttimer_destroy(uttimer_head_def *uttimer_head, uttimer_event_Def *uttimer)
{
	 /* �������Ϸ��� */
	if(uttimer_head == NULL || uttimer == NULL)
	{
		printf("param error\n");
		return;
	}

	uttimer_stop(uttimer_head, uttimer);
	free(uttimer);

	return;
}


uttimer_event_Def *uttimer_create(timer_handle_ptr handle, void *arg, int is_repeat)
{
    uttimer_event_Def *uttimer = NULL;

    /* ���붨ʱ���¼�����ռ� */
    uttimer = (uttimer_event_Def *)malloc(sizeof(uttimer_event_Def));
    if (uttimer == NULL)
    {
        printf("malloc uttimer fail\n");
        return NULL;        
    }

    /* ��ʼ����ʱ����Ϣ */ 
    uttimer->heap_idx = 0;
    uttimer->timer_handle = handle;
    uttimer->arg = arg;
    uttimer->is_repeat = is_repeat;

    return uttimer;
}


static void *uttimer_select_thread(void *arg)
{
	uttimer_head_def *uttimer_head = (uttimer_head_def *)arg;
	uttimer_event_Def *uttimer = NULL;
	llong cur_time;
	struct timespec wait_time;
	int ret;

	pthread_detach(pthread_self());

begin:
	sem_wait(&uttimer_head->uttimer_sem);
	sem_init(&uttimer_head->uttimer_sem, 0, 0);

	while(1)
	{
		/* �Զ�ʱ���ѽ��е���ʱ����ֹ��ʱ�����н��в���ɾ������ */
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
		pthread_mutex_lock(&uttimer_head->heap_mutex);

		/* ��ʱ����Ϊ�գ����������߳� */
		if(uttimer_head->cur_timer_num == 0)
		{
			pthread_mutex_unlock(&uttimer_head->heap_mutex);
			pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
			goto begin;
		}

		uttimer = uttimer_head->heap[1];
		cur_time = get_now_ms();
		if (uttimer->trigger_time <= cur_time)
		{
			if(uttimer->timer_handle)
        		(uttimer->timer_handle)(uttimer->arg);

        	heap_remove(uttimer_head, uttimer->heap_idx);
       
	    	if(uttimer->is_repeat)
	    	{
	    		uttimer->trigger_time += uttimer->trigger_intvl;
	    		heap_insert(uttimer_head, uttimer);
	    	}

			//INVG_LOG_DBG(DBG_UTTIMER, "timer %d triggered, timespan = %d, delay %lld ms\n", 
			//	uttimer->heap_idx, uttimer->trigger_intvl, cur_time - uttimer->trigger_time);

			/* ��ͷ��ʱ���Ѵ����ѷ����˵��������µ��ȶ�ͷ */
	    	pthread_mutex_unlock(&uttimer_head->heap_mutex);
			pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

			continue;
		}
		pthread_mutex_unlock(&uttimer_head->heap_mutex);
		pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

		/* ��ǰʱ��С�ڶ�ͷ��ʱ������ʱ�䣬��ʱ�ȴ� */
        wait_time.tv_sec = uttimer->trigger_time / 1000;
        wait_time.tv_nsec = (uttimer->trigger_time % 1000) * 1000 * 1000;
        ret = sem_timedwait(&uttimer_head->uttimer_sem, &wait_time);
        if(ret == 0)
        {
        	/* �յ��ź�˵����ʱ�����е�����������Ѱ�Ҷ�ͷ */
        	sem_init(&uttimer_head->uttimer_sem, 0, 0);
        	continue;
    	}
	}
}


void uttimer_uninit(uttimer_head_def *uttimer_head)
{
	uttimer_event_Def *uttimer = NULL;

	 /* �������Ϸ��� */
	if(uttimer_head == NULL)
	{
		printf("param error\n");
		return;
	}

	pthread_cancel(uttimer_head->timer_tid);

	while(uttimer_head->cur_timer_num)
	{
		uttimer = uttimer_head->heap[1];
		uttimer_destroy(uttimer_head, uttimer);
	}

	free(uttimer_head->heap);
	free(uttimer_head);
}


uttimer_head_def *uttimer_init(unsigned int max_timer_num)
{
	uttimer_head_def *uttimer_head = NULL;
	int heap_size = 0;
	
	if(max_timer_num <= 0)
	{
		printf("input param invalid: max_timer_num = %d\n", max_timer_num);
		return NULL;
	}

	uttimer_head = (uttimer_head_def *)malloc(sizeof(uttimer_head_def));
	if(uttimer_head == NULL)
	{
		printf("malloc uttimer head fail!\n");
		return NULL;
	}

	sem_init(&uttimer_head->uttimer_sem, 0, 0);
	pthread_mutex_init(&uttimer_head->heap_mutex, NULL);
	
	uttimer_head->max_timer_num = max_timer_num;
	uttimer_head->cur_timer_num = 0;
	heap_size = sizeof(uttimer_event_Def *) * (max_timer_num + 1);	// heap[0]����
	uttimer_head->heap = (uttimer_event_Def **)malloc(heap_size);
	if (NULL == uttimer_head->heap)
    {
        printf("malloc heap space fail");
        free(uttimer_head);
        return NULL;
    }
    memset(uttimer_head->heap, 0, heap_size);
    
    pthread_create(&uttimer_head->timer_tid, NULL, uttimer_select_thread, (void *)uttimer_head);

    return uttimer_head;
	
}


