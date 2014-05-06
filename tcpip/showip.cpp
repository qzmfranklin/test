#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <assert.h>
#include <arpa/inet.h>
/******************************************************************************/ 

struct addrinfo *get_ipaddrinfo_list(const char *inaddr)
{
	struct addrinfo hint;
	memset(&hint,0,sizeof(hint)); 
	hint.ai_family   = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;
	struct addrinfo *res;
	int rval = getaddrinfo(inaddr,NULL,&hint,&res);
	assert(rval==0);
	return res;
}

void print_addrinfo(const struct addrinfo *p)
{
	char ipver[200];
	void * addr;
	int port;
	char addrstr[INET6_ADDRSTRLEN];
	switch (p->ai_family) {
	case AF_INET:
		struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
		addr = &(ipv4->sin_addr);
		inet_ntop(AF_INET,addr,addrstr,INET_ADDRSTRLEN);
		strcpy(ipver,"IPV4");
		port = ipv4->sin_port;
		break;
	case AF_INET6:
		struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
		addr = &(ipv6->sin6_addr);
		inet_ntop(AF_INET6,addr,addrstr,INET6_ADDRSTRLEN);
		strcpy(ipver,"IPV6");
		port = ipv6->sin6_port;
		break;
	default:
		fprintf(stderr,"invalid ip address family, abort\n");
		exit(1);
		break;
	}
	printf("%s[%5d]: %s\n",ipver,port,addrstr);
}

void print_addrinfo_list(struct addrinfo *list)
{
	while (list!=NULL) {
		print_addrinfo(list);
		list = list->ai_next;
	}
}

void print_addr(const char *addr)
{
	struct addrinfo *list = get_ipaddrinfo_list(addr);
	printf("\t\t%s\n",addr);
	print_addrinfo_list(list);
	printf("\n");
	freeaddrinfo(list);
}

int main(int argc, char const* argv[])
{
	char hostname[200];
	gethostname(hostname,200);
	print_addr(hostname);

	printf("Enter the IP address(es) you want to see. ");
	printf("Type \'quit\' to stop testing\n");
	char buf[200];

	while (1) {
		scanf("%s",buf);
		if (strstr(buf,"quit")) break;
		print_addr(buf);
	}

	return 0;
}
