#include "csapp.h"

void echo(int connfd);

int main(int argc, char **argv)
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    listenfd = open_listenfd(atoi(argv[1]));

    while (1)
    {
        clientlen = sizeof(clientaddr);
        connfd = accept(listenfd, (SA *)&clientaddr, &clientlen);
        echo(connfd);
        Close(connfd);
    }
}

void echo(int connfd)
{
    rio_t rio;
    char buf[MAXLINE];

    Rio_readinitb(&rio, connfd);
    while (Rio_readlineb(&rio, buf, MAXLINE) != 0)
        Rio_writen(connfd, buf, strlen(buf));
}