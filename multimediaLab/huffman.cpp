#include<iostream>
#include<vector>
#include<queue>
#include<map>

using namespace std;

struct node{
  string str;
  int weight;

  struct node* left;
  struct node* right;

  node(string s,int val):str(s),weight(val),left(nullptr),right(nullptr){}
};

struct node* huffman(int n){

  auto cmp = [](struct node* a,struct node *b){return a->weight > b->weight;};
  priority_queue<struct node*,vector<struct node*>,decltype(cmp)> heap(cmp);

  struct node* temp;
  string s;
  int val;

  for(int i=0;i<n;i++){
    cin>>s;
    cin>>val;

    temp = new struct node(s,val);
    heap.push(temp);
  }

  struct node* makeshift;

  while(true){
    temp = heap.top();
    heap.pop();
    if(heap.empty())
      break;

    makeshift = heap.top();
    heap.pop();
    struct node* join = new struct node(temp->str+makeshift->str,temp->weight+makeshift->weight);

    if(temp->weight > makeshift->weight){
      join->left = temp;
      join->right = makeshift;
    }
    else {
      join->left = makeshift;
      join->right = temp;
    }

    heap.push(join);
  }

  return temp;
}

void encode(struct node* head,map<string,string> &codes,string codeword){

  if(head->left == nullptr && head->right == nullptr){
    codes[head->str] = codeword;
    return;
  }

  encode(head->left,codes,codeword+"0");
  encode(head->right,codes,codeword+"1");
}

void display(map<string,string> codes){

  cout<<"letter "<<" codeword "<<endl;
  for(auto i=codes.begin();i!=codes.end();i++){
    cout<<"  "<<i->first<<"        "<<i->second<<endl;
  }

}

int main(){

  int n;
  cin>>n;

  struct node* head = huffman(n);

  map<string,string> codes;
  encode(head,codes,"");

  display(codes);

  return 0;
}
