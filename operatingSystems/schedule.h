#ifndef __schedule_H_INCLUDED__
#define __schedule_H_INCLUDED__

enum ATTRIBUTES {PID=0,AT,BT,CT,TAT,WT,TR};
extern int schtype;

class process;
class compare;
class process_table;

#include<iostream>
#include<iomanip>
#include<queue>
#include<vector>
#include<list>

class process
 {
     int attributes[7];
 public:
     void getdata();
     void display();
     void calculate();
     friend class process_table;
     friend class compare;
 };

class compare
    {
    public:
      bool operator()(process const &a,process const &b)
       {
         if(schtype==2 || schtype==3)
           {
               if (a.attributes[TR]>b.attributes[TR])
                 return true;
               else if  (a.attributes[TR] == b.attributes[TR])
                     {
                       if (a.attributes[AT]>b.attributes[AT])
                         return true;
                       else if  (a.attributes[AT] == b.attributes[AT])
                             {
                               if (a.attributes[PID]>b.attributes[PID])
                                 return true;
                               else
                                 return false;
                             }
                       else return false;
                     }
               else
                 return false;
           }
         else
          {
            if (a.attributes[TR]<b.attributes[TR])
             return true;
           else if  (a.attributes[TR] == b.attributes[TR])
                 {
                   if (a.attributes[AT]>b.attributes[AT])
                     return true;
                   else if  (a.attributes[AT] == b.attributes[AT])
                         {
                             if (a.attributes[PID]>b.attributes[PID])
                               return true;
                             else
                               return false;
                         }
                   else
                     return false;
                 }
           else
             return false;
           }
       }
    };

class process_table
     {
         bool quant;
         bool robin;
         int quantum;
         int total;
         int criteria;
         process *table;
         std::list <process> readyqueue;
         std::priority_queue <process,std::vector<process>,compare> sidequeue;
         std::vector <int> time_gantt;
         std::vector <int> pid_gantt;
         process robint;

     public:
         process_table(int,bool,int,int);
         void start();
         int perform(int);
         void delay();
         bool checkbreak();
         void sort(ATTRIBUTES);
         void alldisplay();
         void gantt();

         friend class compare;
     };

#endif
