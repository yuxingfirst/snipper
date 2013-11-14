#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <errno.h>
#include <error.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>

void str_cli(FILE *fp, int sfd ) {
    char recvbuf[1024];	
    while( read(sfd, recvbuf, 1024) > 0 ) {
        fputs(recvbuf, stdout);
    }
	printf("server send fin.\n");
}

int main(void) {
    int s;
    if( (s = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        int e = errno; 
        perror("create socket fail.\n");
        exit(0);
    }
    struct sockaddr_in server_addr, child_addr; 
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    if( connect(s, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0 ) {
        perror("connect fail."); 
        exit(0);
    }
    str_cli(stdin, s);
	return 0;
}
