/*
 * Zhongming Qu, 2014 Jun
 */

/*
 * Code a telnet-like utility for:
 * 	1.	establishing tcp connection to a remote host identified by the 
 * 		<dst,port> pair,
 * 	2.	send text to the remote host, and
 * 	3.	receive message from the remote host.
 *
 * Usage:
 * 	ipmsg [domain_name|ip_address] port
 *
 * IP address can be either ipv4 or ipv6.
 * Built-in timeout is 5s. 
 * Type 'quit' to terminate.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

static void perr(const char * msg)
{
	fprintf(stderr,"%s\n",msg);
	exit(1);
}

static struct addrinfo *get_ipaddrinfo_list(const char *addr, const char *port)
{
/*
 * Copied from Divakar Viswanath, added port
 */
	struct addrinfo hint;
	hint.ai_family  = AF_UNSPEC;
	hint.ai_socktype= SOCK_STREAM;
	struct addrinfo *res;
	int rval = getaddrinfo(addr,port,&hint,&res);
	if (rval) {
		perror("get_ipaddrinfo_list");
		exit(1);
	}
	return res;
}

static void free_ipaddrinfo_list(const struct addrinfo *p)
{
	freeaddrinfo(p);
}

/*
 * Try connecting until the first success
 */

static int try_connect(const struct addrinfo *plist)
{
	int fd;
	for(struct addrinfo *p=plist; p!=NULL; p=p->ai_next) {
		fd = socket(p->ai_family,p->ai_socktype,p->ai_protocol);
		if (fd==-1) { 
			perror("socket"); 
			continue; 
		}
		err = connect(fd,p->ai_addr,p->ai_addrlen);
		if (err==-1) {
			perror("connect");
			continue;
		}
		break; // if reach here, must have succeded
	}
	if (p==NULL) fd=-1;
	return fd;
}

int main(int argc, char const* argv[])
{
	if (argc<3) perr("usage: ipmsg [address] [port]");

	struct addrinfo *plist = 
		get_ipaddrinfo_list(argv[1],argv[2]);
	int fd = try_connect(plist);
	if (fd==-1) perr("cannot connect to remote host");

	/*
	 * do something here
	 */


	close(fd);
	
	return 0;
}
