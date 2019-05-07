#include<iostream>

using namespace std;

double encode(string str,double **arr,string inp){

    double low_val = 0.0;
    double high_val = 1.0;
    double diff = 1.0;
    double range;
    size_t j;

    for(int i=0;i<inp.length();i++){
        j = str.find(inp[i]);

        high_val = low_val + arr[j][1]*diff;
        low_val = low_val + arr[j][0]*diff;
        diff = high_val - low_val;
    }
    return low_val;
}

void decode(string str,double **arr,double encoded){
    double epsilon = 0.001;
    while(true){
        int j = 0;
        for(;j<str.length();j++)
            if(encoded >= arr[j][0] && encoded <= arr[j][1] )
                break;

        cout<<str[j]<<"";
        if(encoded - arr[j][0] < epsilon)
          break;

        encoded = (encoded - arr[j][0])/(arr[j][1] - arr[j][0]);
    }
}

int main(){

    int n;
    cout<<"Enter the number of characters :";
    cin>>n;

    double **arr = new double*[n];
    for(int i=0;i<n;i++)
        arr[i] = new double[2];

    string str;
    char ch;

    for(int i=0;i<n;i++){
        cin>>ch;
        str.push_back(ch);
        cin>>arr[i][0];
        cin>>arr[i][1];
    }

    string inp;
    cout<<"Enter the string to encode";
    cin>>inp;

    cout<<endl;
    cout<<"The table entered is "<<endl;
    for(int i=0;i<n;i++){
        cout<<str[i]<<" ";
        cout<<arr[i][0]<<" ";
        cout<<arr[i][1];
        cout<<endl;
    }

    double encoded_string = encode(str,arr,inp);
    cout<<"The encoded string is: "<<encoded_string<<endl;
    cout<<"The decoded string is: ";
    decode(str,arr,encoded_string);
    cout<<endl;
}
