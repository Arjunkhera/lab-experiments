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

void writing(struct shared *);
void reading(struct shared *);

// store the key for accessing the shared memory
key_t shm_key = ftok("practical",65);

// the structure for shared memory
struct shared{
  bool the_end = false;
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

  string ch = "yes";
  int choice = -1;
  do{

    cout<<"Enter 1 for writing and 2 for reading :";
    cin>>choice;

    cin.clear();
    fflush(stdin);

    if(choice == 1)
      writing(buffer);
    else if(choice == 2)
      reading(buffer);
    else cout<<"Wrong choice"<<endl;

    cout<<"End of reading/writing. Sleeping for 5 seconds"<<endl;
    sleep(5);
    cout<<"Do you wish to continue(y/n) ? :"<<endl;

    cin.clear();
    fflush(stdin);

    cin>>ch;
    if(ch == "no") break;

  }while(true);


  if(shmdt(buffer) == -1){
     //perror("error in deatching from shared memory");
     return 1;
  }

  if(shmctl(shmid,IPC_RMID,0) == -1){
     //perror("error in destroying the shared memory");
     return 1;
  }

  cout<<"End of this Process"<<endl;
  return 0;
}

void writing(struct shared *buffer){
  if(buffer->the_end){
    cout<<"Some Process already writing"<<endl;
    return;
  }

  buffer->the_end = true;

  cin.clear();
  fflush(stdin);

  // to store the read line
  string inptxt;
  cout<<"Writing into the file"<<endl;
  // read a line
  cin>>inptxt;

  getline(cin,inptxt);
  if(inptxt.empty())
    getline(cin,inptxt);
  cout<<"The input is:"<<inptxt<<endl;

  for(int i = 0;i < inptxt.length();i++)
    buffer->str[i] = inptxt[i];
  buffer->str[inptxt.length()] = '\0';

  buffer->the_end = false;

  cin.clear();
  fflush(stdin);
}

void reading(struct shared *buffer){
    cout<<"Reading from the file"<<endl;
    cout<<buffer->str<<endl;

    return;
}
