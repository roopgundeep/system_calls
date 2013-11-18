#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	int return_value,ret;
	printf("Forking process\n");
	fork();
	printf("The process id is %d and return value is %d\n",getpid(),return_value);  
	execl("/bin/ls","ls","-l",NULL);
	printf("This line is not printed\n");
}

