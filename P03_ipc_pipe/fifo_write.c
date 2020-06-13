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
    int fd, ret, num;

    // TODO 1: Create FIFO using the system call

    printf("Waiting for readers ...\n");
    // TODO 2: Open the FIFO for write only 
    printf("Got a reader - Type some stuff\n");

    while ((ret = scanf("%[^\n]%*c", s)), !feof(stdin)) 
    {
        if (ret == 0) // No input read - remove the newline
        {
            getchar();
            continue;
        }
        if ((num = write(fd, s, strlen(s))) == -1)
        {
            perror("write");
        }
        else
        {
            printf("speak: wrote %d bytes\n", num);
        }
    }

    close(fd);

    return 0;
}
