#include <iostream>
#include <string>
using namespace std;

void stuff(string& stuffed_data){

stuffed_data.push_back('1');
stuffed_data.push_back('1');
stuffed_data.push_back('1');
stuffed_data.push_back('1');
stuffed_data.push_back('1');
stuffed_data.push_back('1');
}
int main(){

string data;
cout<<"Enter data: ";
cin>>data;

string stuffed_data="";
int count=0;
string::iterator i=data.begin();
stuff(stuffed_data);
for(;i!=data.end();i++){

	stuffed_data.push_back(*i);
	if(*i=='1'){
		if(count<4)
			count++;
		else{
			count=0;
			stuffed_data.push_back('0');
		}
	}

	else
		count=0;
}

stuff(stuffed_data);
cout<<"Here is the Bit-Stuffed String: ";
cout<<stuffed_data<<endl;
return 0;
}
