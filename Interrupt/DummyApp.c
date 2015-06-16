#include <stdio.h>
#include <fcntl.h>

int main()
{

int fd = open("/dev/Dummy", O_RDWR);
if(fd < 0)
{

perror("Open");
return -1;

}

return 0;

}
