#include<stdio.h> 
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<errno.h>
int main(void)
{
	pid_t pid;
	int status;
	char* cmd[] = {"ls"};

	pid=fork();

	if(pid == 0)
	{
		execvp(*cmd,cmd);        // Replaces the address space of this program with the specified program
		printf("This is not printed\n");
	}
	else
	{
		printf("Parent is still working :)\n");
		wait(&status);
	}
        return 0;
}
