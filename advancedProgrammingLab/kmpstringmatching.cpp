#include<iostream>
#include<vector>

using namespace std;

void preprocess(string substr,int *prefix){

    int j = 0,i = 1;
    prefix[0] = 0;

    while(i < substr.length()){

        // character match
        if(substr[i] == substr[j]){
            prefix[i] = j+1;
            i++;
            j++;
            continue;
        }

        // character mismatch
        if(j == 0){
            prefix[i] = 0;
            i++;
            continue;
        }

        j = prefix[j-1];
    }

}

vector<int> kmp(string str,string substr,int *prefix){

    vector<int> answer;
    int j = 0,i = 0;

    while(i < str.length()){

        // the characters match
        if(str[i] == substr[j]){
            i++;
            j++;

            // the whole substring has been matched
            if(j == substr.length()){
                answer.push_back(i-substr.length());
                j = 0;
            }

            continue;
        }

        // character mismatch
        if(j == 0){
            i++;
            continue;
        }

        j = prefix[j-1];
    }

    return answer;
}

int main(){

    // take input
    string str,substr;
    cin>>str>>substr;

    // preprocess the substring
    int *prefix = new int[substr.length()];
    preprocess(substr,prefix);

    // apply kmp
    vector<int> index = kmp(str,substr,prefix);

    // print the matching indexes
    cout<<"The index are :"<<endl;
    for(auto i : index)
        cout<<i<<" ";
    cout<<endl;

    return 0;
}
