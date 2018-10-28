# Scheduling_Algorithms

## AIM:
Make a single class to run various popular process scheduling algorithms.

This project was more a result of completing the college assignment.

## Program Specifications :
The current build is capable of running the following process scheduling algorithms:
1. First Come First Serve
2. Shortest Job First 
3. Shortest Remaining Time First 
4. Longest Job First
5. Longest Remaining Time First
6. Round Robin Scheduling

The API for the program is as follows:
```c++
#include "schedule.h"

int main()
 {
  process_table p(6,true,3,6); // round robin scheduling
  std::cout<<std::endl;
  p.gantt();                   // displaying the gantt chart
  std::cout<<std::endl;
 }
```
The arguments to be passed are :

number of processes | Preemptive or Not | Time Quantum | Type of scheduling algorithm
------------------- | ----------------- | ------------ | ----------------------------
int | bool | int | int (Process Id)

The order of accessing various algorithms is as given in the index below, that is 

Process Name                   | Process Id
------------------------------ | ----------
First Come First Serve | 1
Shortest Job First | 2
Shortest Remaining Time First | 3
Longest Job First | 4
Longest Remaining Time First | 5
Round Robin Scheduling | 6

In order to run the script, first place both the header and cpp files in the same project as your file.
Then type in the following command in the terminal :

```
g++ -o test --std=c++11 your_file.cpp schedule.cpp 
```

In case your compiler is updated, you would not have to explicitly specify the compiler version as by default newer versions refer to c++11 or higher.

Now you can run your file by typing :

```
./test
```

## Requested refinements in the project :
1. Add further support for other scheduling algorithms such as priority queue etc.
2. Make a help function to list the required commands for interacting with the classes.
3. Add comments in the file to explaining the purpose of various classes and functions.

I will get back on this after my exams, but any help is appreciated.
