/*
 * Example code for using pthreads condition variables. The main thread creates
 * three threads. Two of those threads increment a "count" variable, while the
 * third thread watches the value of "count". When "count" reaches a predefined
 * limit, the waiting thread is signaled by one of the incrementing threads. The
 * waiting thread "awakens" and then modifies count. The program continues until
 * the incrementing threads reach TCOUNT. The main program prints the final
 * value of count.
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS  3
#define TCOUNT 10
#define COUNT_LIMIT 12

static int count = 0;
static pthread_mutex_t count_mutex;

void *inc_count(void *t) 
{
    int i;
    long my_id = (long)t;

    for (i = 0; i < TCOUNT; i++)
    {
        pthread_mutex_lock(&count_mutex);
        count++;
        pthread_mutex_unlock(&count_mutex);

        /* Do some work so threads can alternate on mutex lock */
        sleep(1);
    }
    pthread_exit(NULL);
}

void *watch_count(void *t) 
{
    long my_id = (long)t;

    printf("Starting watch_count(): thread %ld\n", my_id);

    while (1) {
        pthread_mutex_lock(&count_mutex);
        if (count < COUNT_LIMIT)
        {
            pthread_mutex_unlock(&count_mutex);
            continue;
        }
        printf("watch_count(): thread %ld. Count now = %d\n", my_id, count);
        pthread_mutex_unlock(&count_mutex);
        break;
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int i, rc; 
    long t1 = 1, t2 = 2, t3 = 3;
    pthread_t threads[3];

    /* Initialize mutex and condition variable objects */
    pthread_mutex_init(&count_mutex, NULL);

    pthread_create(&threads[0], NULL, &watch_count, (void *)t1);
    pthread_create(&threads[1], NULL, &inc_count, (void *)t2);
    pthread_create(&threads[2], NULL, &inc_count, (void *)t3);

    /* Wait for all threads to complete */
    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    printf("main(): Waited on %d threads. Final value of count = %d. Done.\n", 
            NUM_THREADS, count);

    /* Clean up and exit */
    pthread_mutex_destroy(&count_mutex);
    return 0;
}
