#include<iostream>
#include<list>
#include<vector>
#include<stack>
#include<queue>

using namespace std;

struct edgelist{
    list<int> id;
    list<int> weights;
};

class graph{

    public:
        int V;
        int E;
        struct edgelist* vertices;

        graph(int,int);
        void input();
        void display();
};

graph::graph(int V,int E){

    this->V = V;
    this->E = E;
    this->vertices = new struct edgelist[V];
}

void graph::input(){
    int src,dest,weight;
    int brk = 0;

    struct edgelist* head;

    while(brk < this->E){

        cin>>src>>dest>>weight;

        // assuming directed graph
        this->vertices[src].id.push_back(dest);
        this->vertices[src].weights.push_back(weight);

        brk++;
        cout<<src<<" "<<dest<<" "<<weight<<"\n";
    }
}

void graph::display(){
    cout<<" SRC "<<" DEST "<<" WEIGHT "<<endl;

    for(int i=0;i<this->V;i++){
        struct edgelist j = this->vertices[i];

        auto node = j.id.begin();
        auto val = j.weights.begin();

        while(node != j.id.end()){
            cout<<i<<"  "<<*node<<"  "<<*val<<endl;
            node++;
            val++;
        }
    }

}

void bfs(graph *g,int src){

    vector<bool> visited(g->V,false);
    queue<int> buffer;

    buffer.push(src);
    while(!buffer.empty()){

        int cur = buffer.front();
        buffer.pop();

        if(visited[cur] == true)
            continue;

        visited[cur] = true;
        cout<<cur<<" ";

        auto node = g->vertices[cur].id.begin();
        while(node != g->vertices[cur].id.end()){
            if(visited[*node] != true)
                buffer.push(*node);

            node++;
        }
    }

    cout<<endl;
}

void dfs(graph *g,int src){

    vector<bool> visited(g->V,false);
    stack<int> buffer;

    buffer.push(src);
    while(!buffer.empty()){

        int cur = buffer.top();
        buffer.pop();

        if(visited[cur] == true)
            continue;

        visited[cur] = true;
        cout<<cur<<" ";

        auto node = g->vertices[cur].id.begin();
        while(node != g->vertices[cur].id.end()){
            if(visited[*node] != true)
                buffer.push(*node);

            node++;
        }
    }

    cout<<endl;
}

int main(){

    int V,E;
    cin>>V>>E;

    graph g(V,E);
    g.input();
    g.display();

    cout<<"\nRunning BFS\n";
    bfs(&g,0);

    cout<<"\nRunning DFS\n";
    dfs(&g,0);

    return 0;
}
