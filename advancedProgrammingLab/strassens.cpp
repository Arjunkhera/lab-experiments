#include<iostream>

using namespace std;

int** strassens(int **mat1,int n1,int **mat2,int n2,int ){

  int **


}

void display(int **arr,int n1,int n2){

  for(int i=0;i<n1;i++){
    for(int j=0;j<n2;j++)
      cout<<arr[i][j]<<" ";
    cout<<endl;
  }

}

void input(int **arr,int n){

  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      cin>>arr[i][j];

}

int main(){

  int n1,n2;
  cout<<"Enter the dimensions for first matrix :"<<endl;
  cin>>n1;

  int **mat1 = new int*[n1];
  for(int i = 0;i < n1;i++)
    mat1[i] = new int[n1];
  cout<<"Enter the contents for first matrix :"<<endl;
  input(mat1,n1);

  cout<<"Enter the dimensions for second matrix :"<<endl;
  cin>>n2;

  int **mat2 = new int*[n2];
  for(int i = 0;i < n2;i++)
    mat1[i] = new int[n2];
  cout<<"Enter the contents for second matrix :"<<endl;
  input(mat2,n2);

  int** result = strassens(mat1,n1,mat2,n2);
  display(result,n1,n2);
  cout<<endl;

  return 0;
}
