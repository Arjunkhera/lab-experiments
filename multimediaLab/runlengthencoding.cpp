#include<iostream>
#include<string>

using namespace std;

string runlength(string str){

  int runlength = 1;
  string answer = "";

  auto i = str.begin();
  for(; i != str.end()-1;i++){

    if(*i == *(i+1)){
      runlength++;
      continue;
    }

    answer = answer + *i + to_string(runlength);
    runlength = 1;

  }
  answer = answer + *i + to_string(runlength);

  return answer;
}

int main(){

  string str;
  cout<<"enter the string to be encoded :\n";
  cin>>str;

  string encoded = runlength(str);
  cout<<"The encoded string is : "<<encoded<<endl;

  return 0;
}
