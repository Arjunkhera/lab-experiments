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
    // set message type to 1
    payload.msgtype = 1;

    // write data to be put in queue
    printf("Start writing data\n");
    gets(payload.data);
    printf("End of writing\n");

    // send the payload
    msgsnd(id,&payload,sizeof(payload),0);

    return 0;
}



