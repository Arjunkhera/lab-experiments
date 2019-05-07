//Distance Vector Routing Algorithm

#include<iostream>
using namespace std;
struct node
{
    unsigned dist[20];
    unsigned from[20];
}rt[10];
int main()
{
    int costmat[20][20];    //cost matrix
    int nodes,i,j,k,count=0;

    //Taking number of nodes
    cout<<"\nEnter the number of nodes : ";
    cin>>nodes;

    //Taking cost matrix of the graph
    cout<<"\nEnter the cost matrix :\n";
    for(i=0;i<nodes;i++)
    {
        for(j=0;j<nodes;j++)
        {
            cin>>costmat[i][j];
            costmat[i][i]=0;
            rt[i].dist[j]=costmat[i][j];//initialise the distance equal to cost matrix
            rt[i].from[j]=j;
        }
    }



        do
        {
            count=0;

            //Bellman Ford Algorithm
            for(i=0;i<nodes;i++)
            for(j=0;j<nodes;j++)
            for(k=0;k<nodes;k++)
                if(rt[i].dist[j]>costmat[i][k]+rt[k].dist[j])
                {
                    //calculating minimum distance
                    rt[i].dist[j]=rt[i].dist[k]+rt[k].dist[j];
                    rt[i].from[j]=k;
                    count++;
                }
        }while(count!=0);

        //Printing router table
        for(i=0;i<nodes;i++)
        {
            cout<<"\n\n For router "<<i+1<<endl;
            for(j=0;j<nodes;j++)
                cout<<"\t\nnode "<< j+1 <<" via "<< rt[i].from[j]+1 <<" Distance "<<rt[i].dist[j];
        }
    cout<<endl<<endl;
}
