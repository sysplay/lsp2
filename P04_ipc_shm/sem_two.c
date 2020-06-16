#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "sem.h"

#define SEGMENT_SIZE 0x400

int main()
{
    key_t key = 0x12345; // Using same for both shm & sem
    int segment_id;
    char *shared_memory;
    int sem_id;

    // TODO 1: Allocate shared memory segment using shmget
    printf("1: Allocated a shared segment\n");

    // TODO 2: Attach shared memory segment
    printf("2: Mapped shared memory at address %p\n", shared_memory);

    // TODO 3: Allocate the binary semaphore
    
    // TODO 4: Invoke wait
    printf("3: Wait call returned\n");

    /* Print out the string from shared memory */
    printf("4: Shared memory has \"%s\"\n", shared_memory);

    /* Write a string to the shared memory segment */
    sprintf(shared_memory, "I am fine. How r u?");
    printf("2: Message posted and timepass for a 6 secs\n");
    sleep(6);

    // TODO 5: Invoke post
    printf("5: Post call returned\n");

    // TODO 6: De-allocate the semaphore
    printf("6: Semaphore freed\n");

    // TODO 7: Detach the shared memory
    printf("7: Unmapped shared memory\n");
    sleep(2);

    // TODO 8: Deallocate the shared memory segment
    printf("8: Finally deallocated the shared memory\n");

    return 0;
}
