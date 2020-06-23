//#define CLEANUP_ZOMBIE

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#ifdef CLEANUP_ZOMBIE
#include <signal.h>
#endif

#include "sock.h"

#define PORT_NUM 2000
#define BUF_SIZE 100

#ifdef CLEANUP_ZOMBIE
static void cleanup_zombie(int sno)
{
	int child_status;

	wait(&child_status);
}
#endif

static void serve_the_eth(int efd, char *from_ip)
{
    int read_cnt;
    char buf[BUF_SIZE];

    while (1)
    {
        if ((read_cnt = read_eth(efd, buf, BUF_SIZE)) <= 0)
        {
            printf("CS: Connection from %s went down\n", from_ip);
            close(efd);
            break;
        }
        buf[read_cnt - 1] = 0;
        printf("CS: %s: %s\n", from_ip, buf);
    }
}

int main(int argc, char *argv[])
{
    int sock_fd;
    char *ip_addr;
    char remote_ip[16];
    int efd;
    pid_t child_pid;

#ifdef CLEANUP_ZOMBIE
    struct sigaction sa;
#endif

    if (argc != 2)
    {
        printf("Usage: %s <ip addr>\n", argv[0]);
        return 1;
    }

    ip_addr = argv[1];

    printf("Creating socket ... ");
    // TODO 1: Open the socket using open_socket

#ifdef CLEANUP_ZOMBIE
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &cleanup_zombie;
    sigaction(SIGCHLD, &sa, NULL);
#endif

    while (1)
    {
        printf("Waiting for accepting connections on socket ...\n");
        // TODO 2: Wait for the client to connect
        if (efd == -1)
            return -1;
        else
        {
            printf("Received a connection from %s\n", remote_ip);
            child_pid = fork();
            // TODO 3: Serve the client in the child process 
            if (child_pid == 0) // Child
            {
                close(sock_fd); // Closing the well-known port
                printf("CS: Concurrent server (%d) started\n", getpid());
                printf("CS: Concurrent server (%d) exited\n", getpid());
                return 0;
            }
            else // Error or Parent 
            {
                if (child_pid < 0)
                {
                    printf("Spawning concurrent server failed. Unable to serve\n");
                }
                close(efd); // Closing the ephemeral port
            }
        }
    }

    close(sock_fd);

    return 0;
}
