#if 00
#include<stdio.h>
#include<string.h>
#include<errno.h>
int main() {
	FILE *fp;
	char buffer[256];
	fp = fopen("A.txt", "r");
	if (fp == NULL) {
		/* errno - available in errno.h */
		strerror_r(errno, buffer, sizeof(buffer));
		printf("Error message=> %s\n", buffer);
		return;
	}
	fclose(fp);
	return 0;
}

#endif


#if 0
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main()
{
	FILE *fp;

	char buf[256];
	fp = fopen("A.txt", "r");
	if(fp == NULL)
	{
		if(strerror_r(15000, buf, sizeof(buf)) < 0)
		{
			perror("Failed\n");
		}
		else
			printf(" %s ", buf);


	}


}
#endif


#if 0

#include <stdio.h>
#include <sys/time.h>
#include <time.h>

struct timeval tv;
struct tm tm;

int main()
{

	struct tm *ltm;
	gettimeofday(&tv, NULL);
	ltm = localtime_r(&tv.tv_sec, &tm);

	printf(" %X %X \n", ltm, &tm);

	printf(" hh:mm:ss = %d:%d:%d \n", tm.tm_hour, tm.tm_min, tm.tm_sec);
	printf(" hh:mm:ss = %d:%d:%d \n", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

	printf(" year: month: date: %d: %d: %d \n", tm.tm_mday, tm.tm_mon, tm.tm_year);
	printf(" year: month: date: %d: %d: %d \n", ltm->tm_mday, ltm->tm_mon, ltm->tm_year);

	printf("wday: yearday:bls:  %d: %d :%d \n", tm.tm_wday, tm.tm_yday, tm.tm_isdst);
	printf("wday: yearday:bls:  %d: %d :%d \n", ltm->tm_wday, ltm->tm_yday, ltm->tm_isdst);



}

#endif


#if 0
#include <stdio.h>
#include <pwd.h>

int main()
{

	struct passwd *pd = getpwuid(getuid());
	printf(" %s ", pd->pw_name);
	printf(" %s ", pd->pw_passwd);
	return 0;
}

#endif
#if 0
#include <stdio.h>
#include <stdlib.h>

int main()
{

	char *buf = malloc(20);
	buf = realloc(buf, 30);
	return 0;

}

#endif


#if 0

#include <stdio.h>
#include <string.h>

int main()
{

	char p[10] = {'c', 'h'};
	char q[4] = {'t', 'e', 'j', '\0'};

	printf(" %s ", strcat(p,q));
	return 0;

}

#endif

#if 0
#include <stdio.h>
#include <stdlib.h>

int main()
{

	char *p, *np;
	p = malloc(12);
	printf(" %X ", p);

	np = NULL;
	np = realloc(p, 200000);
	printf(" %X ", np);
	printf(" %X ", p);

	return 0;

}

#endif


#if 0

#include <stdio.h>

int a(int *p)
{

	p = NULL;
}

int main()
{

	int *p = malloc(10);
	a(p);
	printf( " %X ", p);

}
#endif


#if 0
#include <stdio.h>
#include <stdarg.h>

int main()
{


	char str[10] = "ThisisJun";
	snprintf(str, 4, "charan");
	printf(" %s ", str);



}

#endif


#if 0
#include <stdio.h>
#include <stdlib.h>


int main()
{

	unsigned int seed = 1;

	int i;

	for(i=0; i<10; ++i)
	{
		printf(" %d ", rand_r(&seed));
		printf(" %d \n", seed);
	}
}


#endif


#if 0
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;
	char **buf = (char**) malloc( 2 * sizeof(char*));

	buf[0] = malloc(10);
	buf[1] = malloc(10);

	for(i=0; i< 10; ++i)
	{
		buf[0][i] = i;
	}


	for(i=0; i< 10; ++i)
	{
		buf[1][i] = i;
	}

	for(i=0; i< 10; ++i)
		printf(" %d ", buf[0][i]);
	for(i=0; i<10; ++i)
		printf(" %d ", buf[1][i]);

	return 0;
}


#endif

