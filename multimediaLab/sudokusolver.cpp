#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <random>
#include <chrono>
#include <thread>

using namespace std;

// size of the sudoku board
#define SIZE 9
// default values for the board
#define UNASSIGNED 0

// function declarations
bool SolveSudoku(vector<vector<int> >&);
bool FindUnAssignedPos(vector<vector<int> > &,int&,int&);
bool isSafe(vector<vector<int> >&,int,int,int);
void createGrid(vector<vector<int> >&);
void display(vector<vector<int> >&);
bool isSolvable(vector<vector<int> >);

int menu(){

  int choice;
  cout<<endl;
  cout<<"1. Enter Values"<<endl;
  cout<<"2. Reset"<<endl;
  cout<<"3. Submit"<<endl;
  cout<<"*. Exit"<<endl;
  cout<<"Choose: ";

  cin>>choice;
  return choice;

}

int main(){

    vector<vector<int>> grid(SIZE,vector<int>(SIZE,UNASSIGNED)),intial_state;

    createGrid(grid);

    intial_state = grid;
    int key,row,col,val;

    while( true ){

      std::system("clear");
      display(grid);
      key = menu();

      if(key == 1){

        cout<<"Enter row, column and values (1-indexed): ";
        cin>>row>>col>>val;

        if(val > 9 || val < 1)
          cout<<"Invalid number entry"<<endl;
        else if(grid[row-1][col-1] != UNASSIGNED)
          cout<<"Cant change existing number"<<endl;
        else if(isSafe(grid,row-1,col-1,val))
          grid[row-1][col-1] = val;
        else cout<<"Not A Valid Move !"<<endl;

      }
      else if(key == 2){
        grid = intial_state;
        cout<<"Resetting |||| "<<endl;
      }
      else if(key == 3){

          key = 1;
          for(row = 0;row < SIZE;row++){
            for(col = 0;col < SIZE;col++)
              if(grid[row][col] == UNASSIGNED){
                key = 0;
                cout<<"Not so easy boy, Get back to it!!!"<<endl;
                break;
              }

            if(!key)
              break;
          }

          if(key){
            cout<<"Congratulations!!! You have solved the puzzle!"<<endl;
            exit(0);
          }

      }
      else{
        cout<<"Exiting...."<<endl;
        exit(0);
      }

      std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }
}

// construct a random problem grid for sudoku
void createGrid(vector<vector<int>> &grid){

  // fill the grid with numbers
  SolveSudoku(grid);

  vector<int> array,temp;
  for(int i = 0;i < (SIZE*SIZE);i++)
        temp.push_back(i);

  int n,t;
  n = temp.size();

  // construct a vector of random indices
  srand(time(NULL));
  for(int i = 0;i < n;i++){

      t = rand()%temp.size();
      array.push_back(temp[t]);
      temp.erase(temp.begin()+t);

  }

  int i = 0;
  // remove as many elements as possible, however ensure sudoku is solvable
  while(i < n){

      t = grid[array[i]/SIZE][array[i]%SIZE];
      grid[array[i]/SIZE][array[i]%SIZE] = UNASSIGNED;

      if(!isSolvable(grid))
        grid[array[i]/SIZE][array[i]%SIZE] = t;

      i++;
  }

}

bool isSolvable(vector<vector<int>> grid){

  int count,val;
  int count_un = 0;
  bool changed = false;

  for(int i = 0;i < SIZE;i++){
    for(int j = 0;j < SIZE;j++){

      if(grid[i][j] != UNASSIGNED){
        count_un++;
        continue;
      }

      count = 0;
      val = -1;

      for(int num = 1;num <= SIZE;num++)
        if(isSafe(grid,i,j,num)){
          count++;
          if(count > 1)
            break;

          val = num;
        }

      if(count == 1){
        grid[i][j] = val;
        changed = true;
      }

    }
  }

  if(count_un == SIZE*SIZE)
    return true;

  if(!changed)
    return false;

  return isSolvable(grid);
}

// construct the sudoku grid using backtracking
bool SolveSudoku(vector<vector<int>> &grid){

  int row, col,t;

  // check whether the sudoku grid been filled completely
  if( !FindUnAssignedPos(grid,row,col) )
    return true;

  vector<int> array,temp;
  // construct a vector of ordered elements till 9
  for(int i = 1;i <= SIZE;i++)
    temp.push_back(i);

  // construct a vector of random numbers from 1 to 9
  srand(time(NULL));
  for(int i = 0;i < SIZE;i++){

    t = rand()%temp.size();
    array.push_back(temp[t]);
    temp.erase(temp.begin()+t);

  }

  for(int i = 0;i < SIZE;i++){

    if(isSafe(grid,row,col,array[i])){

      grid[row][col] = array[i];
      if( SolveSudoku(grid) )
        return true;

      // failed to find a solution, backtrack
      grid[row][col]=UNASSIGNED;
    }
  }

  // no valid positions, backtrack
  return false;
}

// find the position of any unassigned grids
bool FindUnAssignedPos(vector<vector<int>> &grid,int &row, int &col){

  for(row = 0;row < SIZE;row++)
    for(col = 0;col < SIZE;col++)
      if(grid[row][col] == UNASSIGNED)
        return true;

  return false;
}

// check whether the grid is legal
bool isSafe(vector<vector<int>> &grid,int row,int col,int val){

  // current grid is empty
  if(grid[row][col] != UNASSIGNED)
    return false;

  // no row or column violations
  for(int i = 0;i < SIZE;i++)
    if(grid[row][i] == val || grid[i][col] == val)
      return false;

  // check for box violations
  int box = sqrt(SIZE);
  int box_row = (row/box)*box;
  int box_col = (col/box)*box;

  for(int i = 0;i < box;i++)
    for(int j = 0;j < box;j++)
      if(grid[i + box_row][j+ box_col] == val)
        return false;

  // no violation found
  return true;
}

// display the grid
void display(vector<vector<int>> &grid){

  cout<<endl;

  int box = sqrt(SIZE);
  for(int i = 0;i < SIZE;i++){
    for(int j = 0;j < SIZE;j++){

      if(grid[i][j] == UNASSIGNED)
        cout<<"_ ";
      else
        cout<<grid[i][j]<<" ";

      if((j+1)%box == 0)
        cout<<" ";
    }

    cout<<endl;
    if((i+1)%box == 0)
      cout<<endl;
  }

}
