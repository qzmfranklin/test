#include "inet_utils.h"
#include <signal.h>
#define BACKLOG 3

static void perr(const char * msg)
{
	fprintf(stderr,"%s\n",msg);
	exit(1);
}

static void sigchld_handler(int s)
{
	while(waitpid(-1, NULL, WNOHANG) > 0);
}

int main(int argc, char const* argv[])
{
	if (argc<2) perr("usage: chat_server [port]");

	struct addrinfo *plist = 
		get_addrinfo_list("localhost",argv[1],SOCK_STREAM);
	int fd = try_bind(plist);
	if (fd==-1) perr("Cannot bind socket to port");

	freeaddrinfo(plist);

	if (listen(fd,BACKLOG)==-1) {
		perror("listen");
		exit(1);
	}

	struct sigaction sa;
	sa.sa_handler = sigchld_handler; 
	sa.sa_flags   = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGCHLD,&sa,NULL)==-1) {
		perror("sigaction");
		exit(1);
	}

	// start a thread to monitor stdin for user input here: TODO

	while(1) {
		struct sockaddr_storage skaddr;
		socklen_t addr_len;
		int client_fd = accept(fd,(struct sockaddr *)&skaddr,&addr_len);
		if (fd==-1) {
			perror("accept");
			exit(1);
		}

		char addrstr[INET6_ADDRSTRLEN];
		get_ipaddrstr(&skaddr,addrstr);
		printf("server: got connection from %s\n",addrstr);

		int pid=fork();
		if (pid<0) {
			perror("fork");
			exit(1);
		} else if (pid==0) { 
			// child
			close(fd);

			// do something
			write(client_fd,"Hello!",6);

			close(client_fd);
			exit(0);
		}

		// parent
		close(client_fd);
	}

	return 0;
}
