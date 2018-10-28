#include<stdio.h>
#include<sys/types.h>
#include<sys/shm.h>

int main(){

    // obtain the key
    key_t smkey = ftok("thisiskey",65);

    // get the id of the shared memory
    int id = shmget(smkey,1024,0666|IPC_CREAT);

    // convert void* to char* for writing 
    char *str = (char*) shmat(id,(void*)0,0);
    
    // write into the shared memory
    printf("Start reading data from shared memory\n");
    printf("%s",str);
    printf("\nEnd of reading from shared memory\n");
    
    // detach the process from the shared memory
    shmdt(str);
    // destroy the shared memory
    shmctl(id,IPC_RMID,NULL);

    return 0;
}



