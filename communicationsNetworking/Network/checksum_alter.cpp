#include <iostream>
#include <string>
#include <bitset>
#define M 8

using namespace std;


bitset<M> operator+(bitset<M>& a,bitset<M>& b){

	bitset<M> c(0);
	bool carry=false;

	for(int i=0;i<M;i++){

		c[i]=int(bool(a[i])^bool(b[i])^carry);
		carry=bool(a[i])&&bool(b[i]) || bool(b[i])&&carry || carry&&bool(a[i]);

	}
	
	return c;
}

bitset<M> operator!(bitset<M>& a){

	bitset<M> c(0);
	for(int i=0;i<M;i++)
		c[i]=~a[i];

	return c;
}
int main(){

	string data,recieved;
	int k_,i;

	cout<<"Enter the size of checksum: ";
	cin>>k_;
	cout<<"Enter the data sent by the transmitter: ";
	cin>>data;
	
	int const &k=k_;
	if(data.size()%k!=0){
		cout<<"Cannot Divide the data into size of "<<k<<"!!! Exiting"<<endl;
		exit(1);
	}

	cout<<"Enter the data recieved by the transmitter: ";
	cin>>recieved;

	if(data.size()+k!=recieved.size()){
		cout<<"Lenght of data sent and recieved inconsistent!!! Exiting"<<endl;
	}

	bitset<k> checksum(0);
	//finding the ideal data that should have been recieved
	for(int i=0;i<data.size()/k;i+=k){
		checksum=checksum+bitset<k>(data.substr(i,k));
	}
	checksum=(!checksum);

	//ideal data that should have been recieved
	data=data+checksum.to_string(char);


	//checking at reciever that whether the recieved data is correct or not
	checksum=bitset<k>(0);
	for(int i=0;i<recieved.size()/k;i+=k){
		checksum=checksum+bitset<k>(recieved.substr(i,k));
	}
	checksum=(!checksum);

	if(checksum.to_ulong!=0)
		cout<<"The recieved data is corrupted. Ideally, it should have been "<<data<<endl;

	else
		cout<<"According to CheckSum procedure, the recieved data is correct"<<endl;

	return 0;
}