#if 0
#include <stdio.h>
int f(int a)
{

	int p[a]= { 1, 2};
	printf(" %d %d \n", p[0], p[1]);


}
int main()
{
	int a = 2;
	f(a);
	return 0;

}


#endif
#if 0
#include <stdio.h>
#include <stdlib.h>

int main()
{

	unsigned int seed = 1;
	int i;

	for(i=0; i<10; ++i)
		printf(" %d ", rand_r(&seed));
	for(i=0; i<10; ++i)
		printf(" %d ", rand_r(&seed));

	return 0;

}

#endif
#if 0
#include <stdio.h>

int  main()
{

	int i = 10;
	{
		int i = 5;
		++i;  

		printf(" %d ", i);
	}
	printf(" %d ", i);
}

#endif

#if 0
#include <stdio.h>

int main()
{

	int *p[0];

	printf(" %X ", p);

	return 0;


}

#endif

#if 0
#include <stdio.h>

int main()
{

	int a = 10;
	return 0;

}

#endif

#if 0

#include <stdio.h>
#include <stdlib.h>

#define index 4096*5 
int main()
{

	char *p = malloc(10);

	p[index] = 100;
	printf(" %d ", p[index]);
	return 0;

}

#endif

#if 0

#include <stdio.h>

enum A
{

	A = 1,
	B
};

int main()
{

	enum A o = 1;
	if( o == A)
		printf("Equal");
	else
		printf("Not equal"); 
}
#endif


#if 0
#define _GNU_SOURCE
#include <stdio.h>

int main()
{

	fcloseall();
	printf(" Will this be printed \n");
	return 0; 

}

#endif



#if 0

#include <stdio.h>


int main()
{

	char *s;
	char c = 'a';
	s = &c;

	printf(" %X \n", s);
	if((*s++ = c) != 'a') printf(" This is not equals\n");
	printf(" %X \n", s); //Address is incremented.


	return 0;


}

#endif


#if 0

#include <stdio.h>
//void a(char *p) //Segphault.
void a(char p[]) //Segphault.
{

	*p = 'C';

}

int main()
{

	char *p = "charan";
	a(p);
	printf(" %s ", p);
	return 0;
}

#endif


#if 0

#include <stdio.h>
const int a()
{

	printf(" This is from a\n");

}
int main()
{

	//const int (*const p)();
	//p = a;  // Read only varaible p.

	//const int (*const p)() = a;
	//p(); // NO error


	const int (const* p)();
	//p = a;

	return 0;
}

#endif

#if 0
#include <stdio.h>

int main()
{

	int *a const;
	return 0


}

#endif


#if 0

#include <stdio.h>
struct A
{

	int a;
	char b;
	int c;

}o1;
int main()
{

	printf(" %d ", (int)(&o1 + 1) - (int) (&o1));

}

#endif




#if 0


#include <stdio.h>

int main()
{

	int var = 10;
	int res = 0;
	int i;

	for(i=(8 * sizeof(var)) -1; i >=0; --i)
	{
		res |= ((var & 0x01) << i);
		var >>= 1;
	}

	printf(" %X ", res);

	return 0;
}

#endif

#if 0

#include <stdio.h>

int main()
{

	int  n = 10;
	int cnt = 0;
	while(n)
	{

		if(n & n-1) ++cnt;
		n = n-1;

	}
	printf(" %d ", cnt);
	return 0;
}

#endif


#if 0

#include <stdio.h>
int MACRO_EXTRACT(val, m, n) {								
	int temp = ((~0)>>n) << n;							
	temp = (temp << (sizeof(val)*8 - m - 1 )) >> (sizeof(val)*8 - m - 1); 	
	val & temp; } 


int main()
{

	int res = MACRO_EXTRACT(12, 2, 0);
	printf(" %d", res);
	return 0;	


}

#endif

#if 0

#include <stdio.h>

#define extract(val, m, n)   ({ \
		int mask = ((~0)>>n)<<n;	\
		mask = (mask << (31 -m));	\
		printf(" %X ", mask);		\
		mask = ((unsigned)mask >> (31 -m)); 	\ 
		printf(" %X ", mask); 		\
		val = val & mask;   		\
		printf(" The valus is :  %d ", val); })

