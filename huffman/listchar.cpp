#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

void count_char_freq(const char *fname, size_t *freq)
{
	int fd = open(fname,'r');
	memset(freq,0,sizeof(size_t)*128);
	char buf[BUFSIZ];
	while (read(fd,buf,BUFSIZ-1)>0)
		for (int i = 0; i < BUFSIZ-1; i++)
			freq[buf[i]]++;
	close(fd);
}

static void print_char_freq0(const char ch, const size_t freq) 
{
	if (ch<32)
		printf("[%3d] \" \" %lu\n",ch,freq);
	else
		printf("[%3d] \"%c\" %lu\n",ch,ch,freq);
}

void print_char_freq(const size_t *freq) 
{
	for (int i = 0; i < 128; i++)
		print_char_freq0(i,freq[i]);
}

int main(int argc, char const* argv[])
{
	if (argc<2) {
		fprintf(stderr,"Usage: listchar.exe [filename]\n");
		exit(1);
	}

	size_t freq[128]; // 128 ASCII keys
	count_char_freq(argv[1],freq);
	print_char_freq(freq);



	return 0;
}
