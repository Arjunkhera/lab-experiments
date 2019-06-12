#include<iostream>
#include<vector>
#include<climits>

using namespace std;

void recursive(vector<long int> parents,long int cur,long int src){

    if(cur == src){
        cout<<cur;
        return;
    }

    cout<<cur<<"<--";
    recursive(parents,parents[cur],src);
}

void display(vector<long int> distances,vector<long int> parents,long int src){
    cout<<"vertex is: "<<" distance is :"<<" path is: "<<endl;
    for(long int i=0;i<distances.size();i++){
        cout<<i<<"           "<<distances[i]<<"             ";
        recursive(parents,i,src);
        cout<<endl;
    }
}

void djisktra(long int n,long int src,long int **arr){

    vector<bool> visited(n,false);
    vector<long int> parents(n,0);
    vector<long int> distances(n,0);

    for(long int i=0;i<n;i++)
        if(arr[src][i] != INT_MAX){
            distances[i] = arr[src][i];
            parents[i] = src;
        }
        else distances[i] = INT_MAX;

    long int min_distnode = 0;
    long int index = -1;
    visited[src] = true;

    for(long int k=1;k<n;k++){

        // find the minimum distance node
        min_distnode = INT_MAX;
        for(long int j=0;j<n;j++){
            if(visited[j] == true)
                continue;

            if(min_distnode > distances[j]){
                min_distnode = distances[j];
                index = j;
            }
        }

        visited[index] = true;
        for(long int h=0;h<n;h++)
            if(distances[index] + arr[index][h] < distances[h] && h != src){
                distances[h] = distances[index] + arr[index][h];
                parents[h] = index;
            }
    }

    distances[src] = 0;
    display(distances,parents,src);

}

void input(long int V,long int E,long int **distance_matrix){

    long int src,dest,weight;

    for(long int i=0;i<E;i++){
        cin>>src>>dest>>weight;
        distance_matrix[src][dest] = weight;
        distance_matrix[dest][src] = weight;
    }

    for(long int i=0;i<V;i++)
        for(long int j=0;j<V;j++)
            if(distance_matrix[i][j] == -1)
                distance_matrix[i][j] = INT_MAX;

}

int main(){

    long int V,E,src;
    cin>>V>>E>>src;

    // input distance_matrix
    long int **distance_matrix = new long int*[V];
    for(long int i=0;i<V;i++)
        distance_matrix[i] = new long int[V];

    // set all distances to -1
    for(long int i=0;i<V;i++)
        for(long int j=0;j<V;j++)
            distance_matrix[i][j] = -1;

    // enter the distances of the directed graph
    input(V,E,distance_matrix);

    // solution function
    djisktra(V,src,distance_matrix);

    cout<<endl;
    return 0;
}
