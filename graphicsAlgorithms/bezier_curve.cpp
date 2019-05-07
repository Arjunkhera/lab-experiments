#include<iostream>
#include<graphics.h>
#include<cmath>

float orx,ory;

void plotaxis()
 {
     line(0,ory,2*orx,ory);
     line(orx,0,orx,2*ory);
 }

void initialize()
 {
    int gd = DETECT,gm;
    initgraph(&gd,&gm,"");

    orx = getmaxx()/2;
    ory = getmaxy()/2;

    plotaxis();
 }

class bezier
 {
     int n;
     int k;
     int *pointx;
     int *pointy;
     float comb;
     float u;

     public :
         bezier();
         void combination();
         void calculate();
         void cycle();
 };

bezier::bezier()
 {
     std::cout<<"Enter the number of control points that you want ";
     std::cin>>n;

     n--;

     pointx = new int[n+1];
     pointy = new int[n+1];

     std::cout<<"Enter the control points "<<std::endl;

     for ( int i = 0; i<(n+1); i++)
     {
         std::cin>>pointx[i];
         std::cin>>pointy[i];
     }

     comb = 1;
     k = 0;
     u = 0;

     cycle();

 }

void bezier::combination()
 {
     if ( k == 0 || k == n )
        comb = 1;
     else
        comb = comb * ( (n-k+1)/k );
 }

void bezier::calculate()
 {
     double p_x = 0;
     double p_y = 0;

     for( int j = 0; j<(n+1); j++)
     {
        combination();

        p_x = p_x + ( comb * pow(u,k) * pow(1-u,n-k) * pointx[k] );
        p_y = p_y + ( comb * pow(u,k) * pow(1-u,n-k) * pointy[k] );

        k++;
     }

     k = 0;
     comb = 1;
     putpixel(orx + p_x,ory - p_y,12);

 }

void bezier::cycle()
 {
    u = 0;
    while( u<=1 )
    {
        calculate();
        u = u + 0.01;
    }
 }

int main()
 {
     initialize();
     bezier b[2];

     getch();
     return 0;
 }
