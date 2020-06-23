#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MY_SOCK_PATH "/tmp/ns"
#define Q_LEN 50
#define BUF_SIZE 100

static void process_eth(int fd, char *from_socket)
{
    int read_cnt;
    char buf[BUF_SIZE];

    while (1)
    {
        if ((read_cnt = recv(fd, buf, BUF_SIZE, 0)) <= 0)
        {
            printf("Connection from %s went down\n", from_socket);
            break;
        }
        buf[read_cnt - 1] = 0;
        printf("%s: %s\n", from_socket, buf);
    }
}

int main()
{
    int sock_fd;
    struct sockaddr_un my_addr;
    int eth_fd;
    socklen_t sun_size;
    struct sockaddr_un their_addr;

    printf("Creating socket ... ");
    // TODO 1: Create the local socket
    
    printf("done\n");

    // TODO 2: Initialize the fields for my_addr
    //
       printf("Binding socket to %s ... ", MY_SOCK_PATH);
    // TODO 3: Bind socket
    
    printf("done\n");

    printf("Listening on socket ... ");
    // TODO 4: Listen on the socket

    printf("done\n");

    sun_size = sizeof(their_addr);
    printf("Waiting for accepting connections on socket ...\n");
    // TODO 5: Wait for the client to connect
 
    printf("Received a connection through %s. Processing its data ...\n", MY_SOCK_PATH);
    process_eth(eth_fd, MY_SOCK_PATH);
    printf("Done\n");

    close(eth_fd);
    close(sock_fd);

    unlink(MY_SOCK_PATH); // TRY: Comment this to see the socket persistent

    return 0;
}
