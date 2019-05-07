# include <iostream>
# include <graphics.h>

class midpoint_circle
 {
     float orx,ory;
     float radius;

     float p;

     public :
         midpoint_circle();
         void initialize();
         void plotaxis();
         void plot_points();
 };

midpoint_circle::midpoint_circle()
 {
     std::cout<<"Enter the radius of the circle "<<std::endl;
     std::cin>>radius;

     p = (5/4) - radius;

     initialize();
     plot_points();
 }

void midpoint_circle::plot_points()
 {
     float xtemp = 0;
     float ytemp = radius;

     while ( xtemp <= ytemp )
        {
            if ( p < 0 )
                p = p + 2*xtemp + 3;
            else
            {
                p = p + 2*(xtemp - ytemp) + 6;
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

void midpoint_circle::plotaxis()
 {
     line(0,ory,2*orx,ory);
     line(orx,0,orx,2*ory);
 }

void midpoint_circle::initialize()
 {
    int gd = DETECT,gm;
    initgraph(&gd,&gm,"");

    orx = getmaxx()/2;
    ory = getmaxy()/2;

    plotaxis();
 }

int main()
 {
     midpoint_circle m;
     getch();
     return 0;
 }


