#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>

int main(){
	pid_t pid1, pid2;
	pid1 = fork();
	printf("%d \n", pid1);
	sleep(1);
	
	exit(0);
}

