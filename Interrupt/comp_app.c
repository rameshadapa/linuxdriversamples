#include <stdio.h>
#include <fcntl.h>
#include <signal.h>

int fd;

void Handler(int data)
{

	char buf[6];
	buf[read(fd, buf, 5)] = '\0';

	printf(" %s \n", buf);	

}

int main()
{

	unsigned long flags = 0;
	fd = open("/dev/comp", O_RDWR);
	
	if( fd < 0)
	{
		perror("Open \n");
		return -1;
	}


	signal(SIGIO, Handler);
	fcntl(fd, F_SETOWN, getpid());
	flags = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, flags | FASYNC);

	while(1);
	

	

}
