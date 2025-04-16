#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <linux/types.h>
#include <netinet/in.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/shm.h>
#include <sys/ioctl.h>

char *get_IP()
{
    int i, sockfd;
    struct ifconf ifconf;
    char buf[SOCKET_BUFFER_SIZE];
    struct ifreq *ifreq;
    char *ip = "";

    ifconf.ifc_len = SOCKET_BUFFER_SIZE;
    ifconf.ifc_buf = buf;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        err("new socket fail\n");
        return NULL;
    }
    ioctl(sockfd, SIOCGIFCONF, &ifconf);
    close(sockfd);

    ifreq = (struct ifreq *)buf;
    for (i = (ifconf.ifc_len / sizeof(struct ifreq)); i > 0; i--)
    {
        ip = inet_ntoa(((struct sockaddr_in *)&(ifreq->ifr_addr))->sin_addr);
        if (strcmp(ip, "127.0.0.1") == 0)
        {
            ifreq++;
            continue;
        }
        return ip;
    }
    return NULL;
}