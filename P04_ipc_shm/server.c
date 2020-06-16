#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <fcntl.h>
#include <sys/shm.h>

#include "sig.h"
#include "em_registers.h"
#include "sem.h"

#define FIFO_NAME "myfifo"
#define KEY 0x12345 // Would retrieve the same if not detached


void sig(int signum)
{
    printf("Received signal %d\n", signum);
}

int get_lib_count()
{
    int libcount;
    // TODO 6: Open the pipe with ls lib*.so and return the lib count
    
    return -1;
}

void *shm_allocate(key_t key, size_t shm_size,
        int flags, int *shm_id, void *addr)
{
    // TODO 7: Allocate the shared memory
    printf("The segment id: %d (0x%X)\n", *shm_id, *shm_id);

    // TODO 8: Attach the shared memory
}

int main()
{
    int fd, libcount;
    struct em_registers reg;
    int shm_id;
    char *shm_addr = NULL;
    const int shm_size = sizeof(struct em_registers);
    int sem_id;

    memset(&reg, 0, sizeof(struct em_registers));
    reg.va = 440;
    reg.vb = 438;
    reg.vc = 430;
    
    // TODO 1: Register handler sig for SIGINT and SIGPIPE

    // TODO 2: Get the count of lib*.so files using pipe
    if (libcount > 0)
    {
        printf("Library count = %d\n", libcount);
    }

    // TODO 9: Allocate the shared memory
    printf("Shared memory attached at address %p\n", shm_addr);

    // TODO 10: Allocate the binary semaphore
    printf("Semaphore created with id: %d\n", sem_id);

    // TODO 11: Initialize the binary semaphore
    printf("1: Semaphore set to 1\n");
    
    // TODO 3: Create the FIFO
    
    printf("Waiting for readers ...\n");
    // TODO 4: Open the FIFO
       printf("Got a reader - Sending registers\n");

    // TODO 12: Get the semaphore
    while (1) 
    {
        // TODO 13: Synchronize the access to shared memory using semaphore
        memcpy(&reg, shm_addr, sizeof(struct em_registers)); 

        // TODO 5: Write EM Registers to the FIFO
        
        sleep(5);
        printf("Sent shared registers\n");
    }
       close(fd);

    return 0;
}