int main()
{

	//char c = 10;
	//printf("%d ", sizeof(c));

	int val = 10;
	int m = 2;
	int n = 0;

	//val = (val >> n) << n;
	//val = (val << 31 - m ) >> (31 -m );
	//printf(" %d ", val);

	//m= extract(val, m, n);

	if(m = extract(val, m, n))

		printf(" %d ", m); // We will get the return value of the printf.



	return 0;
}

#endif



#if 0

#include <stdio.h>

int main()
{

	int a = -1;
	unsigned int b = -1;

	printf(" %d ", a);
	printf(" %d ", b);

}

#endif



#if 0
#include <stdio.h>
struct A
{
	int a,b;
}*p;

int main()
{

	int c[2] = {1, 2};
	p = (struct A*) c;

	printf(" %d %d ", p->a, p->b);

}
#endif


#if 0
#include <stdio.h>
struct A
{
	int a;
	short b;
	char c;
	float d;
} o = {1, 2, 'c', 3.14};

int main()
{
	char *p = &o.c;
	unsigned long val;
	printf(" %X \n", &o);
	val = &((struct A*)0)->c;
	struct A *st = (p - val);
	printf(" %X ", (unsigned )st);

	return 0;
}

#endif


#if 0

#include <stdio.h>

int fun(int n)
{
	if(n == 0) printf(" Reached 0\n");

	while(n > 0) fun(n-1);
}

int main()
{


	fun(3);

}

#endif


#if 0

#include <stdio.h>

struct A
{

	char a:8;
	unsigned short b:8;

}o;

int main()
{

	o.a = 255;
	printf(" %d", o.a);
	return 0;	

}


#endif


#if 0
#include <stdio.h>
#include <assert.h>

int main()
{

	assert(0);
	return 0;



}

#endif


#if 0
#include <stdio.h>

int main()
{

	unsigned char c = 257;
	printf(" %d ", c);

}
#endif


#if 0
#include <stdio.h>
int main()
{

	unsigned short a = 0xAABB;
	unsigned char *p = (unsigned char*) &a;
	printf(" %X ", *p);
	return 0;

}

#endif


#if 0

#include <stdio.h>

int main()
{

	char *p = "1A";
	printf(" %d ", p[0]);

}

#endif



#if 0

#include <stdio.h>
#include <pthread.h>

pthread_t pid[2];
pthread_mutex_t mutex;

void *Thr1(void *p)
{

	pthread_mutex_lock(&mutex);
	pthread_mutex_lock(&mutex);
	printf( " From %s \n", __func__);
	return NULL;

}

void *Thr2(void *p)
{

	pthread_mutex_unlock(&mutex);
	pthread_mutex_unlock(&mutex);

	printf( " From %s \n", __func__);

	return NULL;

}
int main()
{

	pthread_mutex_init(&mutex, NULL);

	pthread_create(&pid[0], NULL, Thr1, NULL);
	pthread_create(&pid[1], NULL, Thr2, NULL);


	pthread_join(pid[0], NULL);
	pthread_join(pid[1], NULL);
}


#endif

#if 0

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

pthread_t pid[2];
sem_t count;
void *Thr1(void *p)
{

	sem_wait(&count);
	sem_wait(&count);
	sem_wait(&count);
	sem_wait(&count);
	sem_wait(&count);
	printf( " From %s \n", __func__);
	printf(" %d ", count);
	return NULL;

}

void *Thr2(void *p)
{


	sem_post(&count);
	sem_post(&count);
	sem_post(&count);
	sem_post(&count);
	//sem_post(&count);
	printf( " From %s \n", __func__);

	return NULL;

}
int main()
{

	sem_init(&count, 0, 0);	
	pthread_create(&pid[0], NULL, Thr1, NULL);
	sleep(1);
	pthread_create(&pid[1], NULL, Thr2, NULL);


	pthread_join(pid[0], NULL);
	pthread_join(pid[1], NULL);
}


#endif


#if 0
#include <stdio.h>

