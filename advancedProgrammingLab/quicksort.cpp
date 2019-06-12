#include<iostream>

using namespace std;

int pivot(int arr[],int start,int end){

    int temp;
    int j = start;
    int i = start-1;
    int pivotelement = arr[end];

    while(j < end){

        if(arr[j] <= pivotelement){
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
        j++;
    }

    i++;
    temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;

    return i;
}

void quicksort(int arr[],int start,int end){

    if(start >= end)
        return;

    int pivotindex = pivot(arr,start,end);
    quicksort(arr,start,pivotindex-1);
    quicksort(arr,pivotindex+1,end);

}

void display(int arr[],int n){
    for(int i=0;i<n;i++)
        cout<<arr[i]<<" ";

    cout<<endl;
}

int main(){

    int n;
    cin>>n;

    int *arr = new int[n];
    for(int i=0;i<n;i++)
        cin>>arr[i];

    quicksort(arr,0,n-1);
    display(arr,n);

    return 0;
}
