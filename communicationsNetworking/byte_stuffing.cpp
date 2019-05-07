#include<iostream>
#include<string>

using namespace std;

class byte_stuffing
 {
   int length,length_esc;
   string flag,escape;
   string interrupt;

   public :

   byte_stuffing(string,string);
   string sender(string);
   string receiver(string);
   void display(string);
 };

byte_stuffing::byte_stuffing(string flag,string escape)
 {
   this->flag = flag;
   this->length = flag.length();

   this->escape = escape;
   this->length_esc = escape.length();
 }

string byte_stuffing::sender(string data)
 {
   bool check;
   int i,local_length;
   string answer = "";
   size_t position,position_flag,position_escape,len;

   while(1)
    {
      check = true;
      len = data.length();
      position_flag = data.find(flag);
      position_escape = data.find(escape);

      if( position_flag == string::npos && position_escape == string::npos)
        {
          answer.append(data);
          break;
        }

      if(position_flag < position_escape)
       {
        check = false;
        position = position_flag;
        local_length = this->length;
       }
      else
       {
         position = position_escape;
         local_length = this->length_esc;
       }

      i = 0;
      while( i != position )
       {
         answer.push_back(data[i]);
         i++;
       }
      answer.append(this->escape);
      if(check)
        answer.append(this->escape);
      else answer.append(this->flag);

      i += local_length;

      if( i >= len)
        break;

      data = data.substr(i,len-i);
    }
   answer = flag + answer + flag;

   cout<<"The converted string is : ";
   display(answer);
   return answer;
 }

string byte_stuffing::receiver(string data)
 {
   bool check;
   int i;
   string answer = "";
   size_t position,position_flag,position_escape,len;

   len = data.length();
   data = data.substr(this->length,len-2*this->length); //removing flags

   while(1)
    {
      check = true;
      len = data.length();
      position_flag = data.find(flag);
      position_escape = data.find(escape);

      if( position_escape == string::npos)
        {
          answer.append(data);
          break;
        }

      position = position_escape;
      i = 0;
      while( i != position )
       {
         answer.push_back(data[i]);
         i++;
       }
      i += this->length_esc;
      if( i == position_flag)
        {
          answer.append(this->flag);
          i += this->length;
        }
      else {
        answer.append(this->escape);
        i += this->length_esc;
      }

      if( i >= len)
        break;

      data = data.substr(i,len-i);
    }

   cout<<"The converted string is : ";
   display(answer);
   return answer;
 }

void byte_stuffing::display(string str)
 {
   cout<<str<<endl;
 }

int main()
 {
   int choice;
   char ch;
   string data,flag,escape;

   cout<<"Enter the flag being used by the protocol :";
   cin>>flag;
   cout<<"Enter the Escape character being used by the protocol :";
   cin>>escape;

   byte_stuffing byte(flag,escape);

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
        case 1: byte.sender(data);
          break;
        case 2: byte.receiver(data);
          break;
        default : cout<<"wrong choice entered"<<endl;
      };

     cout<<"Do you wish to continue(Y/N) ? "<<endl;
     cin>>ch;
   }while(ch == 'Y' or ch=='y');

   return 0;
 }
