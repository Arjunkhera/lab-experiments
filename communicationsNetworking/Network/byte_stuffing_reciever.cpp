#include <iostream>
#include <string>
using namespace std;

int main(){

	string stuffed_data,data;

	char flag,esc;

	cout<<"Enter flag: ";
	cin>>flag;
	cout<<"Enter Escape Sequence: ";
	cin>>esc;
	cout<<"Enter recieved data: ";
	cin>>stuffed_data;

	int isesc=0,i=0,j,escaped=0;

	cout<<"Data Frames extracted are: "<<endl;
	
	while(i<stuffed_data.size()){
	

		if(escaped){
			cout<<stuffed_data[i];
			escaped=0;
			i++;
			continue;
		}

		else if(stuffed_data[i]==esc){
			escaped=1;
			i++;
			continue;
		}

		else if(stuffed_data[i]==flag){
			cout<<endl;
			i++;
			continue;
		}
		cout<<stuffed_data[i];	
		i++;
	}
	return 0;
}
