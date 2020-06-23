#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT_NUM 2000
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

int main(int argc, char *argv[])
{
    int sock_fd;
    char *ip_addr;
    struct sockaddr_in my_addr;
    socklen_t my_addr_len = sizeof(my_addr);

    if (argc != 2)
    {
        printf("Usage: %s <server ip addr>\n", argv[0]);
        return 1;
    }

    ip_addr = argv[1];

    printf("Creating socket ... ");
    // TODO 1: Create the socket using socket
    
    printf("done\n");

    // TODO 2: Initialize the required fields for my_addr
   
    printf("Connecting socket to %s ... ", ip_addr);
    // TODO 3: Connect to the socket

    printf("done\n");

    if (getsockname(sock_fd, (struct sockaddr *)&my_addr, &my_addr_len) == -1)
    {
        perror("getsockname");
    }
    else
    {
        printf("Got (ephemeral) Port # %hu on IP %s\n",
                ntohs(my_addr.sin_port), inet_ntoa(my_addr.sin_addr));
    }

    transmit_eth(sock_fd);

    close(sock_fd);

    return 0;
}
