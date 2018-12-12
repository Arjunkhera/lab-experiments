#include<fstream>
#include<iostream>
#include<stdbool.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

using namespace std;

// Returns 'true' if the character is a DELIMITER.
bool isDelimiter(char ch){
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}')
        return true;
    return false;
}

// Returns 'true' if the character is an OPERATOR.
bool isOperator(char ch){
    if (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == '>' || ch == '<' ||
        ch == '=')
        return true;
    return false;
}

// Returns 'true' if the string is a VALID IDENTIFIER.
bool validIdentifier(char* str){
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||
        str[0] == '9' || isDelimiter(str[0]) == true)
        return (false);
    return (true);
}

// Returns 'true' if the string is a KEYWORD.
bool isKeyword(char* str){
    if (!strcmp(str, "if") || !strcmp(str, "else") ||
        !strcmp(str, "while") || !strcmp(str, "do") ||
        !strcmp(str, "break") ||
         !strcmp(str, "continue") || !strcmp(str, "int")
        || !strcmp(str, "double") || !strcmp(str, "float")
        || !strcmp(str, "return") || !strcmp(str, "char")
        || !strcmp(str, "case") || !strcmp(str, "char")
        || !strcmp(str, "sizeof") || !strcmp(str, "long")
        || !strcmp(str, "short") || !strcmp(str, "typedef")
        || !strcmp(str, "switch") || !strcmp(str, "unsigned")
        || !strcmp(str, "void") || !strcmp(str, "static")
        || !strcmp(str, "struct") || !strcmp(str, "goto"))
        return (true);
    return (false);
}

// Returns 'true' if the string is an INTEGER.
bool isInteger(char* str){
    int i, len = strlen(str);

    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' || (str[i] == '-' && i > 0))
            return (false);
    }
    return (true);
}

// Returns 'true' if the string is a REAL NUMBER.
bool isRealNumber(char* str){
    int i, len = strlen(str);
    bool hasDecimal = false;

    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' && str[i] != '.' ||
            (str[i] == '-' && i > 0))
            return (false);
        if (str[i] == '.')
            hasDecimal = true;
    }
    return (hasDecimal);
}

// DRIVER FUNCTION
int main(){

    char c,temp[100];
    for(int i = 0;i < 100;i++) temp[i]='\0';

    int index = 0;
    ifstream fin("input.cpp", ios::app);

    while(fin.get(c)){

        temp[index] = (char)c;

        if(c == '\n' || c == ' '){

            char newTemp[100];
            for(int i=0;i<100;i++) newTemp[i]='\0';

            int j = 0;
            for(int i=0;i<strlen(temp);i++) if(temp[i] != ' ' && temp[i] != '\n') newTemp[j++]=temp[i];

            newTemp[j]='\0';
            if(strlen(newTemp) == 0) {
            }
            else if(isOperator(newTemp[0])) {
                cout<<newTemp[0]<<" "<<"Operator\n";
            }
            else if(isDelimiter(newTemp[0])) {
                cout<<newTemp[0]<<" "<<"Delimiter\n";
            }
            else if(isRealNumber(newTemp)) {
                cout<<newTemp<<" "<<"Real Number\n";
            }
            else if(isInteger(newTemp)) {
                cout<<newTemp<<" "<<"Integer\n"; }
            else if(isKeyword(newTemp)) {
                cout<<newTemp<<" "<<"Keyword\n";
            }
            else if(validIdentifier(newTemp)) {
                cout<<newTemp<<" "<<"Valid Identifier\n";
            }
            else {
                cout<<newTemp<<" "<<"Invalid Identifier\n";
            }
            for(int i=0;i<100;i++) {
                temp[i]='\0';
            }
            index=0;
        }
        else if(isOperator(c) || isDelimiter(c)){
            char newTemp[100];
            for(int i=0;i<100;i++) {
                newTemp[i]='\0';
            }
            int j=0;
            for(int i=0;i<strlen(temp)-1;i++) {
                if(temp[i]!=' ') {
                    newTemp[j++]=temp[i];
                }
            }
            newTemp[j]='\0';
            char ch = temp[strlen(temp)-1];
            if(strlen(newTemp) == 0) {
            }
            else if(isOperator(newTemp[0])) {
                cout<<newTemp[0]<<" "<<"Operator\n";
            }
            else if(isDelimiter(newTemp[0])) {
                cout<<newTemp[0]<<" "<<"Delimiter\n";
            }
            else if(isRealNumber(newTemp)) {
                cout<<newTemp<<" "<<"Real Number\n";
            }
            else if(isInteger(newTemp)) {
                cout<<newTemp<<" "<<"Integer\n";
            }
            else if(isKeyword(newTemp)) {
                cout<<newTemp<<" "<<"Keyword\n";
            }
            else if(validIdentifier(newTemp)) {
                cout<<newTemp<<" "<<"Valid Identifier\n";
            }
            else {
                cout<<newTemp<<" "<<"Invalid Identifier\n";            }
            if(isOperator(ch)) {
                cout<<ch<<" "<<"Operator\n";            }
            else {
                cout<<ch<<" "<<"Delimiter\n";            }
            for(int i=0;i<100;i++) {
                temp[i]='\0';            }
            index=0;
        } else {
            index++;
        }
    }

    return 0;
}
