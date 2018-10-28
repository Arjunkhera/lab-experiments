#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define PERMISSIONS 0644

struct payload{
  long msgtype;
  char msgtext[100];
};

int main(){

  struct payload buffer;
  int msqid,len,status;
  key_t key;

  key = ftok("msgkey.txt",'b');
  if(key == -1){
    printf("Unable to generate key\n");
    exit(1);
  }

  msqid = msgget(key,PERMISSIONS);
  if(msqid == -1){
    printf("Unable to access message queue\n");
    exit(1);
  }

  for(;;){
      status = msgrcv(msqid,&buffer,sizeof(buffer.msgtext),0,0);

      if(status == -1){
        printf("Unable to recieve the message\n");
        exit(1);
      }

      printf("recieve message : %s\n",buffer.msgtext);
      len = strcmp(buffer.msgtext,"end");
      if(len == 0) break;
  }

  printf("End of recieving process, nothing more to recieve\n");
  system("rm msgkey.txt");
  exit(0);
}
