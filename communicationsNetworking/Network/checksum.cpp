#include <iostream>
#include <string>

using namespace std;


string operator*(string op1,string op2){
	
	if(op1.size()!=op2.size()){
		cout<<"Error cannot add"<<endl;
		exit(1);
	}

	string answer(op1.size(),'0');
	
	bool carry=false;
	bool ans,a,b;

	int temp;

	for(int i=op1.size()-1;i>=0;i--){
	
		temp=op1[i]-'0';
		if(temp<0 || temp>1){
			cout<<"Data contains characters other than 0 or 1"<<endl;
			exit(1);
		}		
		
		a=bool(temp);

		temp=op2[i]-'0';
		if(temp<0 || temp>1){
			cout<<"Data contains characters other than 0 or 1"<<endl;
			exit(1);
		}

		b=bool(temp);

		ans=a^b^carry;
		carry= (a&b) | (b&carry) | (carry&a);

		answer[i]=(ans?'1':'0');
	}

	if( /* (answer.compare(string(op1.size(),'1'))!=0) &&*/ carry ){

	      string op3=string(op1.size(),'0');
	      op3[op1.size()-1]='1';
	      answer=answer*op3;
	}

	return answer;
}

string operator!(string& op){

	string answer(op.size(),'0');
	for(int i=0;i<op.size();i++)
		answer[i]= (!(op[i]-'0') + '0');

	return answer;

}
int main(){

	string data,recieved;
	int k;

	cout<<"Enter the size of checksum: ";
	cin>>k;
	
	cout<<"Enter the data sent by the transmitter: ";
	cin>>data;

	if(data.size()%k!=0){
		cout<<"Cannot divide the data sent in size of checksum!! Aborting"<<endl;
		exit(1);
	}

	cout<<"Enter the data recieved by the reciever: ";
	cin>>recieved;

	if(data.size()+k!=recieved.size()){
		cout<<"Sizes of Data sent and recieved inconsistent!! Aborting"<<endl;
		exit(1);
	}

	//finding the data that should have been recieved;
	string checksum(k,'0');

	for(int i=0;i<data.size();i+=k){
		checksum=checksum*data.substr(i,k);
	}
	checksum=(!checksum);
	
	cout<<"Checksum: "<<checksum<<endl;

	//correct data that should have been recieved
	data=data+checksum;
	
	checksum=string(k,'0');
	for(int i=0;i<recieved.size();i+=k){
		checksum=checksum*recieved.substr(i,k);
	}
	checksum=(!checksum);
	bool correct=true;

	for(int i=0;i<k;i++)
		if(checksum[i]=='1'){
			correct=false;
			break;
		}

	if(correct)
		cout<<"According to CheckSum procedure, the data is correct"<<endl;

	else
		cout<<"The Data recieved is corrupt. It should have been "<<data<<". Call for retransmission;)"<<endl;


	return 0;
}
