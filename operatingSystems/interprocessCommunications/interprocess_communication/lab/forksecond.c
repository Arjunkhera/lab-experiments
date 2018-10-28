#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
   	      	
   int common 
   pid_t pid, mypid, myppid;
   pid = getpid();
   printf("Before fork: Process id is %d\n", pid);
   pid = fork();

   if (pid < 0) {
      perror("fork() failure\n");
      return 1;
   }
	
  

   printf("Hoga shaka higa higa : %d\n",getpid());

   // Child process
   if( pid > 0) { // Parent process 
      sleep(2);
      printf("This is parent process\n");
      mypid = getpid();
      myppid = getppid();
      printf("Process id is %d and PPID is %d\n", mypid, myppid);
      printf("Newly created process id or child pid is %d\n", pid);
   } else {
      printf("This is child process\n");
      mypid = getpid();
      myppid = getppid();
      printf("Process id is %d and PPID is %d\n", mypid, myppid);
   }
   return 0;
}
