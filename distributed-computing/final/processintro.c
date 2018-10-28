#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(){

    int mypid,myppid;

    printf("My id is : %d\n",getpid());
    printf("My parent id is : %d\n",getppid());


	return 0;
}
