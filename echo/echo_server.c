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

void str_echo(int c ) {
    ssize_t n;
    char buf[1024];
    while( (n = read(c, buf, 1024)) > 0 ) {
        write(c, buf, n); 
    }
    printf("client quit.:%d", n);
}

int main() {
    int s, c;
    pid_t child;
    struct sockaddr_in server_addr, child_addr; 
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
    //server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if( (s = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        perror("create socket fail.");
        exit(0);
    }

    if( bind(s, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0 ) {
        perror("bind fail.");
        exit(0); 
    }
    
    if( listen(s, 1024) < 0 ) {
        perror("listen fail.");
        exit(0); 
    }

    printf("start server...\n");
    for (;;) {
        socklen_t clilen = sizeof(child_addr);
        c = accept(s, (struct sockaddr *)&child_addr, &clilen);

        str_echo(c);    
        sleep(10);
        printf("close client.\n");
        close(c);
    }
    exit(0);
}
