#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/* Allocate a temporary buffer */
void *allocate_buffer(size_t size)
{
    printf("Resource Allocated\n");
    return malloc(size);
}
/* Deallocate a temporary buffer.  */
void deallocate_buffer(void *buffer)
{
    free(buffer);
    printf("\nResource Freed\n");
}
void *do_some_work(void *p)
{
    /* Allocate a temporary buffer.  */
    void *temp_buffer = allocate_buffer(1024); // Is it the right place???
    int i;

    // pthread_exit(NULL); // TRY: Uncomment to see no handler invocation
    // TODO 3: Register the clean up handler to deallocate the buffer
    //
    // pthread_exit(NULL); // TRY: Uncomment to see the handler invocation
    /* Do some work here that might call pthread_exit or might be cancelled */
    for (i = 0; i < 10; i++)
    {
        fputc('c', stderr);	
        fflush(stderr);
        sleep(1);
    }
    // TODO 4: Unregister the clean up handler to deallocate the buffer
    return NULL;
}

int main()
{
    pthread_t thread_id;
    void *status;

    pthread_create(&thread_id, NULL, &do_some_work, NULL);
    sleep(3);
    // TODO 1: Cancel the thread
    // TODO 2: Join the thread & check the status
    if (status == PTHREAD_CANCELED)
    {
        printf("Thread was cancelled\n");
    }
    else
    {
        printf("Thread terminated normally\n");
    }

    return 0;
}
