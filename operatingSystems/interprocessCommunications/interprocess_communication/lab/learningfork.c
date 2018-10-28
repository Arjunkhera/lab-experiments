#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
	
	printf("I am just checking whether this line is printed in both parent and child\n");	

	int pid = fork();

	if(pid < 0){
		printf("Unable to create child");
		exit(1);
	}
	
	if(pid == 0){
		printf("I am the child process\n");
	}
	else {
		printf("I am the parent process\n");
	}

	printf("This is the end of the program\n");

	return 0;
}
