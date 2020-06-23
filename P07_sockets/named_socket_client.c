#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MY_SOCK_PATH "/tmp/ns"
#define BUF_SIZE 100

static void transmit_eth(int fd)
{
    int read_cnt, write_cnt;
    char buf[BUF_SIZE];

    while (1)
    {
        printf("Enter string to be transmitted (^D to exit): ");
        read_cnt = scanf("%[^\n]%*c", buf);
        if (read_cnt == EOF)
        {
            break;
        }
        if (read_cnt == 0)
        {
            scanf("%*c");
            buf[0] = 0;
        }
        if ((write_cnt = send(fd, buf, strlen(buf) + 1, 0)) == -1)
            // May generate SIGPIPE, if server closes the connection
        {
            perror("send");
        }
    }
}

int main()
{
    int sock_fd;
    struct sockaddr_un my_addr;

    printf("Creating socket ... ");
    // TODO 1: Create AF_UNIX socket

    printf("done\n");

    // TODO 2: Initialize the fields for my_addr

    printf("Connecting socket to %s ... ", MY_SOCK_PATH);
    // TODO 3: Connect to the socket
    
    printf("done\n");

    transmit_eth(sock_fd);

    close(sock_fd);

    return 0;
}
