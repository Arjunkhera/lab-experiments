#include <iostream>
#include <string>
using namespace std;
string CRC_gen(const string divisor,string dividend)
{
	string copy_dividend=dividend;
	for(int i=0;i<divisor.size()-1;i++)	copy_dividend+="0";
	for(int i=0;i<dividend.size();i++)
	{
		if(copy_dividend[i]!='0')
		{
			int p=divisor.size();
			while(p)
			{
				copy_dividend[i+p-1]='0'+((copy_dividend[i+p-1]-'0')^(divisor[p-1]-'0'));
				p--;
			}
		}
	}
	string CRC=copy_dividend.substr(copy_dividend.size()-divisor.size()+1,divisor.size()-1);
	return CRC;

}
void CRC_correction(const string divisor, string dividend)
{
	for(int i=0;i<dividend.size()-divisor.size()+1;i++)
	{
		if(dividend[i]!='0')
		{
			int p=divisor.size();
			while(p)
			{
				dividend[i+p-1]='0'+((dividend[i+p-1]-'0')^(divisor[p-1]-'0'));
				p--;
			}
		}
	}
	string CRC=dividend.substr(dividend.size()-divisor.size()+1,divisor.size()-1);
	bool check=true;
	for(int i=0;i<CRC.size();i++)
	{
		if(CRC[i]=='1')	check=false;
	}
	if(check)	cout<<"NO ERROR" << endl;
	else	cout<<"ERROR...Resend the data" << endl;
}
int main()
{
	string divisor, dividend;
	cout<<"AT SENDER END"<<endl;
	cout<<"******************************************"<<endl;
	cout<<"Enter Divisor      : ";
	getline(cin,divisor);
	cout<<"Enter Dataword     : ";
	getline(cin,dividend);
	string CRC=CRC_gen(divisor,dividend);
	dividend+=CRC;
	cout<<"Generated CRC Code : "<< CRC << endl;
	cout<<"Data to be transmitted : " << dividend<<endl;
	cout<<"******************************************"<<endl;
	cout<<"Transmission..."<<endl;
	cout<<"AT RECIEVER END"<<endl;
	cout<<"******************************************"<<endl;
  /*
	if(dividend[5]=='0')	dividend[5]='1';
	else	dividend[5]='0';
	*/
	
	cout<<"Received Data          : ";
	cout<<dividend<<endl;

	CRC_correction(divisor,dividend);
}
