#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>

// TODO 1: Obtain a binary semaphore id, allocating if necessary
int binary_semaphore_allocate(key_t key, int sem_flags)
{
    return 0;
}

// TODO 2: Deallocate a binary semaphore
int binary_semaphore_deallocate(int semid)
{
    return 0;
}

// TODO 3: Obtain a pre-existing binary semaphore
int binary_semaphore_get(key_t key, int sem_flags)
{
    return 0;
}

// TODO 4: Initialize a binary semaphore with a value of 1
int binary_semaphore_set(int semid)
{
    return 0;
}

// TODO 5: Wait for the binary semaphore. Decrement the value by -1
int binary_semaphore_wait(int semid)
{
    struct sembuf operations[1];

    /* Use the first (and only) semaphore. */
    /* Decrement by 1. */
    /* Permit undoing. */
    /* Perform the operation with semop*/
    return 0;
}

// TODO 6: Post to a binary semaphore: Increment its value by 1
int binary_semaphore_post(int semid)
{
    struct sembuf operations[1];

    /* Use the first (and only) semaphore. */
    /* Increment by 1. */
    /* Permit undoing. */
    /* Perform the operation with semop*/
    return 0;
}
