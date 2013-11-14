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
#include <sys/types.h>

void sig_handle(int signal) {
	pid_t pid = getpid();
	printf("handle signal, pid:%d, signal:%d\n", pid, signal);
}

int main(void) {
	signal(SIGPIPE, sig_handle);
    int s, c;
    struct sockaddr_in server_addr, child_addr; 
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
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
        if( fork() == 0 ) {
			pid_t child = getpid();
			printf("In child process :%d\n", child);
			/*
			 * 首先调用close, 然后再注释掉close,调用shutdown
			*/
            close(s); 
            //shutdown(c, SHUT_WR);
            exit(0);
        }
        sleep(5);//让子进程先执行
		pid_t parent = getpid();
		printf("In parent process:%d\n", parent);
		const char *buf = "server parent process send data";
		int n = write(c, buf, strlen(buf));
		close(c);
    }
    return 0;
}
