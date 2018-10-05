#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include <time.h>

#define SERVPORT        2000
#define MAXLINE         4096
#define LISTENQ         10

void str_serv(int sockfd)
{
    //code for data sending recieving on server side
}

int main(int argc, char **argv)
{
    int             listenfd, connfd;
    pid_t               childpid;
    socklen_t           clilen;
    struct sockaddr_in  cliaddr, servaddr;
    //tcp connection
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket error"); 
        exit(1);
    }
    //zeroising servaddr structure
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(SERVPORT);
    //binding listenfd to servaddr
    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1){
        perror("bind error");
        exit(1);
    }
    //start listening
    if ((listen(listenfd, LISTENQ)) == -1){
        perror("listen error");
        exit(1);
    }

    //working with child processes--concurrent server
    for( ; ; ) {
        clilen = sizeof(cliaddr);
        if ((connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen)) == -1) 
            perror("accept error");

        if ( (childpid = fork()) == 0) {  /* child process */
            close(listenfd);    /* close listening socket */
        str_serv(connfd);   /* process the request */
        exit(0);
        }
        close(connfd);       /* parent closes connected socket */
    }
}


