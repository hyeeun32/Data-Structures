#include "csapp.h"
#include <signal.h>

void echo(int connfd);

int main(int argc, char **argv) {
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;

    signal(SIGPIPE, SIG_IGN);

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    listenfd = open_listenfd(argv[1]);
    if (listenfd < 0) {
        perror("Open_listenfd error");
        exit(1);
    }

    printf("Server listening on port %s...\n", argv[1]);

    while (1) {
        clientlen = sizeof(clientaddr);
        connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
        if (connfd < 0) {
            perror("accept");
            continue;
        }
        printf("Accepted connection: fd=%d\n", connfd);
        echo(connfd);
        Close(connfd);
        printf("Closed connection: fd=%d\n", connfd);
    }
}
void echo(int connfd) {
    rio_t rio;
    char buf[MAXLINE];
    ssize_t n;

    Rio_readinitb(&rio, connfd);
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) > 0) {
        Rio_writen(connfd, buf, n);
    }
    if (n < 0) {
        perror("Rio_readlineb error");
    }
}