struct A
{

	int a;
	char c;
	int b;

} o = {1, 2, 3};

int main()
{


	unsigned long p = (unsigned long *)(&o.c);	

	unsigned long q = &((struct A*)0)->c;

	struct A *z = (struct A*)(p - q);

	printf(" %d %d %d \n", z->a, z->c, z->b);
	return 0;
}


#endif


#if 0

#include <stdio.h>
#include <string.h>

char *strrev(char *str)
{
	char *p1, *p2;

	if (! str || ! *str)
		return str;
	for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
	{
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}
	return str;
}

int main()
{

	char p[] = "This is a string";
	int temp = 0;
	char *q = strrev(p);
	int len = strlen(q);
	int i;
	for(i=0; i<len ; ++i)
		if(q[i] == ' ') 
		{
			++temp;
			q[i] = '\0';
		}

	char *z = q;
	for(i=0; i< (temp+1); ++i)
	{	
		z = strrev(z);
		z += strlen(z) + 1;

	}
	for(i=0; i<len ; ++i)
		if(q[i] == '\0') 
		{
			++temp;
			q[i] = ' ';
		}
	printf("%s", q);
	return 0;

}

#endif


#if 0

#include <stdio.h>

#define A 1; printf("Helloworld");

int main()
{

	//	A; // Outputs after expansion as ... 1 printf("Helloworld");
	A;


}

#endif

#if 0

#include <stdio.h>

int main()
{

	//	printf(" %d ", getpid());
	//	printf(" %jd ", getpid());
	return 0;


}

#endif




#if 0

#include <stdio.h>

int main()
{


	if(fork())
	{
		printf(" Parent : %d \n", (int)getpid());
	}
	else
		printf(" Child : %d \n", (int)getpid());

	printf(" PID : %d \n", (int)getpid());

	return 0;

}



#endif

#if 0

#include <stdio.h>

int a()
{

	int b;
	return b=2;
}
int main()
{

	printf(" %d ", a());
	return 0;


}

#endif


#if 0

#include <stdio.h>

//const int a = 10;
int main()
{
	const int a = 10;

	int *b = (int*) &a;
	*b = 11;
	printf(" %d ", *b);

	return 0;

}
#endif



#if 0

#include <stdio.h>

struct abcdefghi_l
{
	int angkor_wait
};

int main()
{

	struct abcdefghi_l o = {10};

	printf(" %d ", o.angkor_wait);
	return 0;

}
#endif


#if 0

#include <stdio.h>

char *strrev_l(char *p)
{

	int i, j = 0;
	for(i=0; p[i]; ++i, ++j);

	for( i = 0, --j ; i < j; ++i, --j)
	{

		p[i] = p[i] ^ p[j];
		p[j] = p[i] ^ p[j];
		p[i] = p[i] ^ p[j];
	
	}

	
	return p;
}
int main()
{
	char p[] = "charan Teja Reddy";
	strrev_l(p);

	printf(" %s\n", p);
	return 0;
}

#endif


#if 0

#include <stdio.h>
#include <stdlib.h>

#define LENGTH(x) (sizeof(x)/sizeof(x[0]))
int a[3] = {1, 2, 9};
int b[2] = {1, 9};

int c[(sizeof(a) + sizeof(b))/sizeof(a[0]) - 1];

int main()
{
//	printf(" %d ", sizeof(c));

	memset(c, 0, sizeof(c));
	int i, j;

	for(i =0; i< LENGTH(a); ++i)
	{
		for(j=0; j<LENGTH(b); ++j)
		{
			c[i + j] += a[i] * b[j];
			
		}
	}


	for(i =0; i<LENGTH(c); ++i)  printf(" %d ", c[i]);
		

}

#endif

#if 0

#include <stdio.h>

int l;

//int a[l]; Error. Variably modified file scope.


int main()
{

return 0;
}
#endif



#if 0

#include <stdio.h>
#include <math.h>

#define length(x) (sizeof(x)/sizeof(x[0]))

int a[] = {1, 2, 5, 6, 8, 10, 15, 20, 23, 26, 30, 42};
int ele;

