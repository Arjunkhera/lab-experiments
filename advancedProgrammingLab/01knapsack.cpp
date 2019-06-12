#include<iostream>

using namespace std;

void input(int *weights,int *values,int n){

    for(int i = 0; i<n ;i++)
        cin>>weights[i]>>values[i];

}

int recursive(int *weights,int *values,int n,int max_weight,int i){

    // base case
    if(i == n || max_weight == 0)
        return 0;

    // recursive call
    if(max_weight >= weights[i])
        return max(values[i] + recursive(weights,values,n,max_weight-weights[i],i+1),recursive(weights,values,n,max_weight,i+1));
    else return recursive(weights,values,n,max_weight,i+1);
}

int dynamicprogramming(int *weights,int *values,int n,int max){

    // initialize the dp array
    int **arr = new int*[n+1];
    for(int i = 0; i<=n ; i++)
        arr[i] = new int[max+1];

    for(int i = 0; i<=n; i++)
        for(int j = 0; j<=max; j++)
            arr[i][j] = 0;

    // find the answer using dp
    for(int i = 1; i<=n; i++)
        for(int j = 1; j<=max; j++)
            if((weights[i-1] <= j) && (arr[i-1][j - weights[i-1]] + values[i-1]) > arr[i-1][j])
                arr[i][j] = arr[i-1][j - weights[i-1]] + values[i-1];
            else arr[i][j] = arr[i-1][j];

    return arr[n][max];
}

int main(){

    int n,max_weight;
    cin>>n>>max_weight;

    int *weights = new int[n];
    int *values = new int[n];

    input(weights,values,n);

    int answer1 = recursive(weights,values,n,max_weight,0);
    int answer2 = dynamicprogramming(weights,values,n,max_weight);


    cout<<"Answer through recursive method : "<<answer1<<endl;
    cout<<"Answer through dp method : "<<answer2<<endl;


    return 0;
}
