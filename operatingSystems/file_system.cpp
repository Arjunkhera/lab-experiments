// THIS PROGRAM WAS PROVIDED BY DHARMESH SINGH

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

int main()
{
	int choice;
	string buffer;
	fstream myfile;
	myfile.open("./oslab.txt");
	char key;

	do{
		myfile.clear();

		cout<<endl;
		cout<<" Available  options are as follows : ";
		cout<<endl<<"1. read date from the file : ";
		cout<<endl<<"2. write data into the file : ";
		cout<<endl<<"3. append the file ";

		cin>>choice;

		myfile.seekg(0,ios::beg);
		myfile.seekp(0,ios::beg);

		switch(choice)
		{
			case 1: while(getline(myfile,buffer))
				{
					cout<<buffer<<endl;
				}
				cout<<endl;
				break;

			case 2: myfile.close();
			  myfile.open("./oslab.txt",ios::in | ios::trunc | ios::out);
				cout<<"\nEnter what you want to write in the file: "<<endl;
				cin.ignore(1,'\n');
				getline(cin,buffer);
				myfile<<buffer;
				myfile<<endl;
				myfile.close();
				myfile.open("./oslab.txt");
				break;

			case 3: myfile.seekp(0,ios::end);
				cout<<"\nEnter what you want to append in the file: "<<endl;
				cin.ignore(1,'\n');
				getline(cin,buffer);
				myfile<<buffer;
				myfile<<endl;
				break;
		}

		cout<<endl;
		cout<<" do you want to continue (y/n): ";
		cin>>key;
		key=toupper(key);

	}while(key!='N');

	myfile.close();
	return 0;
}
