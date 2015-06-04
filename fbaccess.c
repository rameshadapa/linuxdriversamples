#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>


int main(void)
{
	int fbfd = 0;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;

	long int screensize = 0;
	char *fbp = 0;
	int x=0, y=0;
	long int location = 0;

	fbfd = open("/dev/fb0", O_RDWR);
	if(fbfd == -1) {
		perror("Error: cannot open framebuffer device.\n");
		exit(1);
	}
	printf("The framebuffer device opened successfully.\n");

	if(ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
		perror("Error reading fixed screen info.\n");
		exit(2);
	}
	
	if(ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
		perror("Error reading var screen info.\n");
		exit(3);
	}
	
	printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

	screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

	printf("Screen size:: %d\n", screensize);

	fbp = (char*)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
	if((int)fbp == -1) {
		printf("Failed to map framebuffer device into memory.\n");
		exit(4);
	}

	printf("The framebuffer device was mapped to device successfully.\n");

	for(x=0; x<vinfo.xres; x++)	{
		for(y=0; y<vinfo.yres; y++)	{
	
			location = (x + vinfo.xoffset)*(vinfo.bits_per_pixel/8) + (y + vinfo.yoffset)*finfo.line_length;

			*(fbp + location) = 100 + x%150;
			*(fbp + location + 1) = 15 + x%250;
			*(fbp + location + 2) = 200 + x%50;
			*(fbp + location + 3) = 0;
		}
	}
	munmap(fbp, screensize);
	close(fbfd);
	return 0;
}
