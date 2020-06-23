#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "sock.h"

#define PORT_NUM 2000
#define Q_LEN 1
#define BUF_SIZE 100

static void process_eth(int fd, char *from_ip)
{
    int read_cnt;
    char buf[BUF_SIZE];

    while (1)
    {
        if ((read_cnt = read_eth(fd, buf, BUF_SIZE)) <= 0)
        {
            printf("Connection from %s went down\n", from_ip);
            break;
        }
        buf[read_cnt - 1] = 0;
        printf("%s: %s\n", from_ip, buf);
    }
}

int main(int argc, char *argv[])
{
    int sock_fd;
    char *ip_addr;
    int eth_fd;
    char remote_ip[16];

    if (argc != 2)
    {
        printf("Usage: %s <ip addr>\n", argv[0]);
        return 1;
    }

    ip_addr = argv[1];

    printf("Opening socket ... ");
    if ((sock_fd = open_socket(ip_addr, PORT_NUM)) == -1)
    {
        perror("socket");
        return 2;
    }
    printf("Waiting for accepting connections on socket ...\n");
    if ((eth_fd = get_socket(sock_fd, remote_ip)) == -1)
    {
        close(sock_fd);
        return -1;
    }
    process_eth(eth_fd, remote_ip);

    close(eth_fd);
    close(sock_fd);

    return 0;
}
