#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct msgbuf {
    long msgtype;
    char data[200];
}payload;

int main(){
    
    // obtain the key
    key_t key = ftok("msgqprgram",65);

    // get the queue id
    int id = msgget (key,0666|IPC_CREAT);

    // receive the payload
    msgrcv(id,&payload,sizeof(payload),1,0);

    // print the payload data 
    printf("Start of payload data\n");
    printf("%s\n",payload.data);
    printf("End of payload data\n");

    // destroy the mesage queue
    msgctl(id,IPC_RMID,NULL);

    return 0;
}



