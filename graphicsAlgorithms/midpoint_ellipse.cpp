# include <iostream>
# include <graphics.h>

class midpoint_ellipse
 {
     float orx,ory;
     float rx,ry;
     float x,y;

     float p;

     public :
         midpoint_ellipse();
         void initialize();
         void plotaxis();
         void plot_region1();
         void plot_region2();
 };

midpoint_ellipse::midpoint_ellipse()
 {
     std::cout<<"Enter the x major and y major of the ellipse "<<std::endl;
     std::cin>>rx>>ry;

     initialize();
     plot_region1();
 }

void midpoint_ellipse::plot_region1()
 {
     x = 0;
     y = ry;

     float check = 2*ry*ry*x - 2*rx*rx*y;

     p = ry*ry - rx*rx*ry + (rx*rx)/4;

     while ( check <= 0 )
        {
            if ( p < 0 )
                p = p + ry*ry*( 2*x + 3);
            else
            {
                p = p + ry*ry*( 2*x + 3) + rx*rx*( 2 - 2*y );
                y = y - 1;
            }

            x++;

            putpixel(orx+x,ory-y,8);
            putpixel(orx+x,ory+y,9);
            putpixel(orx-x,ory-y,10);
            putpixel(orx-x,ory+y,11);

            check = 2*ry*ry*x - 2*rx*rx*y;
        }
     plot_region2();
 }

void midpoint_ellipse::plot_region2()
 {
     p = (x + 0.5)*ry*ry + (y-1)*rx*rx - rx*rx*ry*ry;

     while ( y >= 0 )
        {
            if ( p > 0 )
                p = p + rx*rx*( 3 - 2*y );
            else
            {
                x = x + 1;
                p = p + rx*rx*( 3 - 2*y ) + 2*ry*ry*x;
            }

            y--;

            putpixel(orx+x,ory-y,12);
            putpixel(orx+x,ory+y,13);
            putpixel(orx-x,ory-y,14);
            putpixel(orx-x,ory+y,15);
        }

 }

void midpoint_ellipse::plotaxis()
 {
     line(0,ory,2*orx,ory);
     line(orx,0,orx,2*ory);
 }

void midpoint_ellipse::initialize()
 {
    int gd = DETECT,gm;
    initgraph(&gd,&gm,"");

    orx = getmaxx()/2;
    ory = getmaxy()/2;

    plotaxis();
 }

int main()
 {
     midpoint_ellipse e;
     getch();
     return 0;
 }



