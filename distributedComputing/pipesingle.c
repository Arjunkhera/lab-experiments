#include<stdio.h>
#include<unistd.h>

int main(){

  int status,pid,fd[2];
  char message[2][50] = { "written by parent","written by child"};
  char buffer[100];

  // create a pipe
  status = pipe(fd);
  if(status == -1){
    printf("Unable to create a pipe\n");
    exit(1);
  }

  pid = fork();

  if(pid < 0){
    printf("Unable to create a child procces \n");
    exit(1);
  }
  else if(pid > 0){
    printf("I am the parent and I am writing a message in the pipe\n");
    write(fd[1],message[0],sizeof(message[0]));

    wait(NULL);
  }
  else {
    printf("Reading from the pipe\n");
    read(fd[0],buffer,sizeof(buffer));

    printf("Hey I am in child and I read this from the pipe\n");
    printf("%s\n",buffer);
  }

  exit(0);
}
