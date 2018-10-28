#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class disk
 {
    int n,max,min;
    int choice;
    int initial, direction;
    vector<int> request_queue;
    vector<int>::iterator start,pointer;
    int distance;
    bool ready,circular;

    public :
     disk();
     void fcfs();
     void SSTF();
     void not_fcfs_right();
     void not_fcfs_left();
     void display();
 };

disk::disk()
 {
   int temp;

   distance = 0;

   cout<<"Enter the total number of requests : ";
   cin>>n;

   cout<<"Enter the requests in order : ";

   for(int i = 0; i<n; i++)
      {
        cin>>temp;
        request_queue.push_back(temp);
      }

   cout<<"The following are the available page replacement algorithms : \n";
   cout<<"1.First Come First Serve \n";
   cout<<"2.SCAN  \n";
   cout<<"3.CSCAN \n";
   cout<<"4.LOOK  \n";
   cout<<"5.CLOOK \n";
   cout<<"6.SSTF \n";

   cout<<endl;
   cout<<"Enter your choice :";
   cin>>choice;
   cout<<endl;
   cout<<"---------------------"<<std::endl;

   if( choice !=1 && choice!=6 )
     {
       cout<<endl;
       cout<<"Enter the maximum limit of the disk : ";
       cin>>max;

       cout<<"Enter the minimum limit of the disk : ";
       cin>>min;

       cout<<"Enter the Initial request being serviced : ";
       cin>>initial;

       cout<<"Enter the direction of Initial movement { 0 : right, 1 : left } : ";
       cin>>direction;
       cout<<endl;

       sort(request_queue.begin(),request_queue.end());
       pointer = find(request_queue.begin(),request_queue.end(),initial);
       start = pointer;

       ready = false;
       if( choice == 3 || choice == 5 )
         circular = true;
       else circular = false;

       if( direction )
         not_fcfs_left();
       else not_fcfs_right();

     }

   if( choice==1 )
      fcfs();

   if( choice==6 )
      SSTF();

   display();

 }

void disk::SSTF()
 {
   cout<<"Enter the initial request being serviced : ";
   cin>>initial;

   int counter = n-1;
   int condition = 0;

   vector<int>::iterator left,right,check;

   sort(request_queue.begin(),request_queue.end());
   pointer = find(request_queue.begin(),request_queue.end(),initial);

   while( counter > 0 )
   {
     left = pointer - 1;
     right = pointer +1;

     if(pointer != request_queue.end() - 1)
        { while( right != request_queue.end() )
           {
            if(*right != 0)
                break;
            right++;
           }
           if( right == request_queue.end())
             condition = 1;
        }
      else condition = 1;

     if(pointer != request_queue.begin())
         { while( left != request_queue.begin())
            {
             if(*left != 0)
                  break;
             left--;
           }
           if(left == request_queue.begin() && *left== 0)
            condition = 2;
         }
     else condition = 2;

     if( condition == 1 )
      check = left;
     else if( condition == 2 )
      check = right;
     else {
            if( abs(*right - *pointer) > abs(*pointer - *left)  )
              check = left;
            else check = right;
          }


    distance += abs(*check - *pointer);
    *pointer = 0;
    pointer = check;
    counter--;
   }
 }

void disk::fcfs()
 {
   vector<int>::iterator i = request_queue.begin();

   while( (i+1) != request_queue.end() )
    {
      distance += abs( *(i+1) - *i );
      i++;
    }
 }

void disk::not_fcfs_right()
 {
    vector<int>::iterator j = pointer;

    if( ready && circular )
     {
       while( (j+1) != start )
          {
            distance += ( *(j+1) - *j );
            j++;
          }
       return;
     }

    if( j == request_queue.end() - 1 )
     goto skip;


    while( (j+1) != request_queue.end())
       {
         distance += ( *(j+1) - *j );
         j++;
       }

    if( ready )
      return;

    skip:
    ready = true;

    if( choice == 2 || choice == 3 )
      distance += ( max - request_queue.back() );

    if( choice == 3 || choice == 5 )
     {
          if( choice == 3 )
           {
             distance += ( max - min );
             distance += ( request_queue.front() - min );
           }

          if( choice == 5 )
             distance += ( request_queue.back() - request_queue.front() );

          pointer = request_queue.begin();

          not_fcfs_right();
          return;
     }

     if( start == request_queue.begin())
      return;

     if ( choice == 2 )
        distance += ( max - request_queue.back() );

     pointer = start - 1;
     distance += ( request_queue.back() - *pointer );

     not_fcfs_left();

  }

void disk::not_fcfs_left()
 {
   vector<int>::iterator j = pointer;

   if( ready && circular )
    {
      while( (j-1) != start )
         {
           distance += ( *j - *(j-1) );
           j--;
         }
      return;
    }

   if( j == request_queue.begin())
    goto skip;

   while( (j-1) != request_queue.begin())
      {
        distance += ( *j - *(j-1) );
        j--;
      }

   distance += ( *j - *(j-1) );
   j = request_queue.begin();

   if( ready )
    return;

   skip:
   ready = true;

   if( choice == 2 || choice == 3 )
     distance += ( request_queue.front() - min );

   if( choice == 3 || choice == 5 )
    {
         if( choice == 3 )
          {
            distance += ( max - min );
            distance += ( max - request_queue.back() );
          }

         if( choice == 5 )
            distance += ( request_queue.back() - request_queue.front()  );

         pointer = request_queue.end() - 1;

         not_fcfs_left();
         return;
    }

    if( start == request_queue.end() - 1 )
     return;

    if ( choice == 2 )
      distance += ( request_queue.front() - min );

    pointer = start + 1;
    distance += ( *pointer - request_queue.front() );

    not_fcfs_right();

 }

void disk::display()
 {
   cout<<"The total distance traversed is "<<distance<<endl;
 }

int main()
 {
   disk d;
   return 0;
 }
