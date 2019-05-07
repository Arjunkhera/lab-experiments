#include<iostream>
#include<string>

using namespace std;

class bit_stuffing
 {
   int length,length_interrupt;
   string flag;
   string interrupt;

   public :

   bit_stuffing(string);
   string sender(string);
   string receiver(string);
   void display(string);
 };

bit_stuffing::bit_stuffing(string flag)
 {
   this->flag = flag;
   this->length = flag.length();

   interrupt = flag.insert(length-1,"0");
   this->length_interrupt = interrupt.length();

   //to check the value that the flag will be converted to
   // display(interrupt);
 }

string bit_stuffing::sender(string data)
 {
   int i;
   string answer = "";
   size_t position,len;

   while(1)
    {
      len = data.length();
      position = data.find(flag);

      if( position == string::npos )
        {
          answer.append(data);
          break;
        }

      i = 0;
      while( i != position )
       {
         answer.push_back(data[i]);
         i++;
       }
      i += this->length;
      answer.append(this->interrupt);

      if( i >= len)
        break;

      data = data.substr(i,len-i);
    }
   answer = flag + answer + flag;

   cout<<"The converted string is : ";
   display(answer);
   return answer;
 }

string bit_stuffing::receiver(string data)
 {
   int i;
   string answer = "";
   size_t position,len;

   len = data.length();
   data = data.substr(this->length,len-2*this->length); //removing flags

   while(1)
    {
      len = data.length();
      position = data.find(interrupt);

      if( position == string::npos )
        {
          answer.append(data);
          break;
        }

      i = 0;
      while( i != position )
       {
         answer.push_back(data[i]);
         i++;
       }
      i += this->length_interrupt;
      answer.append(this->flag);

      if( i >= len)
        break;

      data = data.substr(i,len-i);
    }

   cout<<"The original string was : ";
   display(answer);
   return answer;
 }

void bit_stuffing::display(string str)
 {
   cout<<str<<endl;
 }

int main()
 {
   int choice;
   char ch;
   string data,flag;

   cout<<"Enter the flag being used by the protocol :";
   cin>>flag;

   bit_stuffing bit(flag);

   do
   {
     cout<<"Enter your choice : "<<endl;
     cout<<"1.Stuff the data"<<endl;
     cout<<"2.Retrieve the data"<<endl;
     cin>>choice;

     cout<<"Enter the data :";
     cin>>data;
     cout<<endl;

     switch(choice)
      {
        case 1: bit.sender(data);
          break;
        case 2: bit.receiver(data);
          break;
        default : cout<<"wrong choice entered"<<endl;
      };

     cout<<"Do you wish to continue(Y/N) ? "<<endl;
     cin>>ch;
   }while(ch == 'Y' or ch=='y');

   return 0;
 }
