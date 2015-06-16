#include <stdio.h>
#include <fcntl.h>

int main()
{

	int fd = open("/dev/comp", O_RDWR);
	if(fd < 0)
	{
		perror("Open");
		return -1;
	}

	char buf[4];
	read(fd, buf, sizeof(buf));

	return 0;
	

}
