#include <iostream>
#include <iomanip>
using namespace std;



int main(){
  int V,E,i,j,source,u,v,w,min;
  cout<<"Enter the number of vertices: ";
  cin>>V;

  int adj[V][V];
  int dist[V];
  bool sptSet[V];

  cout<<"Enter the adjacency matrix (0 if no edge is present): "<<endl;
  for(i=0;i<V;i++)
    for(j=0;j<V;j++)
      cin>>adj[i][j];
  cout<<"Enter the source vertex: ";
  cin>>source;

  for(i=0;i<V;i++)
    dist[i]=INT_MAX,sptSet[i]=false;
  dist[source]=0;

  for(i=0;i<V-1;i++){

    min=INT_MAX;
    for(j=0;j<V;j++)
      if(dist[j]<=min && !sptSet[j])
        min=dist[j],u=j;

    sptSet[u]=true;

    for(v=0;v<V;v++){
      if(!sptSet[v] && dist[u]!=INT_MAX && adj[u][v] && dist[u] + adj[u][v] < dist[v])
        dist[v]=adj[u][v]+ dist[u];
    }
  }

  cout<<setw(20)<<"Destination"<<setw(10)<<"Distance"<<endl;
  for(i=0;i<V;i++){
    cout<<setw(20)<<i<<setw(10)<<dist[i]<<endl;
  }


}
