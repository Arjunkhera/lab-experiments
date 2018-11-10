%{

#include<stdio.h>

%}

%token NUMBER
%left '+' '-'
%left '*' '/'
%right NEGATIVE

%%

st: exp {printf("\n");}
    ;

exp:  exp '+' exp {printf("+");}
    | exp '-' exp {printf("-");}
    | exp '*' exp {printf("*");}
    | exp '/' exp {printf("/");}
    | '-' exp %prec NEGATIVE {printf("-");} 
    | '(' exp ')' 
    | NUMBER {printf("%d",$1);}
    ;

%%
    
int main()
{
    yyparse();
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
