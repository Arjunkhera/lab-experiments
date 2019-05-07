#include <iostream>
#include <iomanip>
using namespace std;

int main(){
  int V,E,source,i,e,u,v,w;
  cout<<"Enter the number of vertices and edges: ";
  cin>>V>>E;

  int setEdges[E][3];
  int distances[V];

  cout<<"Enter the set of edges: "<<endl;
  for(i=0;i<E;i++)
    cin>>setEdges[i][0]>>setEdges[i][1]>>setEdges[i][2];

  cout<<"Enter the source: ";
  cin>>source;

  for(i=0;i<V;i++)
    distances[i]=INT_MAX;
  distances[source]=0;

  for(i=0;i<V-1;i++){
    for(e=0;e<E;e++){
      u=setEdges[e][0];
      v=setEdges[e][1];
      w=setEdges[e][2];
      if(distances[u]!=INT_MAX && distances[v] > distances[u] + w){
        distances[v] = distances[u] + w;
     }
    }
  }

  for(e=0;e<E;e++){
    u=setEdges[e][0];
    v=setEdges[e][1];
    w=setEdges[e][2];

    if(distances[u]!=INT_MAX && distances[v] > distances[u] + w){
      cout<<"Negative Cycle exist in the graph. exiting...";
      exit(1);
    }

 }

  cout<<setw(20)<<"Destination"<<setw(10)<<"Distance"<<endl;
  for(i=0;i<V;i++){
    cout<<setw(20)<<i<<setw(10)<<distances[i]<<endl;
  }

  return 0;
  }
