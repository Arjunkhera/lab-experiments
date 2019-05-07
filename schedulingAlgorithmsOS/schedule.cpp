#include "schedule.h"

int schtype;

void process::getdata()
 {
    std::cout<<"Enter process id:";
    std::cin>>attributes[PID];
    std::cout<<"Enter arrival time: ";
    std::cin>>attributes[AT];
    std::cout<<"Enter burst time: ";
    std::cin>>attributes[BT];

    attributes[TR] = attributes[BT];
 }

void process::display()
 {
  std::cout<<std::endl;
  std::cout<<std::setw(5)<<attributes[PID]<<"|"<<std::setw(5)<<attributes[AT]<<" | "<<std::setw(5)<<attributes[BT]<<" | "<<std::setw(5)<<attributes[CT]<<" | "<<std::setw(5)<<attributes[TAT]<<" | "<<std::setw(5)<<attributes[WT]<<" | ";
 }

void process::calculate()
  {
    attributes[TAT] = attributes[CT] - attributes[AT];
    attributes[WT] = attributes[TAT] - attributes[BT];
    display();
  }

process_table::process_table(int n,bool quantb,int quantumb,int criteriab)
 {
      quant = quantb;
      robin = false;

      if(quant)
        quantum = quantumb;
      else quantum = 1;

      total = n;
      table = new process[n];
      criteria = criteriab;
      schtype = criteria;

      for(int i=0;i<total;i++)
         table[i].getdata();


      sort(AT);
      start();
 }

void process_table::start()
 {
   bool decide;
   int time = 0;
   int index = 0;
   int jump = 0;

   while(true)
    {

      while( (index<total) && (table[index].attributes[AT] <= time) )
       {
         readyqueue.push_back(table[index]);
         sidequeue.push(table[index]);
         index++;
       }

      if(robin)
       {
         readyqueue.push_back(robint);
         robin = false;
       }

      decide = checkbreak();

      if(decide && index>=total)
        break;

      if(decide && index<total)
        {
          time++;
          continue;
        }

      jump = perform(time);
      time += jump;

    }
 }

int process_table::perform(int time)
 {
   int jump;
   process j;

   if(quant)
    {
      switch(criteria)
       {
          case 6 :  j = readyqueue.front();
                    readyqueue.pop_front();
                    break;

          case 3 :
          case 5 : j = sidequeue.top();
                   sidequeue.pop();
                   break;
       }

       if(j.attributes[TR] <= quantum)
        {
          jump = j.attributes[TR];
          j.attributes[CT] = time + jump;
          j.attributes[TR] = 0;
          j.calculate();
          pid_gantt.push_back(j.attributes[PID]);
          time_gantt.push_back(j.attributes[CT]);

        }
       else {
              jump = quantum;
              j.attributes[TR] -= quantum;
              pid_gantt.push_back(j.attributes[PID]);
              time_gantt.push_back(time+jump);

              switch(criteria)
                {
                    case 6 :  robin = true;
                              robint = j;
                              break;
                    case 3 :
                    case 5 : sidequeue.push(j);
                             break;
                }

            }
    }
   else
    {
      switch(criteria)
        {
          case 1 :  j = readyqueue.front();
                    readyqueue.pop_front();
                    break;
          case 2 :
          case 4 :  j = sidequeue.top();
                    sidequeue.pop();
                    break;
        }

    j.attributes[CT] = time + j.attributes[BT];
    j.attributes[TR] = 0;
    j.calculate();

    jump = j.attributes[BT];

     }

    return jump;
    }

bool process_table::checkbreak()
 {
     if(criteria==1 || criteria==6)
      { if(readyqueue.empty())
          return true;
        else
          return false;
      }

     if(sidequeue.empty())
        return true;
     else
        return false;

 }

void process_table::sort(ATTRIBUTES at)
 {
    for(int i=0;i<total-1;i++)
    {
        for(int j=0;j<total-i-1;j++)
        {
            if(table[j].attributes[at]>table[j+1].attributes[at])
            {
                process temp = table[j];
                table[j] = table[j+1];
                table[j+1] = temp;
            }
        }
    }
 }

void process_table::alldisplay()
 {
   std::cout<<std::endl;
   std::cout<<std::setw(5)<<"PID"<<"|"<<std::setw(5)<<"AT"<<" | "<<std::setw(5)<<"BT"<<" | "<<std::setw(5)<<"CT"<<" | "<<std::setw(5)<<"TAT"<<" | "<<std::setw(5)<<"WT"<<" | ";

   for (int i=0;i<total;i++)
      table[i].display();

   std::cout<<std::endl;
 };

void process_table::gantt()
 {
   std::cout<<std::endl;
   for(std::vector<int> ::iterator i = pid_gantt.begin();i!=pid_gantt.end();i++)
      std::cout<<std::setw(5)<<*i<<" | ";

   std::cout<<std::endl;
   for(std::vector<int> ::iterator i = time_gantt.begin();i!=time_gantt.end();i++)
      std::cout<<std::setw(5)<<*i<<" | ";
 }
