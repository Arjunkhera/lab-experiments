#include<bits/stdc++.h>
#include<unistd.h>

using namespace std;

int main(){

  pid_t pid;
  int fid[2];

  string message = "hello i am a resident of parent";
  int size = sizeof(message);
  string *output = new string(message.size(),'0');

  if(pipe(fid) == -1){
    std::cerr<<"Pipe Failed\n";
    return 1;
  }

  pid = fork();

  if(pid > 0){
    cout<<"The message being sent is : "<<message;
    write(fid[1],&message,size);

    wait();
  }
  else if(pid == 0){
    read(fid[0],output,size);
    cout<<"\nI am reading the output in child : ";
    cout<<*output;
    cout<<"\nfinished reading\n";
  }
  else{
    cerr<<"abort !!\n";
  }

  return 0;
}
