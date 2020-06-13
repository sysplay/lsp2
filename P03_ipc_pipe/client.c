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

    if ((read(fd, &reg, sizeof(struct em_registers))) > 0)
    {
        printf("Va = %u, Vb = %u Vc = %u\n", reg.va, reg.vb, reg.vc);
    }
   
    close(fd);

    return 0;
}
