#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        printf("socket create edilemedi");
    }

    struct sockaddr_in  server_addr;
    /* Set N bytes of S to 0.  */
    bzero((char *) &server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr=  INADDR_ANY;
    server_addr.sin_port= 0; // this means connect to the first available port!?


    if (bind(sockfd, (struct sockaddr *) & server_addr, sizeof server_addr) < 0) {
        if(errno == EADDRINUSE) {
            printf("the port is not available. already to other process\n");
            return 0;
        } else {
            printf("could not bind to process (%d) %s\n", errno, strerror(errno));
            return 0;
        }
    }

    socklen_t len = sizeof server_addr;
    if (getsockname(sockfd, (struct sockaddr *)&server_addr, &len) == -1) {
        perror("socket name bulunamadı");
        return 0;
    }

    printf("port number %d ile sockfd bind edildi \n", ntohs(server_addr.sin_port));

    void * message = NULL;
    recvfrom(sockfd,message,1024,0,NULL,NULL);




    if (close(sockfd) < 0 ) {
        printf("socket kapatılamadı: %s\n", strerror(errno));
        return;
    }

    return 0;
}
