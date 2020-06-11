#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int status, w, pid;

    if ((pid = fork()) == 0)
    {
        pause();
    }
    else
    {
        do {
            // TODO 1: Wait for the child with waitpid
            // Make sure to include WUNTRACED and WCONTINUE options
            // TODO 2: Check if exited normally or abnormally and print status accordingly
            // TODO 3: Check for the stop and continue signals

            } while (!WIFEXITED(status) && !WIFSIGNALED(status));

        printf("\nDone with main program.\n");
    }
    return 0;
}