void bisearch(int low, int high)
{

	int mid = ((low + high) >> 1);

	if(a[mid] == ele) printf(" Element is found \n");
	if(low >= high) { printf(" Element is not found\n"); return;}

	if(ele < a[mid]) bisearch(low, mid );
	else if(ele > a[mid]) bisearch(mid + 1, high);
	

}

int main()
{

	int n = length(a);

	int low = 0, high = n - 1;

	while(1)
	{
		printf(" Enter the element to be scanned \n");
		scanf("%d", &ele);

		if(ele < 0) break;
		
		bisearch(low, high);
	}


}

#endif


#if 0


#include <stdio.h>

//#define DEBUG(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#define DEBUG(fmt...) fprintf(stderr, fmt)
int main()
{

	DEBUG("charan: %d \n", 10);
	return 0;

}

#endif


#if 0

#include <stdio.h>

#define LENGTH(a) (sizeof(a)/sizeof(a[0]))

int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

int bisearch(int key,int l,int h)
{

	if(h>=l)
	{
		int mid = (l + h) >> 1;

		if(arr[mid] == key) return 1;

		else if(key > arr[mid])  return bisearch(key, mid + 1, h);

		else if(key < arr[mid]) return bisearch(key, l, mid - 1);
		
	}

	return 0;

}


int main()
{

	int len = LENGTH(arr);

	int l = 0, h = len -1;

	while(1)
	{
		int ele;
		printf(" Enter element to search \n");
		scanf("%d", &ele);

		if(ele < 0) break;


		if(bisearch(ele, l, h)) printf(" Element is found \n");
		else printf("Element is not found \n");
	}

	return 0;
}

#endif

#if 0
#include <stdio.h>
/* Add the below two lines global makes the core dump */
const char a = 10;
char *p = &a;

int main()
{
/* The two lines here makes the things fine */
const char a = 10;
char *p = &a;
*p = 20;

}

#endif


#if 0
#include <stdio.h>
int main()
{

   int i;
   for(i=0; i< 10; ++i)
   {
      int a = 0;
      printf(" %d ", ++a);
   }

   return 0;

}

#endif

#if 0
#include <stdio.h>
void d2b(int a)
{

   if(a==0) return;
   d2b(a>>1);
   printf("%d",a%2);
}

int get_positive(int a)
{
   while( a < 0)
   {
       a = a + 0xFFFF + 1;
   }

   return a;

}
int main()
{

  char a = -1;
  if( a < 0) a = get_positive(a);
  d2b(a);
  printf("\n");
  return 0;

}

#endif

#if 0

#include <stdio.h>

int main()
{

   int a = 10;
   *a = 20; // Error is this.
   return 0;

}
#endif

#if 0
#include <stdio.h>
int main()
{
	int i = 10;
	for(; i<15; ++i)
	{
		printf(" %d ", i); // 10
		{
		 int i = 20;
		 printf(" %d ", i);//20
		}
	}
	return 0;
}
#endif

#if 0
#include <stdio.h>

struct A
{
	int a,b;
}o1 = {1,2}, o2;
int main()
{
	if(o2 == o1) ; // Error: Can't compare twi structure objects.
	return 0;
}

#endif

#if 0

#include <stdio.h>

int main()
{

	int i;
	for(i=0; i< 10; ++i)
	{
		int j = 10;
		printf(" %d ", ++j);
	}
	return 0;
}

#endif

#if 0

#include <stdio.h>
#include <getopt.h>


int main(int argc, char **argv)
{
	int opt = -1, long_index;
	static struct option long_option[] = {
		{"area", no_argument, 0, 'a'},
		{"perim",no_argument, 0, 'p'},
		{"length", required_argument, 0, 'l'},
		{"breadth", required_argument, 0, 'b'},
		{0,0,0,0}

	};

	int a , p, l, b ;
	a = p = l = b = -1;
	while(-1 != (opt=getopt_long(argc, argv, "apl:b:", long_option, &long_index)))
	{
		switch(opt)
		{
			case 'a':
				a = 0;break;
			case 'p':
				p = 0; break;
			case 'l':
				l = atoi(optarg);break;
			case 'b':
				b = atoi(optarg); break;
			default:
				break;

		}

		printf(" Area ; %d ", l*b);
	}
	
	return 0;
}

