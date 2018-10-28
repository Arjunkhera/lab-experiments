#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main(){

    printf("Before calling fork\n");
    pid_t pid = fork();

    if(pid < 0){
        printf("Failure to fork\n");
        exit(1);
    }
    
    if(pid == 0){
        printf("The pid of child is : %d\n",getpid());
        printf("The pid of child's parent is : %d\n",getppid());
        sleep(10);
        printf("The pid of child's parent is : %d\n",getppid());
    } else {   
        // Uncomment the sleep to see change in order
        sleep(3);
        wait();
        printf("The pid of parent is : %d\n",getpid());
    }

    printf("This is the end of the road\n");

    return 0;
}


