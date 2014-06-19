#include "inet_utils.h"

struct addrinfo *get_addrinfo_list( 
		const char *addr, 
		const char *port,
		const int socktype)
{
	struct addrinfo hint;
	hint.ai_family   = AF_UNSPEC;
	hint.ai_socktype = socktype;
	struct addrinfo *res;
	int rval = getaddrinfo(addr,port,&hint,&res);
	if (rval) {
		perror("getaddrinfo");
		exit(1);
	}
	return res;
}

struct addrinfo *get_addrinfo_list_server( 
		const char *addr, 
		const char *port,
		const int socktype)
{
	struct addrinfo hint;
	hint.ai_family   = AF_UNSPEC;
	hint.ai_socktype = socktype;
	hint.ai_flags    = AI_PASSIVE; // passive open
	struct addrinfo *res;
	int rval = getaddrinfo(addr,port,&hint,&res);
	if (rval) {
		perror("getaddrinfo");
		exit(1);
	}
	return res;
}


static struct sockaddr_in *ipv4;
static struct sockaddr_in6 *ipv6;
void print_addrinfo(const struct addrinfo *p)
{
	char ipver[200];
	void *addr;
	int  port;
	char addrstr[INET6_ADDRSTRLEN];
	switch (p->ai_family) {
	case AF_INET:
		ipv4 = (struct sockaddr_in *)p->ai_addr;
		addr = &(ipv4->sin_addr);
		inet_ntop(AF_INET,addr,addrstr,INET_ADDRSTRLEN);
		strcpy(ipver,"IPV4");
		port = ipv4->sin_port;
		break;
	case AF_INET6:
		ipv6 = (struct sockaddr_in6 *)p->ai_addr;
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

int try_connect(struct addrinfo *plist)
{
	int fd;
	struct addrinfo *p;
	for(p=plist; p!=NULL; p=p->ai_next) {
		fprintf(stderr,"Connecting to:    ");
		print_addrinfo(p);
		fd = socket(p->ai_family,p->ai_socktype,p->ai_protocol);
		if (fd==-1) { 
			perror("try_connect: socket"); 
			continue; 
		}
		int err = connect(fd,p->ai_addr,p->ai_addrlen);
		if (err==-1) {
			perror("try_connect: connect");
			continue;
		}
		break; // if reach here, must have succeded
	}
	if (p==NULL) 
		fd=-1;
	else 
		fprintf(stderr,"Connected\n");
	return fd;
}

int try_bind(struct addrinfo *plist)
{
	int fd;
	struct addrinfo *p;
	for(p=plist; p!=NULL; p=p->ai_next) {
		fd = socket(p->ai_family,p->ai_socktype,p->ai_protocol);
		if (fd==-1) {
			perror("try_bind: socket");
			continue;
		}
		int yes=1;
		if (setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,
					&yes,sizeof(int))==-1) {
			perror("try_bind: setsockopt");
			continue;
			//exit(1);
		}
		if (bind(fd,p->ai_addr,p->ai_addrlen)==-1) {
			close(fd);
			perror("try_bind: bind");
			continue;
		}
		break;
	}
	if (p==NULL) 
		fd=-1;
	else 
		fprintf(stderr,"Bound\n");
	return fd;
}

int pollerr(const int revents)
{
	int err=-1;
	if (revents & POLLHUP)
		fprintf(stderr,"Remote connection closed\n");
	else if (revents & POLLERR)
		fprintf(stderr,"Socket error\n");
	else if (revents & POLLNVAL)
		fprintf(stderr,"Invalid fd\n");
	else
		err=0;
	return err;
}

void *client_sendmgr(void *args)
{
	fprintf(stderr,"sendmgr starts\n");
	int fd=*(int*)args;
	char buf[BUFSIZ];
	buf[0]=0;

	// poll the stdin for user input
	struct pollfd ufds;
	ufds.fd     = STDIN_FILENO;
	ufds.events = POLLIN;

	// timeout after 5min
	fprintf(stderr,"local>");
	while(1) {
		int rval=poll(&ufds,1,-1);
		if (rval==-1) {
			perror("sendmgr: poll");
			break;
		}

		int len = read(STDIN_FILENO,buf,BUFSIZ-1);
		buf[len-1]=0;

		/*
		 *fprintf(stderr,"echo :%s[end]\n",buf);
		 *for (int i = 0; i < len; i++)
		 *        fprintf(stderr,"%d ",buf[i]);
		 *fprintf(stderr,"\n");
		 */

		if (!strcmp(buf,"quit")) {
			fprintf(stderr,"Quit\n");
			exit(1);
		}

		write(fd,buf,len-1);
		fprintf(stderr,"local>");
		//printf("local>");
	}

	fprintf(stderr,"sendmgr ends\n");
	return NULL;
}

void *client_recvmgr(void *args)
{
	fprintf(stderr,"recvmgr starts\n");
	int fd=*(int*)args;
	char buf[BUFSIZ];
	const size_t BLKSZ=128;

	// poll the socket fd for incoming message
	struct pollfd ufds;
	ufds.fd     = fd;
	ufds.events = POLLIN;

	while(1) {
		int rval = poll(&ufds,1,300000);
		if (rval==-1) {
			perror("recvmgr: poll");
			break;
		} else if (rval==0) {
			fprintf(stderr,"Timeout occured after 5min\n");
			exit(1);
		}
		if (pollerr(ufds.revents)) exit(1);
		int bytesread = read(fd,buf,BLKSZ);
		buf[bytesread]=0;
		//fprintf(stderr,"%s",buf);
		printf("%s\n",buf);
	}
	fprintf(stderr,"recvmgr ends\n");
	return NULL;
}
