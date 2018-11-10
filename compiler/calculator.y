%{

#include<stdio.h>

%}

%token NUMBER
%left '+' '-'
%left '*' '/'

%%
st: exp {printf("sum::%d",$$);}
    ;
exp: exp '+' exp {$$ = $1 + $3;}
    |exp '-' exp {$$ = $1 - $3;}
    |exp '*' exp {$$ = $1 * $3;}
    |exp '/' exp {$$ = $1 / $3;}
    |'('exp')' {$$ = $2;}
    |NUMBER {$$ = $1;}
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
