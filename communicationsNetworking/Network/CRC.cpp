#include <iostream>
#include <string>

using namespace std;

string operator ^(string op1, string op2){
  if(op1.size() != op2.size()){
    cout<<"Error!"<<endl;
    exit(1);
  }

  string ans(op1.size()-1,'0');

  for(int i=0;i<op1.size()-1;i++){
    if(op1[i+1]==op2[i+1])
      ans[i]='0';
    else
      ans[i]='1';
  }

  return ans;
}


int main(){

  string data,divisor,temp,dividend;
  int k;

  cout<<"Enter the data: ";
  cin>>data;

  cout<<"Enter the divisor: ";
  cin>>divisor;

  k=divisor.size();
  dividend= data + string(k-1,'0');
  temp=dividend.substr(0,k);

  while(k<dividend.size()){
    if(temp[0]=='1')
      temp= (temp^divisor) + dividend[k];
    else
      temp= (temp^string(temp.size(),'0')) + dividend[k];
    k++;
  }
  if(temp[0]=='1')
    temp= temp^divisor;
  else
    temp= temp^string(temp.size(),'0');

  cout<<"Data to be sent by transmitter is : "<<data+temp<<endl;
  return 0;
}
