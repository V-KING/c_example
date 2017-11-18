#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#define CONSUMER_COUNT 1        /* 1个消费者线程 */
#define PRODUCER_COUNT 3        /* 3个生产者线程 */
#define BUFFERSIZE 10

int g_buffer[BUFFERSIZE];

unsigned short in = 0;
unsigned short out = 0;

pthread_mutex_t g_mutex;

typedef struct
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} Condition;

Condition not_empty = {PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER};
Condition not_full = {PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER};

int nready;             /* 可以消费的产品数量 */

pthread_t g_thread[CONSUMER_COUNT + PRODUCER_COUNT];    /* 存放生产者和消费者的线程号 */

void* consumer(void* arg)
{
    int num = (int)arg;
    /* 不断消费 */
    while (1)
    {
        pthread_mutex_lock(&g_mutex);
        
        /* 打印仓库当前状态，(为了便于比较，这段打印临界区依然只使用互斥锁保护)
         * */
        int i;
        for (i = 0; i < BUFFERSIZE; i++) 
        {
            if (g_buffer[i] == -1)
                printf("g_buffer[%d] = %s\n", i, "null");
            else
                printf("g_buffer[%d] = %d\n", i, g_buffer[i]);
            
            if (i == out)
                printf("g_buffer[%d]可以消费\n", i);
        }
        
        pthread_mutex_unlock(&g_mutex);
        
        /* 消费产品
         * */
        pthread_mutex_lock(&not_empty.mutex);
        
        while (nready == 0)
            pthread_cond_wait(&not_empty.cond, &not_empty.mutex);
        printf("thread %d 开始消费产品 %d\n", num, g_buffer[out]);
        sleep(4);       /* 消费一个产品需要4秒 */
        g_buffer[out] = -1;
        printf("消费完毕\n");
        --nready;
        out = (out + 1) % BUFFERSIZE;
        
        pthread_cond_signal(&not_full.cond);
        pthread_mutex_unlock(&not_empty.mutex);
    }
    
    return NULL;
}

void* producer(void* arg)
{
    int num = (int)arg;
    /* 不断生产 */
    while (1)
    {
        pthread_mutex_lock(&g_mutex);
        
        /* 打印仓库当前状态
         * */
        int i;
        for (i = 0; i < BUFFERSIZE; i++)
        {
            if (g_buffer[i] == -1)
                printf("g_buffer[%d] = %s\n", i, "null");
            else
                printf("g_buffer[%d] = %d\n", i, g_buffer[i]);
            
            if (i == in)
                printf("g_buffer[%d]可以生产\n", i);
        }
        
        pthread_mutex_unlock(&g_mutex);
        
        /* 生产产品
         * */
        pthread_mutex_lock(&not_full.mutex);
        
        while (nready == BUFFERSIZE)
            pthread_cond_wait(&not_full.cond, &not_full.mutex);
        g_buffer[in]++;
        printf("thread %d 开始生产产品 %d\n", num, g_buffer[in]);
        sleep(2);       /* 生产一个产品需要2秒 */
        printf("生产完毕\n");
        ++nready;
        in = (in + 1) % BUFFERSIZE;
        
        pthread_cond_signal(&not_empty.cond);
        pthread_mutex_unlock(&not_full.mutex);
    }
    
    return NULL;
}

int main(void)
{
    /* 初始化仓库 */
    int i;
    for (i = 0; i < BUFFERSIZE; i++)
        g_buffer[i] = -1;
    
    /* 创建消费者线程，线程号为：[0, CONSUMER_COUNT) */
    for (i = 0; i < CONSUMER_COUNT; i++)
    {
        pthread_create(&g_thread[i], NULL, consumer, (void*)i);
    }
    
    /* 创建生产者线程，线程号为：[CONSUMER_COUNT,
     * CONSUMER_COUNT + PRODUCER_COUNT) */
    for (i = 0; i < PRODUCER_COUNT; i++)
    {
        pthread_create(&g_thread[i + CONSUMER_COUNT], NULL, producer, (void*)(i + CONSUMER_COUNT));
    }
    
    /* 等待创建的所有线程退出 */
    for (i = 0; i < CONSUMER_COUNT + PRODUCER_COUNT; i++)
    {
        pthread_join(g_thread[i], NULL);
    }
    
    return 0;
}

// output is the same as above
