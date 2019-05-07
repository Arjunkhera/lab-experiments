#include<iostream>
#include<graphics.h>

enum Boundary {YMAX=0,YMIN,XMAX,XMIN};
float orx;
float ory;

class liang_barsky
 {
    float p[2][2];
    float store[2][2];
    float box[4];
    float pk[4];
    float qk[4];
    float rk[4];
    float delta_x,delta_y;
    float u_left,u_right;
    int condition;

    public :

    liang_barsky();
    void set();
    void setr();
    bool checkslope();
    bool checkzero();
    void clip();
    void clipping();
    void setpoint();
    void display();

 };

liang_barsky::liang_barsky()
 {
    condition = 0;

    std::cout<<"Enter the coordinates of the viewing window : "<<std::endl;

    std::cout<<"Enter the maximum y coordinate :";
    std::cin>>box[YMAX];

    std::cout<<"Enter the minimum y coordinate :";
    std::cin>>box[YMIN];

    std::cout<<"Enter the maximum x coordinate :";
    std::cin>>box[XMAX];

    std::cout<<"Enter the minimum x coordinate :";
    std::cin>>box[XMIN];

    std::cout<<"Enter the coordinates of the first point of line :";
    std::cin>>p[0][0]>>p[0][1];

    std::cout<<"Enter the coordinates of the second point of line :";
    std::cin>>p[1][0]>>p[1][1];


    store[0][0] = p[0][0];
    store[0][1] = p[0][1];
    store[1][0] = p[1][0];
    store[1][1] = p[1][1];

    u_left = 0;
    u_right = 1;

    set();
    clip();

 }

void liang_barsky::set()
 {
    delta_x = p[1][0] - p[0][0];
    delta_y = p[1][1] - p[0][1];

    pk[0] = -delta_x;
    pk[1] = delta_x;
    pk[2] = -delta_y;
    pk[3] = delta_y;

    qk[0] = p[0][0] - box[XMIN];
    qk[1] = box[XMAX] - p[0][0];
    qk[2] = p[0][1] - box[YMIN];
    qk[3] = box[YMAX] - p[0][1];
 }

void liang_barsky::setr()
 {
     rk[0] = qk[0]/pk[0];
     rk[1] = qk[1]/pk[1];
     rk[2] = qk[2]/pk[2];
     rk[3] = qk[3]/pk[3];
 }

bool liang_barsky::checkzero()
 {
     for( int i=0; i<4; i++)
        if( pk==0 && qk<0 )
            return true;

     return false;
 }

bool liang_barsky::checkslope()
 {
     for(int i = 0; i<4; i++)
        if( pk[i] == 0)
            {
                if( delta_y == 0 )
                 {
                   p[0][0] = box[XMIN];
                   p[1][0] = box[XMAX];
                 }
                else
                {
                   p[0][1] = box[YMIN];
                   p[1][1] = box[YMAX];
                }

               return true;
            }

     return false;
 }

void liang_barsky::clip()
 {
    if(checkzero())
        {
            condition = 2;
            goto jump;
        }
    if(checkslope())
        {
            condition = 1;
            goto jump;
        }
    setr();

    for( int k = 0; k<4 ; k++ )
    {
        if( pk[k] < 0 )
        {
            if ( rk[k] > u_left )
                u_left = rk[k];
        }
        else {
                if ( rk[k] < u_right )
                    u_right = rk[k];
             }
    }

    if ( u_left > u_right )
        {
            condition = 2;
            goto jump;
        }

    condition = 1;

    clipping();

    jump:
    display();

 }

void liang_barsky::clipping()
 {
     p[0][0] = store[0][0] + delta_x*u_left;
     p[0][1] = store[0][1] + delta_y*u_left;

     p[1][0] = store[0][0] + delta_x*u_right;
     p[1][1] = store[0][1] + delta_y*u_right;

 }

void liang_barsky::setpoint()
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

      box[YMAX] = ory - box[YMAX];
      box[YMIN] = ory - box[YMIN];
      box[XMAX] = orx + box[XMAX];
      box[XMIN] = orx + box[XMIN];

  }

void liang_barsky::display()
 {

    setpoint();

    line(box[XMIN],box[YMIN],box[XMIN],box[YMAX]);
    line(box[XMIN],box[YMIN],box[XMAX],box[YMIN]);
    line(box[XMAX],box[YMIN],box[XMAX],box[YMAX]);
    line(box[XMIN],box[YMAX],box[XMAX],box[YMAX]);

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

     liang_barsky lb;

     return 0;
 }
