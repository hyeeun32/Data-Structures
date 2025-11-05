#include "csapp.h"

int main(int argc, char **argv) {
    int clientfd;
    rio_t rio;
    char buf[MAXLINE];

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
        exit(1);
    }

    clientfd = open_clientfd(argv[1], argv[2]);
    if (clientfd < 0) { 
        fprintf(stderr, "Connection failed\n"); 
        exit(1); 
    }

    Rio_readinitb(&rio, clientfd);

    while (fgets(buf, MAXLINE, stdin) != NULL) {
        Rio_writen(clientfd, buf, strlen(buf));
        if (Rio_readlineb(&rio, buf, MAXLINE) <= 0) {
            fprintf(stderr, "Server closed connection\n");
            break;
        }
        printf("%s", buf);
    }

    Close(clientfd);
    return 0;
}