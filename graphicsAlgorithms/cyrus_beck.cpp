#include<iostream>
#include<graphics.h>
#include<cmath>
#include<limits>

float orx;
float ory;

class cyrus_beck
 {
    float p[2][2];
    float store[2][2];
    int n;

    float *boxx,*boxy;
    float t_min,t_max;

    float f[2];
    float normal[2];
    float weight[2];
    float delta[2];

    float dot,numerator,value;
    int condition;

    public :

    cyrus_beck();
    void clip();
    void normal_calculate(int);
    void clipping();
    void setpoint();
    void display();

 };

cyrus_beck::cyrus_beck()
 {
    condition = 0;

    std::cout<<"Enter the number of vertices of the viewing window : "<<std::endl;
    std::cin>>n;

    std::cout<<"Enter the coordinates of the viewing window : "<<std::endl;

    boxx = new float[n];
    boxy = new float[n];

    for(int i=0; i<n; i++)
    {
        std::cout<<" vertex number "<<i+1<<" : ";
        std::cin>>boxx[i]>>boxy[i];
        std::cout<<std::endl;
    }

    std::cout<<"Enter the coordinates of the first point of line :";
    std::cin>>p[0][0]>>p[0][1];

    std::cout<<"Enter the coordinates of the second point of line :";
    std::cin>>p[1][0]>>p[1][1];


    store[0][0] = p[0][0];
    store[0][1] = p[0][1];
    store[1][0] = p[1][0];
    store[1][1] = p[1][1];

    delta[0] = p[1][0] - p[0][0];
    delta[1] = p[1][1] - p[0][1];

    t_min = INT_MIN;
    t_max = INT_MAX;

    clip();
 }

void cyrus_beck::normal_calculate(int j)
 {
    float temp[2];
    float check;

    temp[0] = boxx[(j+1)%n] - boxx[j];
    temp[1] = boxy[(j+1)%n] - boxy[j];

    normal[1] = temp[0];
    normal[0] = -temp[1];

    check = ( temp[0]*normal[1] ) - ( temp[1]*normal[0] );

    if( check<0 )
        {
            normal[1] = -temp[0];
            normal[0] = temp[1];
        }
 }

void cyrus_beck::clip()
 {
     for(int j =0; j<n; j++)
     {

        f[0] = boxx[j];
        f[1] = boxy[j];

        weight[0] = store[0][0] - f[0];
        weight[1] = store[0][1] - f[1];

        normal_calculate(j);

        numerator = normal[0]*weight[0] + normal[1]*weight[1];
        dot = normal[0]*delta[0] + normal[1]*delta[1];

        if(dot!=0)
            value = (-numerator)/dot;
        else value = INT_MAX;

        if( dot > 0 )
        {
            if( value>t_min)
                t_min = value;
        }
        else
        {
            if( value<t_max)
                t_max = value;
        }

     }

     clipping();
 }

void cyrus_beck::clipping()
 {
     if( (t_min < 0) || (t_min>1) || (t_max<0)|| (t_max>1) )
        {
            condition = 2;
            goto jump;
        }

     condition = 1;

     p[0][0] = store[0][0] + delta[0]*t_min;
     p[0][1] = store[0][1] + delta[1]*t_min;

     p[1][0] = store[0][0] + delta[0]*t_max;
     p[1][1] = store[0][1] + delta[1]*t_max;


     jump:
     display();
 }

void cyrus_beck::setpoint()
  {
      for(int i=0;i<2;i++)
       {
           p[i][0] = p[i][0] + orx;
           p[i][1] = ory - p[i][1];
       }

       for(int i=0;i<2;i++)
       {
           store[i][0] = store[i][0] + orx;
           store[i][1] = ory - store[i][1];
       }
  }

void cyrus_beck::display()
 {

    setpoint();

    setcolor(12);
    for(int i=0;i<n;i++)
        line(orx+boxx[i],ory-boxy[i],orx+boxx[(i+1)%n],ory-boxy[(i+1)%n]);

    setcolor(2);
    setlinestyle(3,0,3);
    line(store[0][0],store[0][1],store[1][0],store[1][1]);

    setcolor(14);
    setlinestyle(0,0,3);
    if(condition == 1)
        line(p[0][0],p[0][1],p[1][0],p[1][1]);

    getch();
    closegraph();
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

int main()
 {
     initialize();

     cyrus_beck cb;

     return 0;
 }

