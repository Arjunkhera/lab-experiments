#include<stdio.h>
#include<stdlib.h>

int main(){

	int pid;

	pid = fork();	
	printf("Standard template\n");

	if(pid == 0){
		printf("i am child and my parent is %d\n",getppid());
		sleep(10);
		printf("i am child and my parent is %d\n",getppid());
	}
	else {
		printf("I am parent and my pid is %d\n",getpid());
		sleep(3);
	}

	return 0;
}
