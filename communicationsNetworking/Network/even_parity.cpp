#include <iostream>
#include <string>

using namespace std;

int main(){

	string data,recieved;
	cout<<"Enter the data to be transmitted: ";
	cin>>data;
	cout<<"Enter the data recieved by the reciever: ";
	cin>>recieved;

	if(recieved.size() != data.size()+1){
		cout<<"Size of data recieved and transmitted inconsistent!!! Exiting"<<endl;
		exit(1);
	}

	bool parity=false;
	int temp;
	for(int i=0;i<data.size();i++)
	{
		temp=data[i]-'0';
		if(temp<0 || temp>1){
			cout<<"The data contains characters other than 0 and 1!!! Exiting"<<endl;
			exit(1);
		}
		parity^=bool(temp);
	}

	data.push_back(parity?'1':'0');

	bool new_parity=false;
	for(int i=0;i<recieved.size();i++)
	{
		temp=recieved[i]-'0';
		if(temp<0 || temp>1){
			cout<<"The data contains characters other than 0 and 1!!! Exiting"<<endl;
			exit(1);
		}
		new_parity^=bool(temp);
	}
	if(!new_parity){
		cout<<"According to Even-Parity-Check procedure the above recieved data is correct"<<endl;
	}
	else
		cout<<"The above recieved data is corrupted. The recieved packet should be "<<data<<". Call for Retransmission"<<endl;
	return 0;
}
