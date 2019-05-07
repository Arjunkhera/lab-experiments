#include <iostream>
#include <string>
#include <math.h>
using namespace std;

int main(){
  string data,recieved;
  bool temp;
  cout<<"Enter the data to be sent and recieved: ";
  cin>>data>>recieved;

  int k=1;
  while(true){
    if(pow(2,k) >= data.size() +k +1)
      break;
    k++;
  }

  if(data.size() +k != recieved.size()){
    cout<<"Data sizes not consistent"<<endl;
    exit(1);
  }


  string dataT(data.size()+k,'0');
  int parityPos=1,i,j=0,t,s;
  int m=data.size()+k;

  reverse(data.begin(),data.end());
  reverse(recieved.begin(),recieved.end());
  for(i=0;i<data.size()+k;i++){
    if(parityPos==i+1){
      parityPos*=2;
      continue;
    }
    dataT[i]=data[j++];
  }

  for(i=0;i<k;i++){
    parityPos=pow(2,i);
    temp=false;
    for(j=parityPos; j<=m; j+=2*parityPos){
      for(t=j;t<j+parityPos;t++){
        if(dataT[t-1]=='0')
          temp^=false;
        else
          temp^=true;
      }
    }
    dataT[parityPos-1]=(temp?'1':'0');
  }
  reverse(dataT.begin(),dataT.end());
  cout<<"Data to be transmitted: "<<dataT<<endl;

  string check(k,'0');
  for(i=0;i<k;i++){
    parityPos=pow(2,i);
    temp=false;
    for(j=parityPos; j<=m; j+=2*parityPos){
      for(t=j;t<j+parityPos;t++){
        if(recieved[t-1]=='0')
          temp^=false;
        else
          temp^=true;
      }
    }
    check[i]=(temp?'1':'0');
  }
  long int dec=0;
  int mul=1;
  for(i=0;i<k;i++){
    dec+=(check[i]-'0')*mul;
    mul*=2;
  }
  cout<<"The position which is dirty is : "<<dec<<endl;
}
