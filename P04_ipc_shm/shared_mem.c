#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/stat.h>

#define KEY IPC_PRIVATE // 0x12345 // Would retrieve the same if not detached

int main()
{
    int segment_id;
    char *shared_memory;
    struct shmid_ds shmbuffer;
    int segment_size;
    const int shared_segment_size = 0x6400;

    // TODO 1: Allocate shared memory segment using shmget
    printf("The segment id: %d (0x%X)\n", segment_id, segment_id);

    // TODO 2: Attach shared memory segment
    printf("Shared memory attached at address %p\n", shared_memory);

    // TODO 3: Determine the segment's size
    printf("Segment size: %d (0x%X) bytes\n", segment_size, segment_size);

    /* Write a string to the shared memory segment */
    sprintf(shared_memory, "Hello World");
    printf("Wrote \"Hello World\" into it\n");
    // TODO 4: Detach the shared memory segment
    printf("Shared memory detached\n");

    // TODO 5: Reattach the shared memory segment, at 0x50000000
    printf("Shared memory reattached at address %p\n", shared_memory);
    /* Print out the string from shared memory */
    printf("It contains: %s\n", shared_memory);
    // TODO 6: Detach the shared memory segment
    printf("Shared memory detached\n");
    // TODO 7: Deallocate the shared memory segment

    return 0;
}
