# Basic_OS_Algorithms

Clean implementations of basic os algorithms such as synchronization,reader-writer etc.

## Important Notice :  
**Many Students did not have the idea that the synchronisation programs have been executed using pthreads which are used for managing threads on Unix based systems. Morever they also were new to running programs from bash. Unfortunately I came to know of this only on the day of Practical itself. There were also complaints that the code's were one too demanding and ardous to understand.**

**Hence in view of all these facts, I have decided to push a few changes to the repository, namely :**
1. Giving a few command line examples on how to run programs from bash.
2. Links to threads and other inbuilt functions required for synchronisation.  
3. Adding comments to the programs to help the reader understand the working.

**These changes will take some time to implement, but I hope that they will sure help a wider range of audience to grasp the code's better.**


## Programs covered in the repository are as follows :

Implementation of              | File name 
------------------------------ | ----------
Peterson's solution  | petersons_solution.cpp
Producer Consumer Problem | producer_consumer.cpp
Reader Writer Problem | reader_writer.cpp
Dining Philosopher Probelem | dining_philosopher.cpp
Banker's Algorithm | bankers_algorithm.cpp
Page Replacement( fifo,lru,optimal) | page_replacement.cpp
Scheduling Algorithms | refer to schedule.md
File Management | file_system.cpp
Disk Scheduling(all covered in syllabus) | disk_scheduling.cpp

## IMPORTANT : PLEASE ALWAYS WRITE " USING NAMESPACE STD " AT THE STARTING !!

**Note**   
1. **SSTF of disk scheduling is now working properly :)**
2. The scheduling algorithms has been merged from another repository of mine by the same name.   
3. The scheduling algorithms have been implemented in separate files, consult scheduling.md for more details for the same.
4. You can refer [here](https://stackoverflow.com/questions/44134763/how-thread-join-works) to understand thread.join().
5. The file system program has been provided by Dharmesh Singh.

