#include<iostream>
#include<graphics.h>
#include<cmath>

class coin
 {
     double orx,ory;
     double radius;
     double x,y;
     double d;
     double phi,theta;
     int color;

     public :
         coin();
         void initialize();
         void plotaxis();
         void rotate_coin();
         void calculate();
 };

coin::coin()
 {
     std::cout<<"Enter the radius of the coin : ";
     std::cin>>radius;

     color = 0;

     initialize();
     rotate_coin();
 }

void coin::calculate()
 {
     for(double j = 0; j<=180; j= j+0.25 )
     {
         phi = j;

         d = radius*sin(phi);

         x = d*cos(theta);
         y = radius*cos(phi);

        putpixel(orx+x,ory-y,WHITE);
        putpixel(orx-x,ory-y,WHITE);
     }
 }

void coin::rotate_coin()
 {
     for(double j = 0; j<=90; j= j+0.40 )
     {
       theta = j;

       calculate();

       color = ( color + 1 ) % 14;

       setcolor(color);
       setfillstyle(SOLID_FILL,color);
       floodfill(orx,ory,WHITE);

       delay(10);
       cleardevice();
     }
 }

void coin::plotaxis()
 {
     line(0,ory,2*orx,ory);
     line(orx,0,orx,2*ory);
 }

void coin::initialize()
 {
    int gd = DETECT,gm;
    initgraph(&gd,&gm,"");

    orx = getmaxx()/2;
    ory = getmaxy()/2;

 }

int main()
 {
     coin c;
     getch();
     return 0;
 }


