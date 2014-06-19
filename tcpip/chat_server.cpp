#include "inet_utils.h"
#define BACKLOG 3

static void perr(const char * msg)
{
	fprintf(stderr,"%s\n",msg);
	exit(1);
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

	// do something here
	char buf[BUFSIZ];
	strcpy(buf,"Hello!");
	int len=sizeof("Hello!");
	write(fd,buf,len);

	sleep(10);

	close(fd);
	
	return 0;
}
