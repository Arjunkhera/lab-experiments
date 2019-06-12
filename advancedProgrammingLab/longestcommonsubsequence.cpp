#include<iostream>
#include<stack>
#include<string>

using namespace std;

int main(){

    string stra,strb;
    cin>>stra;
    cin>>strb;

    int lengtha = stra.length();
    int lengthb = strb.length();

    int** dp = new int*[lengthb+1];
    for(int i=0;i<=lengthb;i++)
        dp[i] = new int[lengtha+1];

    for(int i=0;i<=lengthb;i++)
        for(int j=0;j<=lengtha;j++)
            dp[i][j] = 0;

    for(int i=1;i<=lengthb;i++){
        for(int j=1;j<=lengtha;j++){
            if(stra[j-1] == strb[i-1])
                dp[i][j] = dp[i-1][j-1]+1;
            else dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
        }
    }

    cout<<"The length is "<<dp[lengthb][lengtha]<<endl;
    stack<char> answer;

    int i = lengthb;
    int j = lengtha;

    while( j>0 && i>0 ){
        if(stra[j-1] == strb[i-1]){
            answer.push(stra[j-1]);
            i--;
            j--;
            continue;
        }

        if(dp[i-1][j] > dp[i][j-1])
            i--;
        else j--;

    }

    while(!answer.empty()){
        cout<<answer.top();
        answer.pop();
    }

    cout<<endl;
    return 0;
}
