%{

#include<stdio.h>
char pls[100];
char op[] = "$";
len=0;

%}

%token NUMBER
%left '+' '-'
%left '*' '/'

%%

st: exp {printf("\n");}
    ;

exp:  exp '+' exp {printf("+"); strcat(op,"+"); }
    | exp '-' exp {printf("-"); strcat(op,"-"); }
    | exp '*' exp {printf("*"); strcat(op,"*"); }
    | exp '/' exp {printf("/"); }
    | '(' exp ')'
    | NUMBER {printf("%d",$1); strcat(op,$1); }
    ;

%%

int main()
{
    yyparse();

    // printf("%s",op);
    printf("\n");

    return 0;
}

int yywrap()
{
    return 1;
}

void yyerror(char *s)
{
    printf("error:%s",s);
}
