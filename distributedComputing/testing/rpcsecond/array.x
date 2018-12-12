struct arrays{
  int row_first;
  int col_first;
  int first[30];

  int row_sec;
  int col_sec;
  int second[30];

};

program ADD_PROG{

  version ADD_VERS{
    int add(arrays)=1;
  }=1;

}=0x23451122;
