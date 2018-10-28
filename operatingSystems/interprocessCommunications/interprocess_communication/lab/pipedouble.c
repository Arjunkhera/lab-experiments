#include<stdio.h>
#include<unistd.h>

int main(){

  int status,pid,fdfirst[2],fdsecond[2];
  char message[2][50] = {"written by parent","written by child"};
  char buffer[100];

  status = pipe(fdfirst);
  if(status == -1){
    printf("Unable to create the first pipe\n");
    exit(1);
  }

  status = pipe(fdsecond);
  if(status == -1){
    printf("Unable to create the second pipe\n");
    exit(1);
  }

  pid = fork();

  if(pid < 0){
    printf("Unable to create a child procces \n");
    exit(1);
  }
  else if(pid > 0){
    close(fdfirst[0]);
    close(fdsecond[1]);

    printf("Parent is writing the message\n");
    write(fdfirst[1],message[0],sizeof(message[0]));

    wait(NULL);

    read(fdsecond[0],buffer,sizeof(buffer));
    printf("Parent is reading message given by the child : %s\n",buffer);
  }
  else {
    close(fdfirst[1]);
    close(fdsecond[0]);

    read(fdfirst[0],buffer,sizeof(buffer));
    printf("Child is reading message given by the parent : %s\n",buffer);

    printf("Child is writing the message\n");
    write(fdsecond[1],message[1],sizeof(message[1]));
  }

  exit(0);
}
