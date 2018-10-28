#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

class replacement
 {
   int *page,p,n,choice;
   deque <int> table;
   deque<int>::iterator common;
   int page_fault;
   int index;
   bool flag;
   public:
      replacement();
      void traverse();
      void alldisplay();
      void fifo();
      void lru();
      void optimal();
      void replace();
 };

replacement::replacement()
 {
   std::cout<<"Enter the total number of pages in the string : \n";
   std::cin>>p;
   std::cout<<"Enter the number of page slots :  \n";
   std::cin>>n;
   page = new int[p];

   page_fault = n;

   std::cout<<"now enter the page string : ";
   for(int i=0;i<p;i++)
      {
        std::cin>>page[i];
        if (i<n)
            table.push_back(page[i]);
      }

    std::cout<<std::endl;

    std::cout<<"The following are the available page replacement algorithms : \n";
    std::cout<<"1.First in First Out \n";
    std::cout<<"2.Least Recently used \n";
    std::cout<<"3.Optimal replacement \n";

    std::cout<<std::endl;
    std::cout<<"Enter your choice :";
    std::cin>>choice;
    std::cout<<std::endl;
    std::cout<<"---------------------"<<std::endl;
    std::cout<<" Initial state "<<std::endl;
    alldisplay();
    traverse();

 }

void replacement::traverse()
  {
     for(int i = n; i<p ;i++ )
      {
        common = find( table.begin(), table.end(), page[i] );
        index = i;

        flag =  (common != table.end()) ? false :  true ;

        switch (choice)
         {
           case 1: fifo();
                   break;
           case 2: lru();
                   break;
           case 3: optimal();
                   break;
         }

         alldisplay();
      }

      std::cout<<" The total number of page faults were "<<page_fault<<std::endl;

  }

void replacement::alldisplay()
 {
   std::cout<<" PAGE TABLE :  ";

   deque <int>::iterator i = table.begin();

   while( i != table.end() )
    {
      std::cout<<*i<<" ";
      i++;
    }

   std::cout<<std::endl;
   std::cout<<"-----------------------"<<std::endl;
 }

void replacement::fifo()
 {
   if(flag)
    {
      std::cout<<" replacing "<<table.front()<<" with "<<page[index]<<std::endl;

      page_fault++;
      table.pop_front();
      table.push_back(page[index]);

      return;
    }

    std::cout<<" page "<<page[index]<<" already present "<<std::endl;
 }

void replacement::lru()
  {
    if(flag)
     {
       std::cout<<" replacing "<<table.front()<<" with "<<page[index]<<std::endl;

       page_fault++;
       table.pop_front();
       table.push_back(page[index]);

       return;
     }

     std::cout<<" page "<<page[index]<<" already present "<<std::endl;
     replace();

  }

void replacement::replace()
 {
     int temp_value;
     deque <int> temp;

     deque <int>::iterator i = table.end();

     int diff = int(i-common);

     while( diff != 1 )
      {
        temp_value = table.back();
        table.pop_back();
        temp.push_front(temp_value);
        diff--;
      }

      temp_value = table.back();
      table.pop_back();
      temp.push_back(temp_value);

      deque <int>::iterator k = temp.begin();

      while( k != temp.end() )
       {
         table.push_back(*k);
         k++;
       }
 }

void replacement::optimal()
 {
   if(flag)
    {
      int *k;
      int *victim = page+index;

      for(deque<int>::iterator i = table.begin(); i!=table.end() ; i++ )
       {
         k = find( page+index , page+p ,*i );

         if( k > victim)
            {
              victim = k;
              common = i;
            }

         if( victim == page+p )
            break;

       }

      replace();

      std::cout<<" replacing "<<table.back()<<" with "<<page[index]<<std::endl;

      page_fault++;
      table.pop_back();
      table.push_back(page[index]);

      return;

     }

    std::cout<<" page "<<page[index]<<" already present "<<std::endl;

  }

int main()
 {
   replacement r;

   return 0;
 }
