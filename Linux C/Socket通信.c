#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/shm.h>

#define QUEUE 20
#define BUFFER_SIZE 1024
// char buffer[BUFFER_SIZE];
#define err(fmt, args...) printf("[%s][Conan] err: " fmt, __FUNCTION__, ##args) /*debug function */
#define dbg(fmt, args...) printf("[%s][Conan] dbg: " fmt, __FUNCTION__, ##args) /*debug function */

static int serv_sock = 0, clnt_sock = 0, clnt_conn = 0;

int server_init(char *ip, int port)
{
    // 创建套接字
    serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP /*0*/);

    // 将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;            // 使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr(ip); // 具体的IP地址
    serv_addr.sin_port = htons(port);          // 端口

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        err("bind error\n");
        return -1;
    }
    // 进入监听状态，等待用户发起请求
    if (listen(serv_sock, QUEUE) < 0)
    {
        err("listen start error\n");
        return -1;
    }

    // 接收客户端请求
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
    if (clnt_sock < 0)
    {
        err("accept error\n");
        return -1;
    }

    return 0;
}

int server_send()
{
    // 向客户端发送数据
    char buffer[] = "Hello, this is server";
    // write(clnt_sock, str, sizeof(str));
    // memset(buffer,0,sizeof(buffer));
    return send(clnt_sock, buffer, sizeof(buffer), 0);
}

int server_rev()
{
    // 从客户端接收数据
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    recv(clnt_sock, buffer, sizeof(buffer), 0);
    dbg("server get: %s\n", buffer);
    return 0;
}

int client_init(char *ip, int port)
{
    // 创建套接字
    clnt_conn = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP /*0*/);

    // 向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;            // 使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr(ip); // 具体的IP地址
    serv_addr.sin_port = htons(port);          // 端口
    connect(clnt_conn, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (clnt_conn < 0)
    {
        err("accept error\n");
        return -1;
    }

    return 0;
}

int client_send()
{
    // 向服务器发送数据
    char buffer[] = "Hello, this is client";
    // write(clnt_sock, str, sizeof(str));
    // memset(buffer,0,sizeof(buffer));
    return send(clnt_conn, buffer, sizeof(buffer), 0);
}

int client_rev()
{
    // 从服务器接收数据
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    recv(clnt_conn, buffer, sizeof(buffer), 0);
    dbg("client get: %s\n", buffer);
    return 0;
}

int socket_close()
{
    // 关闭套接字
    if (clnt_sock > 0)
        close(clnt_sock);
    if (serv_sock > 0)
        close(serv_sock);
    if (clnt_conn > 0)
        close(clnt_conn);
    return 0;
}

int main()
{

#if 1
    client_init("192.168.0.10", 8384);
    while (1)
    {
        client_send();
        client_rev();
        sleep(3);
    }
    socket_close();
#else
    server_init("192.168.0.85", 8384);
    while (1)
    {
        server_send();
        server_rev();
        sleep(3);
    }
#endif