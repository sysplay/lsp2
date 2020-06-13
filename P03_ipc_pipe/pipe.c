#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void writer(const char *message, int count, int fd)
{
    int len = strlen(message);
    for(; count > 0; --count)
    {
        if (write(fd, message, len) < 0)
        {
            printf("Unable to write\n");
            return;
        }
        sleep(2);
    }
}

void reader(int fd)
{
    char buffer[1024];
    while (read(fd, buffer, sizeof(buffer)) > 0)
        printf("%s", buffer);
}

int main()
{
    int fds[2];
    pid_t pid;
    
    // TODO 1: Create the pipe

    // TODO 2: Create the new process

    // TODO 3: Make a child read from the pipe

    // TODO 4: Make a parent to write to pipe
    
    return 0;
}
