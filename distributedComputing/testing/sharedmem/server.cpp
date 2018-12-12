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

  // open the file for reading the input
  ifstream fin("input.txt");
  // check for errors in opening the file
  if(!fin){
    cerr<<"Error in opening the file"<<endl;
    exit(1);
  }

  // to store the read line
  string inptxt;
  cout<<"Reading contents from file\n"<<endl;

  while(fin){
    // read a line
    getline(fin,inptxt);

    // exit the loop if string is empty
    if(inptxt == "\0") break;

    for(int i = 0;i < inptxt.length();i++)
      buffer->str[i] = inptxt[i];
    buffer->str[inptxt.length()] = '\0';

    cout<<"This was written : "<<inptxt<<endl;
    sleep(3);
  }
  cout<<"Closing the file"<<endl;
  fin.close();

  // marks the end of writing into shared memory
  buffer->the_end = true;

  if(shmdt(buffer) == -1){
     perror("error in deatching from shared memory");
     return 1;
  }

  if(shmctl(shmid,IPC_RMID,0) == -1){
     perror("error in destroying the shared memory");
     return 1;
  }

  cout<<("Writing Completed")<<endl;
  return 0;
}
