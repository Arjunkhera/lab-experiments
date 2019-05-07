#include<iostream>
#include<graphics.h>

class motion
 {
     float height;
     float radius;
     int orx,x;
     float ory;

     float d,inc;
     int color = 0;
     float acceleration = 10;

     public :
         motion();
         void initialize();
         void cycle();
         void downward();
         void upward();

 };

motion::motion()
 {
     initialize();

     std::cout<<"The maximum height of the box is "<<ory<<std::endl;

     std::cout<<"Enter the height of the ball from the ground ";
     std::cin>>height;

     std::cout<<std::endl;

     std::cout<<"Enter the radius of the ball ";
     std::cin>>radius;

     d = height;
     inc = 0;
     x = 10;

     cycle();
 }

void motion::initialize()
 {
    int gd = DETECT,gm;
    initgraph(&gd,&gm,"");

    orx = getmaxx();
    ory = getmaxy();
 }

void motion::cycle()
 {
    while( height > radius )
        downward();
 }

void motion::downward()
 {
    while( d > radius )
    {

        setcolor(WHITE);
        circle(x,ory-d,radius);

        color = (color + 3)%14;

        setcolor(color);
        setfillstyle(SOLID_FILL,color);
        floodfill(x,ory-d,WHITE);

        d -= inc ;
        x = (x+5)%orx;

        delay(10);
        cleardevice();

        inc++;
    }

    upward();
 }

void motion::upward()
 {
    float temp = 0.8 * height;

    if( temp < d )
        {
            setcolor(WHITE);
            circle(x,ory-radius,radius);

            setcolor(color);
            setfillstyle(SOLID_FILL,color);
            floodfill(x,ory-radius,WHITE);


            height = radius;
            return;
        }
    while( d < temp )
    {
        setcolor(WHITE);
        circle(x,ory-d,radius);

        color = (color + 3)%14;

        setcolor(color);
        setfillstyle(SOLID_FILL,color);
        floodfill(x,ory-d,WHITE);

        d += inc ;
        x = (x+5)%orx;

        delay(10);
        cleardevice();

        inc--;
    }

    height = d;
    inc = 0;
 }

int main()
 {
     motion m;
     getch();
     return 0;
 }
