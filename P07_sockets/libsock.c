/* This file contains the Socket Layer Wrapper APIs */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>

#define BACKLOG 1
#define BUF_SIZE 256

int open_socket(const char *ip, int port)
{
    int fd;
    int yes;
    struct sockaddr_in my_addr;

    // TODO 1: Get the socket
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        return -1;
    }

    /* Get rid of "address already in use" error message */
    yes = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        perror("setsockopt");
        return -1;
    }
    // TODO 2: Initialize the required fields for my_addr
    my_addr.sin_family = AF_INET; // address family 
    my_addr.sin_port = htons(port); // short, network byte order
    my_addr.sin_addr.s_addr = inet_addr(ip);
    bzero(&(my_addr.sin_zero), 8);

    // TODO 3: Name the socket
    if (bind(fd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("bind");
        close(fd);
        return -1;
    }

    // TODO 4: Listen to the socket
    if (listen(fd, BACKLOG) == -1)
    {
        perror("listen");
        close(fd);
        return -1;
    }

    return fd;
}

void close_socket(int sfd)
{
    close(sfd);
}

int get_socket(int sfd, char *client_ip)
{
    int fd;
    socklen_t sin_size;
    struct sockaddr_in their_addr;

    sin_size = sizeof(struct sockaddr_in);
    // TODO 5: Accept the connections
    if((fd = accept(sfd, (struct sockaddr *) &their_addr, &sin_size)) == -1)
    {
        perror("accept");
        return -1;
    }
    if (client_ip)
    {
        strcpy(client_ip, inet_ntoa(their_addr.sin_addr));
    }

    return fd;
}

void put_socket(int fd)
{
    close(fd);
}

int write_eth(int fd, const void *buf, unsigned int size)
{
    int write_cnt;

    // TODO 6 Send over the socket
    if ((write_cnt = send(fd, buf, size, 0)) == -1)
    {
        perror("send");
    }
    return write_cnt;
}

int read_eth(int fd, void *buf, unsigned int size)
{
    int read_cnt;

    // TODO 7 Receive from the socket
    if ((read_cnt = recv(fd, buf, size, 0)) <= 0)
    {
        if (!read_cnt)
        {
            errno = 0;
        }
        perror("recv");
        return -1;
    }
    return read_cnt;
}
