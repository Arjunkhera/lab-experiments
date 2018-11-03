%{

#include<stdio.h>

%}

%token NUMBER
%left '+' '-'
%left '*' '/'

%%
st: exp {printf("\n");}
    ;

exp: exp '+' ter  {printf("+");}
    | exp '-' ter {printf("+");}
    | ter;
ter: ter '*' f {printf("+");}
    | ter '\' f {printf("+");}
    | f;
f: '-' f | '(' exp ')' | NUMBER {printf("%d",$1);}

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
