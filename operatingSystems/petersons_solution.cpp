#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

bool flag[2];
char turn;

mutex mux1;
mutex mux2;

void first(int num)
 {
  flag[0] = true;
  turn = 'j';

  while ( turn == 'j' && flag[1] == true )
   ;

  mux1.lock();
  std::cout<<" in critical section of i with thread number "<<num<<std::endl;
  mux1.unlock();

  flag[0] = false;
 }

void second(int num)
 {
  flag[1] = true;
  turn = 'i';

  while ( turn == 'i' && flag[0] == true )
   ;

  mux2.lock();
  std::cout<<" in critical section of j with thread number "<<num<<std::endl;
  mux2.unlock();

  flag[1] = false;
 }

int main()
 {
   thread k[3];
   thread j[3];

   for(int i=0;i<3;i++)
    j[i] = thread(second,i);

   for(int i=0;i<3;i++)
    k[i] = thread(first,i);

   for(int i=0;i<3;i++)
    {
      j[i].join();
      k[i].join();
    }

   return 0;
 }
