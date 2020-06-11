#ifndef SIG_H
#define SIG_H

#include <signal.h>
#include <string.h>

int signal_register(int signum, void (*fun)(int), struct sigaction*oldact, sigset_t *sa_mask); 
int signal_deregister(int signum); 
int signal_restore(int signum, struct sigaction *sa);
int signal_ignore(int signum);
int signal_send(pid_t pid, int signum);

#endif
