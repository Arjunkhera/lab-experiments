#include<iostream>
#include<thread>
#include<condition_variable>
#include<queue>
#include<cstdlib>
#include<ctime>

using namespace std;

mutex mtx,mux;
condition_variable cv;

#define counter 5
bool ready = false;
bool check = true;

class Semaphore
{
  mutex mtx;
  condition_variable cv;
  int count;
  
  public:
    Semaphore (int count_ = 0)
        : count(count_) {}

    void set(int count_ = 0)
     {
       count = count_;
     }

    inline void signal()
    {
        unique_lock<mutex> lock(mtx);
        count++;
        cv.notify_one();
    }

    inline void wait()
    {
        unique_lock<mutex> lock(mtx);

        while(count == 0){
            cv.wait(lock);
        }
        count--;
    }
};

Semaphore philosopher[counter];
Semaphore print(1);

void initialize()
 {
   for(int i=0;i<counter;i++)
    philosopher[i].set(1);
 }

void run()
{
  unique_lock<mutex> lck(mtx);
  ready = true;
  cv.notify_all();
}

void eat(int i)
 {
   unique_lock<mutex> lck(mtx);
   while(!ready)
   {
     cv.wait(lck);
   }
   lck.unlock();

   philosopher[i].wait();
   philosopher[(i+1)%counter].wait();

   print.wait();
   cout<<" philosopher "<<(i+1)<<" is now eating "<<endl;
   std::this_thread::sleep_for(std::chrono::seconds(1));   //the philosopher is eating
   print.signal();

   philosopher[i].signal();
   philosopher[(i+1)%counter].signal();
 }

int main()
 {
   initialize();
   thread p[counter];

   for(int i=0;i<counter;i++)
    p[i] = thread(eat,i);

   run();

   for(int i=0;i<counter;i++)
    p[i].join();

   return 0;
 }
