#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "sig.h"
#include "em_registers.h"

#define FIFO_NAME "myfifo"

int main()
{
    int fd;
    struct em_registers reg;

    // TODO 1: Create the FIFO

    printf("Waiting for writers ...\n");
    // TODO 2: Open the FIFO
 
    printf("Got a writer:\n");

    while ((read(fd, &reg, sizeof(struct em_registers))) > 0)
    {
        printf("Va = %u, Vb = %u Vc = %u\n", reg.va, reg.vb, reg.vc);
        printf("Va Max = %u, Vb Max = %u Vc Max = %u\n", reg.va_max, reg.vb_max, reg.vc_max);
    }
   
    close(fd);

    return 0;
}
