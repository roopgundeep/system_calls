#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int foo = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* foo_initializer()
{
	pthread_mutex_lock(&mutex);
	if (foo == 0)
		foo = 1;	/* This must only be done once. */
	pthread_mutex_unlock(&mutex);
}





main()
{
	pthread_t thread1, thread2;
	int  iret1, iret2;

	/* Create independent threads each of which will execute function */

	iret1 = pthread_create( &thread1, NULL, foo_initializer,NULL);
	iret2 = pthread_create( &thread2, NULL, foo_initializer,NULL);

	/* Wait till threads are complete before main continues. Unless we  */
	/* wait we run the risk of executing an exit which will terminate   */
	/* the process and all threads before the threads have completed.   */

	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL); 

	printf("Thread 1 returns: %d\n",iret1);
	printf("Thread 2 returns: %d\n",iret2);
	exit(0);
}



