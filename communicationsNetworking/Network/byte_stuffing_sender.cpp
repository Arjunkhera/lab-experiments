#include <iostream>
#include <string>
using namespace std;

int main(){

	string data,stuffed_data;
	char flag,esc;

	cout<<"Enter the flag: ";
	cin>>flag;
	cout<<"Enter the Escape : ";
	cin>>esc;
	cout<<"Now Enter the Data: ";
	cin>>data;


	stuffed_data.push_back(flag);
	int i=0;
	for(;i<data.size();i++){
		if(data[i]==flag || data[i]==esc)
			stuffed_data.push_back(esc);
		stuffed_data.push_back(data[i]);
	}
	stuffed_data.push_back(flag);
	cout<<"Stuffed Data: "<<stuffed_data<<endl;

return 0;
}
