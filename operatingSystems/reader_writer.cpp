#include<iostream>
#include<thread>
#include<condition_variable>
#include<queue>
#include<cstdlib>
#include<ctime>
#include<chrono>

using namespace std;

mutex mux;
mutex mtx;
condition_variable cv;

int counter = 0;
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
        unique_lock<mutex> lock(mtx);
        count++;
        cv.notify_one();
    }

    inline void wait()
    {
        unique_lock<mutex> lock(mtx);

        while(count == 0)
        {
            cv.wait(lock);
        }
        count--;
    }
};

Semaphore read(1);
Semaphore write(1);

void run()
{
  unique_lock<mutex> lck(mtx);
  ready = true;
  cv.notify_all();
}

void reader(int index)
 {
   mutex print;
   unique_lock<mutex> lck(mtx);
   while(!ready)
   {
     cv.wait(lck);
   }
   lck.unlock();

   read.wait();
   counter = counter + 1;
   if(counter == 1)
    write.wait();
   cout<<" Reader "<<index<<" entering, number of active readers are : "<<counter<<endl;
   read.signal();

   std::this_thread::sleep_for(std::chrono::seconds(3));   // the reader is reading

   read.wait();
   counter = counter -1;
   if(counter == 0)
    write.signal();
   cout<<" Reader "<<index<<" is leaving, number of active readers are : "<<counter<<endl;
   read.signal();

 }

void writer(int index)
  {
    unique_lock<mutex> lck(mtx);
    while(!ready)
    {
      cv.wait(lck);
    }
    lck.unlock();

    write.wait();
    cout<<" Writer "<<index<<" is now writing"<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));   // the writer is writing
    write.signal();
  }

int main()
 {
   int rd,wr;
   srand((int)time(0));

   cout<<"Enter the number of Readers : ";
   cin>>rd;
   cout<<endl;

   cout<<"Enter the number of Writers : ";
   cin>>wr;
   cout<<endl;

   thread r[rd];
   thread w[wr];

   for(int i=0;i<rd;i++)
    r[i] = thread(reader,i+1);

   for(int i=0;i<wr;i++)
    w[i] = thread(writer,i+1);

   run();

   for(int i=0;i<rd;i++)
    r[i].join();

   for(int i=0;i<wr;i++)
    w[i].join();

   return 0;
 }
