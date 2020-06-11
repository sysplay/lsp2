#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "sig.h"

void sig(int signum)
{
    printf("Received signal\n");
}

int main()
{
    // TODO 1: Register the handler for SIGINT
    return 0;
}
