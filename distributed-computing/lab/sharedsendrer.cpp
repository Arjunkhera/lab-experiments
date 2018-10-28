#include <iostream> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <cstdio> 

using namespace std; 
  
int main() { 
    // ftok to generate unique key 
    key_t key = ftok("shmfile",65); 
  
    // shmget returns an identifier in shmid 
    int shmid = shmget(key,1024,0666|IPC_CREAT); 
	
    // check for error
    if(shmid == -1){
		cout<<"Unable to access the shared memory\n";
		exit(1);
	}
  
    // shmat to attach to shared memory 
    char *str = (char*) shmat(shmid,(void*)0,0); 
  
    cout<<"Write Data : "; 
    gets(str); 
  
    printf("Data written in memory: %s\n",str); 
      
    //detach from shared memory  
    shmdt(str); 
  
    return 0; 
} 

