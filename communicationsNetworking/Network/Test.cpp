#include <iostream>
#include <string>
#include <bitset>
#define M 8
using namespace std;

bitset<M> operator+(bitset<M>& a,bitset<M>& b){
bitset<M> c(0);
bool carry=false;
for(int i=0;i<M;i++){
	c[i]=int(bool(a[i])^bool(b[i])^carry);
	carry=bool(a[i])&&bool(b[i]) || bool(b[i])&&carry || carry&&bool(a[i]);
	cout<<a[i]<<" + "<<b[i]<<" = "<<carry<<c[i]<<endl;
}
return c;
}
int main(){

	bitset<M> a(3);
	bitset<M> b(1);
	cout<<a<<endl<<b<<endl;
	cout<<a+b<<endl;
	return 0;
}
