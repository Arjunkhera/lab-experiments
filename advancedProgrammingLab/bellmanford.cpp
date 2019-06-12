#include<iostream>
#include<climits>
#include<vector>

using namespace std;

struct edge{
    int source;
    int destination;
    int weight;
};

class graph{
    public:
        int V;
        int E;
        struct edge *edgelist;

        graph(int,int);
        void input();
        void display();
};

graph::graph(int V,int E){
    this->V = V;
    this->E = E;

    this->edgelist = new struct edge[this->E];
}

void graph::input(){
    for(int i=0;i<this->E;i++)
        cin>>edgelist[i].source>>edgelist[i].destination>>edgelist[i].weight;
}

void recursive(vector<int> parents,int cur,int src){

    if(cur == src){
        cout<<cur;
        return;
    }

    cout<<cur<<"<--";
    recursive(parents,parents[cur],src);
}

void display(vector<int> distances,vector<int> parents,int src){
    cout<<"vertex is: "<<" distance is :"<<" path is: "<<endl;
    for(int i=0;i<distances.size();i++){
        cout<<i<<"           "<<distances[i]<<"              ";
        recursive(parents,i,src);
        cout<<endl;

    }
}

void bellmanford(graph *g,int src){

    vector<int> distances(g->V);
    vector<int> parents(g->V);

    for(int i=0;i<g->V;i++)
        distances[i] = INT_MAX;
    distances[src] = 0;

    for(int i=1;i<g->V;i++){
        for(int j=0;j<g->E;j++){
            int tempsource = g->edgelist[j].source;
            int tempdestination = g->edgelist[j].destination;

            if(distances[tempsource] != INT_MAX && distances[tempsource] + g->edgelist[j].weight < distances[tempdestination]){
                distances[tempdestination] = distances[tempsource] + g->edgelist[j].weight;
                parents[tempdestination] = tempsource;
            }
        }
    }

    for(int j=0;j<g->E;j++){
        int tempsource = g->edgelist[j].source;
        int tempdestination = g->edgelist[j].destination;

        if(distances[tempsource] != INT_MAX && distances[tempsource] + g->edgelist[j].weight < distances[tempdestination]){
            cout<<"There exists a negative edge cycle";
            return;
        }
    }

    display(distances,parents,src);
}

int main(){

    int V,E;
    // cout<<"Enter the number of vertices in the graph: ";
    cin>>V;
    // cout<<"Enter the number of Edges in the graph: ";
    cin>>E;

    int src;
    // cout<<"Enter the source node";
    cin>>src;

    graph g(V,E);
    g.input();

    bellmanford(&g,src);

    return 0;
}
