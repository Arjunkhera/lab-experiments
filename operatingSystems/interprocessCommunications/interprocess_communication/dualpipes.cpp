#include<bits/stdc++.h>
#include<unistd.h>

using namespace std;

int main(){

  pid_t pid;
  int fid[2],secfid[2],size;

  string message = "Your name is : ";
  string *output = new string(message.size(),'0');
  string *final = new string(30,'0');

  if(pipe(fid) == -1){
    std::cerr<<"Failed to open the pipe\n";
    return 1;
  }
  if(pipe(secfid) == -1){
    std::cerr<<"Failed to open the pipe\n";
    return 1;
  }

  pid = fork();

  if(pid > 0){
    close(fid[0]);
    // cout<<"The message being sent is : "<<message;
    write(fid[1],&message,sizeof(message));
    close(fid[1]);

    wait();

    close(secfid[1]);
    read(secfid[0],final,size);
    cout<<"\nSo here is the result \n";
    cout<<final;
    close(secfid[0]);
  }
  else if(pid == 0){
    close(fid[1]);
    read(fid[0],output,sizeof(message));
    string temp;
    cout<<*output;
    cin>>temp;
    string tosend = *output + temp;
    size = sizeof(tosend);
    cout<<"\nIn child : "<<tosend;

    close(fid[0]);
    close(secfid[0]);
    write(secfid[0],&tosend,sizeof(tosend));

    cout<<"\nfinished working in child\n";
  }
  else{
    cerr<<"abort !!\n";
  }

  return 0;
}
