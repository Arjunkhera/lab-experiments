# Basic_Graphics_Algorithms
 
## 1. What is this ? 
  Clean implementations of basic graphics algorithms such as line clipping,dda,bresenham etc in graphics.h.

## 2. Did you say graphics.h ?
  You heard that right, this is not a matter of taste but of historic syllabus that we follow here,in governmental engineering institutes of India. No option but this :(

## 3. But, glut,opengl,unity so much else to do ?
  Stop this, no means no ! ,can't help it.
 
## 4. I pity you !
  Move on.
  
## 5. Okay, so whats in the menu?
  For that check out the index.md in the repository. It will be continuously updated as more and more programs are uploaded in phasewise manner.
  
## 5. Hey, but I see two copies for each program ?
  You got that right,
    1. Header File
    2. The source code
  
  **Note** : 
  The header file is independant of the program file, that is the program file was made first with all the code.
  Later I decided to port it into the header all in one piece. In case if you have come to this repo after reading the scheduling one,      please dont get confused, there the header and cpp were linked. Here they are not.

## 6. So why make a header file then ?
  I had started with the aim of making it in two separate parts, with the source being a part of cpp file. But running it in codeblocks was continuously giving errors. Unable to find a way around, I decided to bundle it all in the header itself. 

  #### If you find a solution to this, please let me know :) 
  
  Hence the primary reason , I chose to upload the source file independantly.

## 7. So how do I run this on my pc ?
  If you are directly copying the source code, then do the work yourself to understand how to call the functions.
  
  Okay, don't have any hard feelings, the source code of every program has a main with the function calls for that respective program.
  
  As far as the header is concerned : 
  1. Open codeblocks.
  2. Make a c++ project by clicking on console application.
  3. Copy the header file in the project folder.
  4. Call the header in main.cpp of your project by typing 
     ```c++
     #include "header_name.h"
     ```
## 8. Cool, but if I want to run it on Ubuntu?
  1. First install libgraph.
  2. Stop being lazy and google for installation instructions.
  3. Simply place the header in the same directory as your main file.
  4. Include it in you file, just like in the instructions for code-blocks.
  
  **Note** : I was able to run my graphics programs in libgraph, but the screen would automatically close after a few seconds. I was unable to fix it, so just be aware of such an issue.

## 9. There are a lot of typos ?
  I am still not well versed with markdown, if you have anything to add or correct make a pull request :)
  
## 10. Got it, also, can I run it in turbo c ?
  Dont know , have'nt tried it yet. Though if you do, then please let everyone know about it by mentioning that here.
  
## 11. Last question, can I contribute ?
  By all means, please do so, this repository needs a lot of help, for example :
  1. Proper header files with separate source code.
  2. Even better, make static libraries.
  3. Make inbuilt helper functions to list the necessary information about call.
  4. Check for errors if any.
  5. Anything else that comes out of the top of your head.
  
  ### and if you have a big heart, do star it :)
  
  
