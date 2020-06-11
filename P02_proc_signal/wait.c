#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int status, i;

    if (fork() == 0)
    {
        for (i = 0; i < 20; i++)
        {
            sleep(1);
        }
    }
    else
    {
        // TODO 1: Wait for the child process termination
        // TODO 2: Print the exit code, if process exited normally
        // TODO 3: Print the signal number, if process terminated by signals
        printf("\nDone with main program.\n");
    }
    return 0;
}
