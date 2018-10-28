#include<iostream>
#include<vector>
#include<iomanip>

using namespace std;

class process
 {
   int *max,*need,*allocated,*record_available;
   int finish;

 public:
    void create(int);
    bool check(int,int*);
    int retfin();
    void setfin();
    int* retallot();
    void getdata(int);
    void record(int *,int);
    void display_process(int,int);
 };

int process::retfin()
 {
   return this->finish;
 }

void process::setfin()
 {
   this->finish = 1;
 }

int* process::retallot()
 {
   return this->allocated;
 }

void process::getdata(int r)
 {
   std::cout<<"enter the max resource array  :  ";
   for(int j = 0; j<r ; j++ )
      std::cin>>max[j];

   std::cout<<"enter the allocated resource array : ";
   for(int j = 0 ; j<r ; j++ )
      std::cin>>allocated[j];

   for(int  j = 0 ; j<r ; j++ )
      need[j] = max[j] - allocated[j];
 }

void process::create(int r)
 {
   finish = 0;
   max = new int[r];
   need = new int[r];
   allocated = new int[r];
   record_available = new int[r];
 }

bool process::check(int r,int *available)
  {
    bool index = true;

    for(int i=0;i<r;i++)
      {
        if(need[i]>available[i])
           {
             index = false;
             break;
           }
      }

     return index;
  }

void process::record(int *available,int r)
 {
   for( int i = 0; i<r ; i++ )
    this->record_available[i] = available[i];
 }

void process::display_process(int i,int r)
 {
   std::cout<<" PROCESS "<<i<<" : ";

   std::cout<<setw(5);
   for(int j = 0; j<r ; j++ )
      std::cout<<max[j]<<" ";

   std::cout<<setw(10)<<" || ";

   std::cout<<setw(11);
   for(int j = 0 ; j<r ; j++ )
      std::cout<<allocated[j]<<" ";

   std::cout<<setw(10)<<" || ";

   std::cout<<setw(21);
   for(int j = 0 ; j<r ; j++ )
      std::cout<<record_available[j]<<" ";

   std::cout<<std::endl;

 }

class banker
 {
   int n,r;
   bool flag;
   vector <int> safe;
   process *p;
   int *available;
   public:
      banker();
      int find();
      void recursive();
      void remove(int);
      void display();
      void display_table();
 };

banker::banker()
  {
    std::cout<<"enter the number of processes : ";
    std::cin>>n;
    std::cout<<"enter the number of resources : ";
    std::cin>>r;

    std::cout<<"-----------------------------------"<<std::endl;

    p = new process[n];

    for(int i = 0; i<n ; i++)
      {
        std::cout<<"enter data for process "<<i<<std::endl;
        p[i].create(r);
        p[i].getdata(r);

        std::cout<<"-----------------------------------"<<std::endl;
      }

    available = new int[r];
    std::cout<<"enter the available array : ";
    for(int j = 0 ; j<r ; j++ )
      std::cin>>available[j];

    std::cout<<std::endl;

    recursive();

  }

int banker::find()
 {
    bool comp = true;

    for(int i = 0;i<n;i++)
    {
      if(p[i].retfin()==1)
          continue;

      comp = false;

      if(p[i].check(r,available))
          return i;                         // a waiting process can be handled
    }

    if(comp)
      return -1;                            // all the processes have been finished
    return -2;                              // none of need array less than available, Deadlock
 }

void banker::display()
 {
   std::cout<<std::endl;
   vector <int>::iterator i = safe.begin();
   while(i != safe.end())
    {
      std::cout<<"P"<<*i<<" ";
      i++;
    }
    std::cout<<std::endl;
 }

void banker::display_table()
 {
    std::cout<<setw(25)<<"  MAXIMUM     " ;

    std::cout<<setw(20)<<"  ALLOCATED        " ;

    std::cout<<setw(20)<<"  AVAILABLE ARRAY " ;

    std::cout<<std::endl;

    for( int i = 0; i<n; i++ )
       p[i].display_process(i,r);
 }

void banker::remove(int i)
 {
   p[i].setfin();
   p[i].record(available,r);

   for(int j = 0 ;j<r ;j++ )
      available[j] += p[i].retallot()[j];
 }

void banker::recursive()
 {
   int temp = find();

   if(temp == -2)
    {
      std::cout<<"-----------------------------------"<<std::endl;
      display_table();
      std::cout<<"-----------------------------------"<<std::endl;
      std::cout<<"Deadlock "<<std::endl;
      exit(0);
    }
   else if(temp == -1)
    {
      std::cout<<"-----------------------------------"<<std::endl;
      display_table();
      std::cout<<"-----------------------------------"<<std::endl;
      std::cout<<"The safe state is :"<<std::endl;
      display();
      exit(0);
    }

  safe.push_back(temp);
  remove(temp);
  recursive();

 }

int main()
 {
   banker b;

   return 0;
 }