#endif

#if 0

#include <stdio.h>
#include <pthread.h>
#include <signal.h>

pthread_t tid;
struct sigaction sa;
void Handler(int p)
{
	printf(" %s \n", __func__);
}
void *Thr1(void *p)
{
	fprintf(stderr," %s \n", __func__);
	fprintf(stderr, " PID = %d, PPID = %d \n", getpid(), getppid());

	memset(&sa, 0, sizeof(sa));
//	sa.handler = Handler;
	signal(SIGINT, Handler);
	while(1);
	return NULL;

}
int main()
{

pthread_attr_t attr;

pthread_attr_init(&attr);
pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
pthread_create(&tid, &attr, Thr1, NULL);

	fprintf(stderr," %s \n", __func__);
	fprintf(stderr, " PID = %d, PPID = %d \n", getpid(), getppid());
//sleep(1);
while(1);
pthread_join(tid, NULL);

return 0;


}
#endif

#if 0

#include <stdio.h>
#include <pthread.h>

pthread_t tid[2];
pthread_key_t key;
int count = 0;

void close_up_handler(void *p)
{
	printf(" %s \n", __func__);
	return;
}
void *Thr(void *p)
{

	++count;
	pthread_setspecific(key, &count);
	int *q = pthread_getspecific(key);
	fprintf(stderr, " %d \n",*q);

	return NULL;

}

int main()
{

	pthread_key_create(&key, close_up_handler);

	pthread_create(&tid[0], NULL, Thr, NULL);
	sleep(1);
	pthread_create(&tid[1], NULL, Thr, NULL);
	
	
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

}
#endif

#if 0

#include <stdio.h>
struct A
{

	char a[0];// Size is Zero.

};
int main()
{

	printf(" %d \n", sizeof(struct A));
	return 0;

}

#endif

#if 0

#include <stdio.h>

char a[2][3] = {"ch", "ar"};
int main()
{
//	printf(" %s %s \n",a[0],a[1]);
	printf(" %s \n",a);
	return 0; 
}
#endif

#if 0
#include <stdio.h>

int main()
{

	char *p;

//	p = "charan";// Works fine.

	p = malloc(20);
//	p = "charan"; // Fine.
//	*(char*)&(p+1) = "charan";
	char *q = p + 1;
	q = "charan";

	*p = 'C';//  Both the cases above results in segphault
	printf("%s ", p);
	printf("%s ", q);
	return 0;

}

#endif

#if 0
#include <stdio.h>
extern int a;
//int a;
int main()
{

a = 10;
return 0;
}

#endif
#if 0
#include <stdio.h>

struct A
{

	int b;
	char a[];

}o, *p;

int main()
{
//	o.a = malloc(10);
	p = malloc(sizeof(*p) + 10);

	p->b = 10;
//	(char*)(&(p->b) + 1) = "Charan";

//	p->a = "charan"; // error

//	(char*)p->a = "charan"; // Error.
	*(char *)(&p->b + 1) = 20;

	char *q = &p->b +1;

	q = "charan";

	printf(" %d \n", p->b);
// printf(" %d \n", *p->a);
	printf(" %s \n", q);
//rintf(" %d ", sizeof(struct A));

	
	return 0;

}
#endif


#if 0

#include <stdio.h>

struct A
{
	int a;
	struct A *ptr;
}O = 
{
	.a = 10,
	.ptr = &O // Address of a variable is constant. Because these are relative addresses then the actual address.And these are similar to the addre3ss of a function.
};

int a = 10;
//int b = a + 10;// Error
//int b = &a + 10; // NO error

void fun()
{
	fprintf(stderr, " %s \n", __func__);
}

void (*p)() = fun;
int main()
{
	printf(" %d %d\n", O.a, O.ptr->a);
	p();
	return 0;

}
#endif
#if 0

#include <stdio.h>


