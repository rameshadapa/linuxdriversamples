#if 0
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/epoll.h>

#define MAX_EVENTS 32

int epfd;

int main()
{

	//	epfd = epoll_create1(EPOLL_CLOEXEC);
	epfd = epoll_create(1);
	if(epfd < 0)
	{
		perror("epoll_create1");
		return -1;
	}


	struct epoll_event ev, events[MAX_EVENTS];
	int nr, i;

	ev.events = EPOLLIN;
	ev.data.fd = STDIN_FILENO;

	if(epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &ev) < 0)
	{
		perror(" epoll_ctl");
		return -1;
	}

	struct epoll_event ev_s;
	int epfd_s;

	epfd_s = epoll_create(1);
	if(epfd_s < 0)
	{
		perror("epoll_create");
		return -1;
	}
	ev_s.events = EPOLLIN;;
	ev_s.data.fd = epfd;

	if(epoll_ctl(epfd_s, EPOLL_CTL_ADD, epfd, &ev_s) < 0)
	{
		perror("epoll_ctl");
		return -1;
	}


	//nr = epoll_wait(epfd_s, events, MAX_EVENTS, -1);
	nr = epoll_wait(epfd, events, MAX_EVENTS, -1);
	if(nr < 0)
	{
		perror("epoll_wait");
		return -1;
	}

	for(i=0; i< nr; ++i)
	{
		if(events[i].data.fd == STDIN_FILENO)
			//		if(events[i].data.fd == epfd)
		{	

#if 1	
#define BUFLEN 1024
			char buf[BUFLEN];
			int len;

			len = read(events[i].data.fd, buf, BUFLEN);
			if(len < 0)
			{
				perror("read");
				return -1;
			}	

			buf[len] = '\0';
			printf(" %s ", buf);

			return 0;
#endif


			printf(" The STDIN is readable \n");
			return 0;
		}
	}


	if(close(epfd) < 0)
	{
		perror("close");
		return -1;
	}
	fprintf(stderr, "Exiting \n");

	return 0;

}

#endif

#if 0
#include <sys/epoll.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, const char *argv[]) {
	// create event
	struct epoll_event stdin_ev, events[10];

	// set event
	stdin_ev.events = EPOLLIN;
	stdin_ev.data.fd = STDIN_FILENO;

	// create epoll
	int epfd = epoll_create(1), i, rcnt;
	char c;

	// set monitoring STDIN_FILENO 
	epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &stdin_ev);

	while(1) {
		int ret = epoll_wait(epfd, events, 1, -1);

		// timeout or failed
		if(ret == 0) {
			fprintf(stdout, "timeout\n");
			continue;
		} else if (ret < 0) {
			perror("ret<0");
			exit(EXIT_FAILURE);
		}

		// readable
		fprintf(stdout, "%d event(s) happened...\n", ret);
		for(i=0; i < ret; i++) {
			if(events[i].data.fd == STDIN_FILENO &&\
					events[i].events&EPOLLIN) {
				// read a char
				rcnt = read(STDIN_FILENO, &c, 1); 
				// if read 0 char, EOF?
				if(rcnt != 1) {
					fprintf(stdout, "read %d byte\n", rcnt);
					continue;
				}
				// else print ascii
				fprintf(stdout, "ascii code: %d\n", c);
			}
		} 
	}
	close(epfd);
	return 0;
}

#endif

#if 0
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define TIME 5
fd_set readfds;

struct timeval tv;

char buf[256];
int main()
{

	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);

	tv.tv_sec = 10;
	tv.tv_usec = 0;


	if(select(STDIN_FILENO + 1, &readfds, 0, 0, &tv) < 0)
		perror("select");

	if(FD_ISSET(STDIN_FILENO, &readfds))
	{
		buf[read(STDIN_FILENO, buf, 256)] = NULL;
		printf(" Input is readable \n");

		printf(" %s \n", buf);
	}


}


#endif



#if 1

#include <sys/epoll.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>

int epfd, epfd_s;
int main()
{
#define MAXEVENT 32

	epfd = epoll_create(1);
	if(epfd < 0)
	{
		perror("epoll_create\n");
		return -1;
	}


	struct epoll_event ev, events[MAXEVENT];
	int i, nr;

	ev.events = EPOLLIN;
	ev.data.fd = STDIN_FILENO;

	if(epoll_ctl(epfd, EPOLL_CTL_ADD, ev.data.fd, &ev) < 0)
	{
		perror("epoll_ctl\n"); return -1;
	}

	epfd_s = epoll_create(1);
	if(epfd_s < 0)
	{

		perror("epoll_create\n");
		return -1;

	} 

	struct epoll_event ev_s;
	ev_s.events = EPOLLIN;
	ev_s.data.fd = epfd;
	if(epoll_ctl(epfd_s, EPOLL_CTL_ADD, ev_s.data.fd, &ev_s) < 0)
	{

		perror("epoll_ctl");
		return -1;

	}


	nr = epoll_wait(epfd_s, events, MAXEVENT, -1);

	for(i=0; i<nr; ++i)
	{
		if(events[i].data.fd == epfd)
		{
			int nr, i;
			struct epoll_event events[MAXEVENT];
			nr = epoll_wait(epfd, events, MAXEVENT, -1);
			for(i=0; i<nr; ++i)
			{
				if(events[i].data.fd == STDIN_FILENO)
				{
					printf("STDIN is readable \n");
					char buf[1024];
					buf[read(STDIN_FILENO, buf, sizeof(buf) -1)] = '\0';
					printf(" The data read is : %s \n", buf);
				}
			}
			
		}
	}

	return 0;
}

#endif
