# include <iostream>
# include <graphics.h>

class bresenham_circle
 {
     float orx,ory;
     float radius;

     float p;

     public :
         bresenham_circle();
         void initialize();
         void plotaxis();
         void plot_points();
 };

bresenham_circle::bresenham_circle()
 {
     std::cout<<"Enter the radius of the circle "<<std::endl;
     std::cin>>radius;

     p = 3 - 2*radius;

     initialize();
     plot_points();
 }

void bresenham_circle::plot_points()
 {
     float xtemp = 0;
     float ytemp = radius;

     while ( xtemp <= ytemp )
        {
            if ( p < 0 )
                p = p + 4*xtemp + 6;
            else
            {
                p = p + 4*(xtemp - ytemp) + 10;
                ytemp = ytemp - 1;
            }

            xtemp++;

            putpixel(orx+xtemp,ory-ytemp,8);
            putpixel(orx+xtemp,ory+ytemp,9);
            putpixel(orx-xtemp,ory-ytemp,10);
            putpixel(orx-xtemp,ory+ytemp,11);
            putpixel(orx+ytemp,ory-xtemp,12);
            putpixel(orx+ytemp,ory+xtemp,13);
            putpixel(orx-ytemp,ory-xtemp,14);
            putpixel(orx-ytemp,ory+xtemp,15);

        }
 }

void bresenham_circle::plotaxis()
 {
     line(0,ory,2*orx,ory);
     line(orx,0,orx,2*ory);
 }

void bresenham_circle::initialize()
 {
    int gd = DETECT,gm;
    initgraph(&gd,&gm,"");

    orx = getmaxx()/2;
    ory = getmaxy()/2;

    plotaxis();
 }

int main()
 {
     bresenham_circle b;
     getch();
     return 0;
 }

