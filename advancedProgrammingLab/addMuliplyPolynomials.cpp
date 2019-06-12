#include<iostream>

using namespace std;

struct polynomial{

    int power;
    int *arr;
    polynomial(int n):power(n),arr(new int[n]){}
    void input();
    void display();
    void set();

};

void polynomial::input(){

    int temp;
    for(int i = this->power;i >= 0;i--){
        cin>>temp;
        this->arr[i] = temp;
    }

}

void polynomial::display(){

    for(int i = this->power;i >= 1;i--)
        cout<<this->arr[i]<<"(x"<<i<<") + ";

    cout<<this->arr[0]<<"(x"<<0<<")";
    cout<<endl;
}

void polynomial::set(){

    for(int i = this->power;i >= 1;i--)
        this->arr[i] = 0;

}

struct polynomial add(struct polynomial pA,struct polynomial pB){

    int i,maxpower = max(pA.power,pB.power);
    struct polynomial result(maxpower);

    if(pA.power > pB.power){
        i = maxpower;
        for(; i > pB.power; i--)
            result.arr[i] = pA.arr[i];
        for(; i >= 0; i--)
            result.arr[i] = pA.arr[i] + pB.arr[i];
    }
    else{
        i = maxpower;
        for(; i > pA.power; i--)
            result.arr[i] = pB.arr[i];
        for(; i >= 0; i--)
            result.arr[i] = pA.arr[i] + pB.arr[i];
    }

    return result;
}

struct polynomial multiply(struct polynomial pA,struct polynomial pB){

    int i,maxpower = pA.power+pB.power;
    struct polynomial result(maxpower);
    result.set();

    for(int i = pA.power ; i >= 0 ; i--)
        for(int j = pB.power ; j >= 0 ; j--)
            result.arr[i+j] += pA.arr[i]*pB.arr[j];

    return result;
}

int main(){

    int n;
    cout<<"Enter the maximum power of the first polynomial :"<<endl;
    cin>>n;

    polynomial pA(n);
    // enter the constants for the polynomial
    pA.input();

    cout<<"Enter the maximum power of the second polynomial :"<<endl;
    cin>>n;

    polynomial pB(n);
    // enter the constants for the polynomial
    pB.input();

    // adding the two polynomials
    polynomial pAdd = add(pA,pB);
    cout<<"Adding the two gives :"<<endl;
    pAdd.display();

    cout<<endl;

    // adding the two polynomials
    polynomial pMult = multiply(pA,pB);
    cout<<"Multiplying the two gives :"<<endl;
    pMult.display();

    return 0;
}
