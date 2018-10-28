#include<iostream>
#include<thread>
#include<condition_variable>
#include<queue>
#include<cstdlib>
#include<ctime>

using namespace std;

mutex mux;
mutex mtx;
condition_variable cv;

#define buffersize 7                          
int counter;
queue<int> buffer;
bool ready = false;

class Semaphore
{
  mutex mtx;
  condition_variable cv;
  int count;

  public:
    Semaphore (int count_ = 0)
        : count(count_) {}

    inline void signal()
    {
        unique_lock<mutex> lock(mtx);       //to make the statement atomic
        count++;
        cv.notify_one();
    }

    inline void wait()
    {
        unique_lock<mutex> lock(mtx);

        while(count == 0)                   //to prevent spurious wake ups
        {
            cv.wait(lock);
        }
        count--;
    }

};

Semaphore empty(buffersize);
Semaphore full(0);

void run(){
  unique_lock<mutex> lck(mtx);
  ready = true;
  cv.notify_all();
}

void producer()
 {
   unique_lock<mutex> lck(mtx);
   while(!ready)                             //to prevent spurious wake ups
   {
     cv.wait(lck);
   }
   lck.unlock();

   int item = rand()%7;

   empty.wait();
   mux.lock();
   buffer.push(item);
   cout<<" Producer produced  "<<item<<endl;
   mux.unlock();
   full.signal();
 }

void consumer()
  {
    unique_lock<mutex> lck(mtx);
    while(!ready)                           //to prevent spurious wake ups
    {
      cv.wait(lck);
    }
    lck.unlock();

    int item;

    full.wait();
    mux.lock();
    item = buffer.front();
    buffer.pop();
    cout<<" Consumer consumed  "<<item<<endl;
    mux.unlock();
    empty.signal();
  }

int main()
 {
   int prod,cons;
   srand((int)time(0));

   cout<<"Enter the number of Producers : ";
   cin>>prod;
   cout<<endl;

   cout<<"Enter the number of Consumers : ";
   cin>>cons;
   cout<<endl;

   thread p[prod];
   thread c[cons];

   for(int i=0;i<prod;i++)
    p[i] = thread(producer);

   for(int i=0;i<cons;i++)
    c[i] = thread(consumer);

   run();

   for(int i=0;i<prod;i++)
    p[i].join();

   for(int i=0;i<cons;i++)
    c[i].join();

   return 0;
 }
