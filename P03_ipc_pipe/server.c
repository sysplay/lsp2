#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <fcntl.h>
#include "sig.h"
#include "em_registers.h"

#define FIFO_NAME "myfifo"


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

int main()
{
    int fd, num, libcount;
    struct em_registers reg;

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
    
    // TODO 3: Create the FIFO
    
    printf("Waiting for readers ...\n");
    // TODO 4: Open the FIFO
       printf("Got a reader - Sending registers\n");
    // TODO 5: Write EM Registers to the FIFO
       close(fd);

    return 0;
}
