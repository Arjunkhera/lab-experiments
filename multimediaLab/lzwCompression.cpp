#include<iostream>
#include<vector>

using namespace std;

int isPresent(string str,vector<string> &dictionaryStrings){

  bool flag = false;
  auto i = dictionaryStrings.begin();

  for(; i != dictionaryStrings.end(); i++)
    if(*i == str){
      flag = true;
      break;
    }

  if(!flag)
    return -1;

  return (i-dictionaryStrings.begin());
}

void encode(string str,vector<string> &dictionaryStrings,vector<int> &dictionaryIndices,vector<int> &output){

  string::iterator i = str.begin();
  string temp = "";
  int j = 256;
  int index,found;

  while(i != str.end()){

    temp = *i;

    if(i+1 == str.end()){
      output.push_back(int(*i));
      return;
    }

    temp = temp + *(i+1);

    while(i != str.end()){

      index = isPresent(temp,dictionaryStrings);
      if(index == -1)
        break;

      found = index;
      i++;

      if(i+1 == str.end()){
        output.push_back(dictionaryIndices[found]);
        return;
      }

      temp = temp + *(i+1);
    }

    if(temp.length() == 2){
      output.push_back(int(*i));
      dictionaryStrings.push_back(temp);
      dictionaryIndices.push_back(j++);
    }
    else{
      output.push_back(dictionaryIndices[found]);
      dictionaryStrings.push_back(temp);
      dictionaryIndices.push_back(j++);
    }

    i++;
  }
}

void decode(vector<int> &output,vector<string> &dictionaryStrings,vector<int> &dictionaryIndices){

  for(auto i = output.begin(); i != output.end();i++)
    if(*i > 255)
      cout<<dictionaryStrings[*i - 256];
    else cout<<char(*i);

}

int main(){

  string str;

  cout<<"The string to be encoded is : ";
  cin>>str;
  cout<<str<<endl;

  vector<string> dictionaryStrings;
  vector<int> dictionaryIndices;
  vector<int> output;

  encode(str,dictionaryStrings,dictionaryIndices,output);

  cout<<"The output string is as follows : "<<endl;
  for(auto i : output)
    cout<<"<"<<i<<">";
  cout<<endl;

  cout<<"The decoded string is : ";
  decode(output,dictionaryStrings,dictionaryIndices);

  cout<<endl;
}
