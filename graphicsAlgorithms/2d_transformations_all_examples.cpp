// program 6
// for rotation of a point about a origin

int main()
 {

    initialize();

    point p1;

    double angle;
    cout<<"enter the angle by which you want to rotate :";
    cin>>angle;
    cout<<endl;

    angle = angle*(pi/180);

    p1.plot(true,14);

    p1.pbegin();
    p1.rotate(-angle);
    p1.pend();

    p1.plot(false,14);

    getch();
    closegraph();

    return 0;
 }

-----------------------------------------------------------

// program 7
// for rotation about the origin of a triangle

int main()
 {

    initialize();

    point p[3];

    int angle;
    cout<<"enter the angle by which you want to roatate: ";
    cin>>angle;
    cout<<endl;

    for(int i=0;i<3;i++)
        p[i].plot_side(p[(i+1)%3],2,true);

    for(int i=0;i<3;i++)
    {
      p[i].pbegin();
      p[i].rotate(angle);
      p[i].pend();
    }

    for(int i=0;i<3;i++)
        p[i].plot_side(p[(i+1)%3],4,false);

    getch();
    closegraph();

    return 0;
 }

-----------------------------------------------------------

// program 8
// for scaling , example a triangle

int main()
 {

    initialize();

    point p[3];

    int s;
    cout<<"enter the scaling factor: ";
    cin>>s;
    cout<<endl;

    for(int i=0;i<3;i++)
        p[i].plot_side(p[(i+1)%3],2,true);

    for(int i=0;i<3;i++)
    {
      p[i].pbegin();
      p[i].scale(s);
      p[i].pend();
    }

    for(int i=0;i<3;i++)
        p[i].plot_side(p[(i+1)%3],4,false);

    getch();
    closegraph();

    return 0;
 }
 
-----------------------------------------------------------

// program 9
// for translation, example, of a triangle

int main()
 {

    initialize();

    point p[3];

    int tx,ty;
    cout<<"enter the translation coordinates : ";
    cin>>tx>>ty;
    cout<<endl;

    for(int i=0;i<3;i++)
        p[i].plot_side(p[(i+1)%3],2,true);

    for(int i=0;i<3;i++)
    {
      p[i].pbegin();
      p[i].translate(tx,ty);
      p[i].pend();
    }

    for(int i=0;i<3;i++)
        p[i].plot_side(p[(i+1)%3],4,false);

    getch();
    closegraph();

    return 0;
 }

-----------------------------------------------------------

// program 10
// for rotation about a line

int main()
 {

    initialize();

    point p[3];

    int m,b;
    cout<<"enter the slope of line : ";
    cin>>m;
    cout<<"enter the constant  : ";
    cin>>b;
    cout<<endl;

    for(int i=0;i<3;i++)
        p[i].plot_side(p[(i+1)%3],2,true);

    for(int i=0;i<3;i++)
    {
      p[i].pbegin();
      p[i].reflect(-m,b);
      p[i].pend();
    }

    for(int i=0;i<3;i++)
        p[i].plot_side(p[(i+1)%3],4,false);

    getch();
    closegraph();

    return 0;
 }

