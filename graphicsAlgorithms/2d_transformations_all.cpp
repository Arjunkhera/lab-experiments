#include<iostream>
#include<graphics.h>
#include<stdio.h>
#include<cmath>

# define pi 3.14159

using namespace std;

int orx;
int ory;

class point
 {
     int x,y;
     int fx,fy;
 public :
     point();
     void setpoint();
     void pbegin();
     void pend();
     void rotate(double);
     void scale(int);
     void translate(int,int);
     void reflectx();
     void reflect(int,int);
     void plot(bool,int);
     void plot_side(point,int,bool);

 };

point::point()
 {
     cout<<"Enter the x coordinate for the point : ";
     cin>>x;
     cout<<endl;
     cout<<"Enter the y coordinate for the point : ";
     cin>>y;
     cout<<endl;

     setpoint();     // for normalizing the coordinates with respect to the display screen
 }

void point::setpoint()
 {
     x = x + orx;
     y = ory - y;
 }

void point::pbegin()
 {
     fx = this->x - orx;        // for translating the points to the origin
     fy = this->y - ory;
 }

void point::pend()
 {
     fx = fx + orx;             // for translating the points back to the initial point
     fy = fy + ory;
 }

void point::rotate(double angle)
 {
    int xtemp = fx;
    int ytemp = fy;

    fx = xtemp*cos(angle) - ytemp*sin(angle);
    fy = xtemp*sin(angle) + ytemp*cos(angle);
 }

void point::scale(int factor)
 {
    fx = fx*factor;
    fy = fy*factor;
 }

void point::translate(int tx,int ty)
 {
    fx = fx + tx;
    fy = fy + ty;
 }

void point::reflectx()
 {
     fy = -fy;
 }

void point::reflect(int m,int b)
 {
     double angle = atan(m);

     translate(0,-b);
     rotate(-angle);
     reflectx();
     rotate(angle);
     translate(0,b);

 }

void point::plot(bool test,int col)
 {
     if(test)
        {
            setcolor(col);
            line(orx,ory,x,y);
        }

     setcolor(col);
     line(orx,ory,fx,fy);
 }

void point::plot_side(point p,int col,bool test)
 {
     if(test)
        {
            setcolor(col);
            line(this->x,this->y,p.x,p.y);
        }

     setcolor(col);
     line(this->fx,this->fy,p.fx,p.fy);
 }

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





