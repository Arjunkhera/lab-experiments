#include<iostream>
#include<string>
#include<vector>

using namespace std;

class hamming
 {
   int length;
   int parity_bits;
   vector<char> check_parity;
   bool parity;
   char even;
   public :

   hamming(){};
   string calculate(string);
   string sender(string);
   string converter(string);
   string receiver(string,int);
   void display(string);
 };

string hamming::sender(string data)
 {
   string answer;
   this->parity = true;

   answer = converter(data);
   answer = calculate(answer);

   cout<<"The coded string is : ";
   display(answer);

   return answer;
 }

string hamming::calculate(string answer)
 {
   int k,i,count,j=1,m=1;

   while( m <= this->parity_bits )
    {
        count = 0;
        k = j;
        while( k<= this->length )
         {
           i=1;
           while( k<=this->length && i<=j )
            {
              if(answer[k]=='1')
                count++;
              i++;
              k++;
            }

           if( k>length )
            break;

           k += j;
         }

        if(count%2)
          this->even = '1';
        else this->even = '0';

        if(this->parity)
          answer[j] = this->even;
        else this->check_parity.push_back(this->even);

        j *= 2;
        m++;
    }

   return answer;
 }

string hamming::converter(string data)
 {
   this->parity_bits = 0;
   this->length = data.length();
   string answer = "";

   int i=0;
   int j=1,k=1;
   while(i < length)
   {
     if(k==j)
       {
         answer.push_back('0');
         this->parity_bits+=1;
         j *= 2;
       }
     else
       {
         answer.push_back(data[i]);
         i++;
       }

    k++;
   }

   this->length = answer.length();
   answer = "0" + answer;                // to have 1 indexing

   return answer;
 }

string hamming::receiver(string answer,int bits)
 {
   this->parity_bits = bits;
   this->length = answer.length();

   answer = "0" + answer;  // for 1 indexing
   this->parity = false;
   int temp,check_value = 0;

   answer = calculate(answer);

   int j = 1;
   vector<char>::iterator i = this->check_parity.begin();

   while(i != this->check_parity.end())
    {
      temp = int(*i) - 48;
      check_value += j*temp;

      cout<<" temp is "<<temp<<" check_value is "<<check_value<<endl;

      j *= 2;
      i++;
    }

   if(check_value != 0)
    {
      cout<<"The data is corrupted at bit position "<<check_value<<endl;
      if(answer[check_value] == '0')
        answer[check_value] = '1';
      else answer[check_value] = '0';
    }


   cout<<"The coded string is : ";
   display(answer);

   this->check_parity.clear();
   return answer;
 }

void hamming::display(string data)
 {
   data = data.substr(1,this->length);
   cout<<data<<endl;
 }

int main()
 {
   int choice,bit;
   char ch;
   string data;

   hamming h;

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
        case 1: h.sender(data);
          break;
        case 2: cout<<"Enter the number of parity bits : ";
                cin>>bit;
                h.receiver(data,bit);
          break;
        default : cout<<"wrong choice entered"<<endl;
      };

     cout<<"Do you wish to continue(Y/N) ? "<<endl;
     cin>>ch;
   }while(ch == 'Y' or ch=='y');

   return 0;
 }
