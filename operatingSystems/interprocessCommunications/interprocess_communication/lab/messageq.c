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

  // creating a text file to store the unique id
  system("touch msgkey.txt");

  key = ftok("msgkey.txt",'b');
  if(key == -1){
    printf("Unable to generate key\n");
    exit(1);
  }

  msqid = msgget(key,PERMISSIONS | IPC_CREAT);
  if(msqid == -1){
    printf("Unable to create message queue\n");
    exit(1);
  }

  while(fgets(buffer.msgtext,sizeof(buffer.msgtext),stdin) != NULL){
      len = strlen(buffer.msgtext);
      if(buffer.msgtext[len-1] == '\n') buffer.msgtext[len-1] = '\0';

      status = msgsnd(msqid,&buffer,len+1,0);
      if(status == -1){
        printf("Unable to send the message\n");
        exit(1);
      }
  }

  strcpy(buffer.msgtext,"end");
  len = strlen(buffer.msgtext);
  if(msgsnd(msqid,&buffer,len+1,0) == -1){
    printf("System error\n");
    exit(1);
  }

  status = msgctl(msqid,IPC_RMID,NULL);
  if(status == -1){
    printf("system error\n");
    exit(1);
  }

  printf("End of sending process\n");
  exit(0);
}
