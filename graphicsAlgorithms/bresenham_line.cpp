# include <iostream>
# include <graphics.h>

class bresenham
 {
     bool flag;
     float orx,ory;
     float x1,x2,y1,y2;
     float dx,dy;
     float slope;

     float posinc,neginc,p;
     float constant_change,variable_change,stop;

     public :
         bresenham();
         void initialize();
         void plotaxis();
         void slope_x();
         void slope_y();
         void plot_points();
 };

bresenham::bresenham()
 {
     initialize();

     std::cout<<"Enter the first set of coordinates for the line "<<std::endl;
     std::cin>>x1>>y1;

     std::cout<<"Enter the second set set of coordinates for the line "<<std::endl;
     std::cin>>x2>>y2;

     dx = abs(x1 - x2);
     dy = abs(y1 - y2);

     if(x1 == x2)
        {
            line(x1+orx,ory-y1,x1+orx,ory-y2);
            getch();
            exit(0);
        }
     slope = (y1 - y2)/(x1 - x2);

     if( slope > -1 && slope < 1 )
       {
         flag = true;
         slope_x();
       }
     else
       {
         flag = false;
         slope_y();
       }

     plot_points();
 }

void bresenham::slope_x()
 {
        posinc = 2 * (dy - dx);
        neginc = 2 * dy;
        p = 2 * dy - dx;

        if ( x1 > x2 )
            {
                constant_change = x2;
                variable_change = y2;
                stop = x1;
            }
        else
            {
                constant_change = x1;
                variable_change = y1;
                stop = x2;
            }
 }

void bresenham::slope_y()
 {
        posinc = 2 * (dx - dy);
        neginc = 2 * dx;
        p = 2 * dx - dy;

        if ( y1 > y2 )
            {
                variable_change = x2;
                constant_change = y2;
                stop = y1;
            }
        else
            {
                variable_change = x1;
                constant_change = y1;
                stop = y2;
            }
 }

void bresenham::plot_points()
 {

     if(flag)
        putpixel(orx+constant_change,ory-variable_change,12);
     else
        putpixel(orx+variable_change,ory-constant_change,12);

     while (constant_change <= stop)
        {
            constant_change++;

            if ( p < 0 )
                p = p + neginc;
            else
            {
                p = p + posinc;

                if ( slope > 0.0 )
                    variable_change++;
                else
                    variable_change--;
            }

            if(flag)
                putpixel(orx+constant_change,ory-variable_change,12);
            else
                putpixel(orx+variable_change,ory-constant_change,12);
        }
 }

void bresenham::plotaxis()
 {
     line(0,ory,2*orx,ory);
     line(orx,0,orx,2*ory);
 }

void bresenham::initialize()
 {
    int gd = DETECT,gm;
    initgraph(&gd,&gm,"");

    orx = getmaxx()/2;
    ory = getmaxy()/2;

    plotaxis();
 }

int main()
 {
     bresenham b;
     getch();
     return 0;
 }
