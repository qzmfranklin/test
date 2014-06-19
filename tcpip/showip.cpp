#include "inet_utils.h"

int main(int argc, char const* argv[])
{
	if (argc<2) perror("no input arg");

	struct addrinfo *plist =
		get_addrinfo_list(argv[1],NULL,SOCK_STREAM);
	print_addrinfo_list(plist);

	return 0;
}
