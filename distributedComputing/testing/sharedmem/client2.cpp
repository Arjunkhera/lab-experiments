// for c++ related functions
#include<iostream>
#include<fstream>
#include<string>

// for c related functions
#include<cstdio>
#include<cstdlib>
#include<unistd.h>

// for system calls
#include<sys/types.h>
#include<sys/ipc.h>
// for shared memory
#include<sys/shm.h>

using namespace std;

// store the key for accessing the shared memory
key_t shm_key = ftok("practical",65);

// the structure for shared memory
struct shared{
  bool the_end = false;
  int count = 0;
  char str[1024];
};

int main(){

  // create the shared memory
  int shmid = shmget(shm_key,sizeof(shared),0666|IPC_CREAT);
  if(shmid == -1){
    perror("Error in creating shared memory");
    return 1;
  }

  // attach server to the shared memory
  struct shared *buffer = (shared*)shmat(shmid,NULL,0);
  if(buffer == (void *) -1){
     perror("Unable to attach to shared memory");
     return 1;
  }

  // to store the read line
  cout<<"Reading contents from shared memory\n"<<endl;

  int initial = 0;
  while(!buffer->the_end){
    cout<<buffer->str<<endl;
    sleep(3);
  }

  if(shmdt(buffer) == -1){
     perror("error in deatching from shared memory");
     return 1;
  }

  cout<<"Reading Completed"<<endl;
  return 0;
}
