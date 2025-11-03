#include "csapp.h"

int main(int argc, char **argv)
{
    int clientfd;
    rio_t rio;
    char buf[MAXLINE];

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
        exit(1);
    }

    clientfd = open_clientfd(argv[1], atoi(argv[2]));
    Rio_readinitb(&rio, clientfd);

    while (fgets(buf, MAXLINE, stdin) != NULL)
    {
        Rio_writen(clientfd, buf, strlen(buf));
        Rio_readlineb(&rio, buf, MAXLINE);
        printf("%s", buf);
    }

    Close(clientfd);
    return 0;
}