int main()
{

int a = 0;

if(!a++)
{

printf(" Sucks here \n");


}

return 0;
}

#endif



#if 0

#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

void Handler(int data)
{
	char buf[256];
	buf[read(STDIN_FILENO, buf,255)] = '\0';

	printf(" %s \n", buf); 
}
int main()
{

	unsigned long offlags = 0;
	signal(SIGIO, Handler);

	fcntl(STDIN_FILENO, F_SETOWN, getpid()); // Nothing to implement in the driver also. So, no need to worry about it.filp->f_owner = pid.

	offlags = fcntl(STDIN_FILENO, F_GETFL);

	fcntl(STDIN_FILENO, F_SETFL, offlags | FASYNC); // Theis will add the file flags , filp->flags |= FASYNC, whose flag value is cleared by default, and hence th drivers fasync() system call will gets called.
	
	while(1);
		
	return 0;

}

#endif

#if 0
#include <stdio.h>

struct B 
{
	int c;
	int *ptr;
};

struct A
{
	struct A *p;
	int d;
	struct B b;
//}O = { .p = &O, .d = 30, .b.c = .d};// Error that inisitalizer is not constant.
}O = {
	.d = 20,
//	.b.c = .d // Error
//	.b.c = (int)&.d// Error.
	.b.ptr = &O.d // Perfect. We can assign the address but not the values.

	};

int main()
{

printf(" %d \n", O.p->b.c); // 20.
//printf(" %d
return 0;


}

#endif
#if 0

#include <stdio.h>

struct B 
{
	int c;
};

struct A
{

int a;
struct B b;

};

int main()
{

/*	struct A O = {.a = 10,
		      .b = 
			{
 			  .c = 20,
			},
		    };
*/// Perfectly fine.

struct A O;
O.b = {.c = 20}; // Error. These are designated inititalizers and which are initialized during the object declaration itself

//	printf(" %d %d ", O.a, O.b.c);

};

#endif




#if 0

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

extern int errno;
int main()
{

int fd = open("Input.txt", O_RDWR);
if(fd < 0)
{

	printf(" Failed to open the file \n");
	return -1;

}
else
	printf(" Opeming of the file is success\n");

char buf[4096];
if(read(fd, buf, sizeof(buf)) != sizeof(buf))
{
//	perror("read");
	printf(" This is from read%s \n", strerror(errno));

}

return 0;

}

#endif


#if 0

#include <stdio.h>

#define A(x) #x
#define AB(a,b) a##b;
int main()
{

	int ab = 20;

//	char *p = #charan;
//	int v = a ## b;
	int v = AB(a,b);
	char *p = A(charan);
	return 0;

}

#endif


#if 0
#include <stdio.h>
static int a ;

int fun()
{

static int a;

}


int fun1()
{

static int a;
}
int main()
{

return 0;
}

#endif

#if 0

#include <stdio.h>
struct B 
{

	int c;	
	int *p;
}

struct A 
{

	int a, b;
	struct B *b;

};
int main()
{

struct A O = {1};
printf(" %d \n", O.b);

return 0;

}

#endif


#if 0

#include <stdio.h>
#include <math.h>
int main()
{

int a = ceil(pow(100,0.5));
printf(" %d ", a);

return 0;


}

#endif

#if 0


#include <stdio.h>

int reverse(unsigned long num)
{

	unsigned int res = 0;

	while(num)
	{
		res = (res*10) + (num % 10);
		num = num/10;
	}
	
	return res;

}
int main()
{

	printf(" %d ", reverse(4));

}

#endif


#if 0

#include <stdio.h>

int main()
{


int a = 10;
{

int a;
a = 20;
printf(" %d \n", a);

}

printf(" %d \n", a);
return 0;
}

#endif


#if 0

#include <stdio.h>
#include <assert.h>

int main()
{

//	assert(1);
	assert(0);

}

#endif

#if 0

#include <stdio.h>


int main()
{


char p[] = "Hello";

printf(" %c \n", 108);
return 0;
}

#endif

#if 1

#include <stdio.h>

int main()
{

a();
return 0;

}

#endif
