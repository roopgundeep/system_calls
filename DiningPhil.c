#include<stdio.h>
#include<semaphore.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<pthread.h>
struct{
	int data[5];
	sem_t *mutex[5];
}sh;
char *name[]={"p1","p2","p3","p4","p5"};
void *work(void *);
main()
{
	pthread_t tid[5];
	int i;
	for(i=0;i<5;i++)
	{
		sh.mutex[i]=sem_open(name[i],O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP,1);//
	}
	pthread_setconcurrency(6);
	setbuf(stdout,NULL);
	for(i=0;i<5;i++)
		pthread_create(&tid[i],NULL,work,&i);
	for(i=0;i<5;i++)
		pthread_join(tid[i],NULL);
	for(i=0;i<5;i++)
		sem_unlink(name[i]);
}
void *work(void *arg)
{
	int p,i=1;
	p=*((int *)arg);
	while(i++<2)
	{
		sem_wait(sh.mutex[p]);
		sem_wait(sh.mutex[(p+1)%5]);
		sh.data[p]=1;
		printf("p%d[%d %d %d %d %d]\n",p+1,sh.data[0],sh.data[1],sh.data[2],sh.data[3],sh.data[4]);
		sleep(1);//eating
		sh.data[p]=0;
		sem_post(sh.mutex[p]);
		sem_post(sh.mutex[(p+1)%5]);
		sleep(2);//thinking
	}
}
