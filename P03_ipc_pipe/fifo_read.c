#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "myfifo"

int main()
{
    char s[300];
    int num, fd;

    // TODO 1: Create FIFO using the system call
    
    printf("Waiting for writers ...\n");
    // TODO 2: Open the FIFO for read only 
    printf("Got a writer:\n");

    do
    {
        if ((num = read(fd, s, 300)) == -1)
        {
            perror("read");
        }
        else
        {
            s[num] = '\0';
            printf("tick: read %d bytes: \"%s\"\n", num, s);
        }
    }
    while (num > 0);

    close(fd);

    return 0;
}
