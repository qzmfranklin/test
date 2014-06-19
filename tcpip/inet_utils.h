#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Get ipv4/6 address string from struct sockaddr
 */
//void get_ipaddrstr(struct sockaddr *skaddr, char *addstr); //obselete
void get_ipaddrstr(void *addr, char *addstr);

/*
 * Copied from Divakar Viswanath, added port
 */
struct addrinfo *get_addrinfo_list(
		const char *addr, 
		const char *port,
		const int socktype);

struct addrinfo *get_addrinfo_list_server(
		const char *addr, 
		const char *port,
		const int socktype);

/*
 * Print ipv4/6 address
 */
void print_addrinfo(const struct addrinfo *p);
void print_addrinfo_list(const struct addrinfo *p);

/*
 * Try connecting until the first success, return -1 upon failure
 */
int try_connect(struct addrinfo *plist);

/*
 * Try binding to port until the first success, return -1 upon failure
 */
int try_bind(struct addrinfo *plist);

/*
 * Print to stderr error message for poll revents, return 0 if no error
 */
int pollerr(const int revents);

/*
 * Send/Recv manager for client, invoked by pthreads
 */
struct client_mgr_t {
	int fd;
	double timeout_sec;
};
void *client_sendmgr(void *args);
void *client_recvmgr(void *args);

#ifdef __cplusplus
}
#endif

