/* 
 * Copyright (c)2014 
 * All rights reserved 
 * http://blog.csdn.net/ezhou_liukai 
 */  
  
#include <stdio.h>  
#include <pthread.h>  
#include <unistd.h>  
  
pthread_mutex_t g_mutex;  
int g_nflag1, g_nflag2;  
static pthread_cond_t g_cond1 = PTHREAD_COND_INITIALIZER;  
static pthread_cond_t g_cond2 = PTHREAD_COND_INITIALIZER;  
void suspend(int n)  
{  
    pthread_mutex_lock(&g_mutex);  
    switch (n)  
    {  
    case 1:  
          g_nflag1--;  
          break;  
    case 2:  
          g_nflag2--;  
          break;  
    default:  
          break;  
    }  
    pthread_mutex_unlock(&g_mutex);  
}  
  
void resume(int n)  
{  
    pthread_mutex_lock(&g_mutex);  
    switch (n)  
    {  
        case 1:  
            g_nflag1++;  
            pthread_cond_signal(&g_cond1);  
            break;  
        case 2:  
            g_nflag2++;  
            pthread_cond_signal(&g_cond2);  
            break;  
        default:  
            break;  
    }  
     
    pthread_mutex_unlock(&g_mutex);  
}  
  
  
void *thr_fn1(void *arg)  
{     
   for (int i = 0; i< 10; i++)  
   {  
       sleep(1);  
       pthread_mutex_lock(&g_mutex);  
       while (g_nflag1 <= 0)  
       {  
           pthread_cond_wait(&g_cond1, &g_mutex);  
       }  
       pthread_mutex_unlock(&g_mutex);  
  
       printf("Thread_ID: %u , i = %d\n", (unsigned int)pthread_self(), i);  
   }  
}  
  
void *thr_fn2(void *arg)  
{  
    for (int i = 0; i < 10; i++)  
    {  
        sleep(1);  
        pthread_mutex_lock(&g_mutex);  
        while (g_nflag2 <= 0)  
        {  
            pthread_cond_wait(&g_cond2, &g_mutex);  
        }  
        pthread_mutex_unlock(&g_mutex);  
        printf("Thread_ID: %u, i = %d\n", (unsigned int)pthread_self(), i);  
    }  
}  
  
int main(void)  
{  
    pthread_mutex_init(&g_mutex, NULL);  
    g_nflag1 = 1;  
    g_nflag2 = 1;  
    pthread_t tid1,tid2;  
    pthread_setconcurrency(3);  
    pthread_create(&tid1, NULL, &thr_fn1, NULL);  
    pthread_create(&tid2, NULL, &thr_fn2, NULL);  
    sleep(2.1);  
    suspend(2);  
    sleep(5.1);  
  
    resume(2);  
    suspend(1);  
    pthread_cancel(tid1);      
    pthread_join(tid1, NULL);  
    pthread_join(tid2, NULL);  
    return 1;  
}  
