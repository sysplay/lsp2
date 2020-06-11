#include "sig.h"

int signal_register(int signum, void (*fun)(int), struct sigaction *oldact, 
                        sigset_t *sa_mask) 
{
    // TODO 1: Register the signal handler and save the current behaviour in oldact
    return 0;
}

int signal_deregister(int signum) 
{
    // TODO 2: Reset the behaviour to SIG_DFL
    return 0;
}

int signal_restore(int signum, struct sigaction *sa)
{
    // TODO 3: Restore the behaviour as per sa
    return 0;
}

int signal_ignore(int signum) 
{
    // TODO 4: Ignore the signal
    return 0;
}

int signal_send(pid_t pid, int signum)
{
    // TODO 5: Send the signal to the process 
    return 0;
}
