#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "unp.h"
int main(int argc, char** argv) {

    int sockfd, n;
    int port = 13;
    char recvline[MAXLINE];

    struct sockaddr_in servaddr;

    if(argc != 2) {
      err_sys("usage: a.out <IPADDRESS>");
    }
    //create a socket to the server.
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
      err_sys("socket error");
    }

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);

    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);


    // make a connection to the server.
    if( connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0) {
      err_sys("connect error");
    }


    // Read the response.
    //
    while((n = read(sockfd, recvline, MAXLINE)) > 0) {
         recvline[n] = '\n';

         if(fputs(recvline, stdout) == EOF) {
            err_sys("fputs error");
         }
    }

    if(n < 0) {
      err_sys("read error");
    }

    exit(0);
}
