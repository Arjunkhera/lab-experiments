#include<iostream>
#include<graphics.h>

using namespace std;

enum Boundary {YMAX=0,YMIN,XMAX,XMIN};
int orx;
int ory;

class cohen
 {
    float p[2][2];
    float store[2][2];
    float slope;
    float box[4];
    float code[2][4];
    int condition;

    public :

    cohen();
    void set(int);
    bool andpoints();
    bool samepoints();
    bool checkzero(int);
    void clip();
    void clipping(int);
    void setpoint();
    void display();

 };

cohen::cohen()
 {
    condition = 0;

    cout<<"Enter the coordinates of the viewing window : "<<endl;

    cout<<"Enter the maximum y coordinate :";
    cin>>box[YMAX];

    cout<<"Enter the minimum y coordinate :";
    cin>>box[YMIN];

    cout<<"Enter the maximum x coordinate :";
    cin>>box[XMAX];

    cout<<"Enter the minimum x coordinate :";
    cin>>box[XMIN];

    cout<<"Enter the coordinates of the first point of line :";
    cin>>p[0][0]>>p[0][1];

    cout<<"Enter the coordinates of the second point of line :";
    cin>>p[1][0]>>p[1][1];

    slope = ( p[1][1] - p[0][1] )/( p[1][0] - p[0][0] );

    store[0][0] = p[0][0];
    store[0][1] = p[0][1];
    store[1][0] = p[1][0];
    store[1][1] = p[1][1];

    set(0);
    set(1);
    clip();

 }

void cohen::set(int j)
 {
    for(int i=0;i<4;i++)
     {
        switch(i)
         {
            case 0 : code[j][YMAX] = ( ( p[j][1]>box[YMAX] ) ? 1 : 0 );
                     cout<<code[j][YMAX];
                     break;
            case 1 : code[j][YMIN] = ( ( p[j][1]<box[YMIN] ) ? 1 : 0 );
                     cout<<code[j][YMIN];
                     break;
            case 2 : code[j][XMAX] = ( ( p[j][0]>box[XMAX] ) ? 1 : 0 );
                     cout<<code[j][XMAX];
                     break;
            case 3 : code[j][XMIN] = ( ( p[j][0]<box[XMIN] ) ? 1 : 0 );
                     cout<<code[j][XMIN]<<endl;
                     break;
         }
     }
 }

bool cohen::andpoints()
 {
    for(int i=0;i<4;i++)
     {
        if( (code[0][i]==1) && (code[1][i]==1) )
          {
            condition = 2;
            return true;
          }
     }

    return false;
 }

bool cohen::samepoints()
 {
    for(int i=0;i<2;i++)
        if( p[0][i] != p[1][i] )
            {
                condition = 2;
                return false;
            }
    return true;
 }

bool cohen::checkzero(int j)
 {
    for(int i=0;i<4;i++)
        if( code[j][i] == 1 )
            return false;

    return true;
 }

void cohen::clip()
 {
   while(true)
    {

        if(andpoints())
            break;

        if(samepoints())
            break;

        if ( checkzero(0) && checkzero(1) )
            {
                condition = 1;
                break;
            }

        if ( checkzero(0) )
             {
                clipping(1);
                continue;
             }
        if ( checkzero(1) )
            {
                clipping(0);
                continue;
            }

        clipping(0);
        clipping(1);
    }
 }

void cohen::clipping(int j)
 {
    int i = 0;
    bool flag = true;

    while( (i<4) && (flag) )
        {
            if( code[j][i] == 1 )
                 {
                    code[j][i] = 0;

                    switch(i)
                     {
                        case 0 :  p[j][0] = p[0][0] + ( box[YMAX] - p[0][1] )/slope;
                                  p[j][1] = box[YMAX];
                                  break;
                        case 1 :  p[j][0] = p[0][0] + ( box[YMIN] - p[0][1] )/slope;
                                  p[j][1] = box[YMIN];
                                  break;
                        case 2 :  p[j][1] = p[0][1] + ( box[XMAX] - p[0][0] )*slope;
                                  p[j][0] = box[XMAX];
                                  break;
                        case 3 :  p[j][1] = p[0][1] + ( box[XMIN] - p[0][0] )*slope;
                                  p[j][0] = box[XMIN];
                                  break;
                     }
                    flag = false;
                 }
             i++;
        }

    set(j);
 }

void cohen::setpoint()
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

void cohen::display()
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
    initialize();         // initializes the graphics mode
    plotaxis();           // plots the coordinate axis

    cohen c;              // all the neccessary inputs are taken in the constructor call, plus it also initiates the clipping algorithm
    c.display();          // the functions responsible for displaying the window,unclipped line and the clipped line

    return 0;
 }
