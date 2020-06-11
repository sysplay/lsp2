#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "sig.h"

sig_atomic_t sigintcnt = 0;

void handler(int signum)
{
    ++sigintcnt;
    if (signum == SIGUSR1)
    {
        printf("Sleeping ...\n");
        sleep(10);
        printf("Done\n");
    }
}

int main()
{
    sigset_t sa_mask;
    // TODO 1: Register handler for SIGINT
 
    // TODO 2: Add SIGINT to sa_mask;

    // TODO 3: Register same handler for SIGUSR1 as well and pass &sa_mask as arg
    
    for(;;)
    {
        printf("Signal Count: %d\n", (int)sigintcnt);	
        sleep(5); // Would return when signalled
    }
    return 0;
}
