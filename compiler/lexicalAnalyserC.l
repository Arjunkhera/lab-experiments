
%{

#include<stdio.h>
int counter = 0;
int litcount = 0;

%}


%%

main	        printf("KW");
float	        printf("KW");
int	            printf("KW");
return	        printf("KW");
break	        printf("KW");
if	            printf("KW");
else	        printf("KW");
cin	            printf("KW");
cout	        printf("KW");
#include	    printf("INCLUDE ");
\<stdio\.h\>    printf("HEADER");


\"(\\.|[^"\\])*\"	printf("STR%d",litcount++);

[_a-zA-Z][a-zA-Z0-9_]*	printf("ID%d",counter++);

== 	printf("relop=");
\> 	printf("relop>");
\< 	printf("relop<");
= 	printf("equalop");

\+	printf("addop");
\-	printf("subop");
\*	printf("multop");
\/	printf("divop");


; 	printf(";");
, 	printf(",");
\<\< 	printf("<<");
\>\> 	printf(">>");
{ 	printf("{");
} 	printf("{");

%%


int yywrap(){
    return 1;
}

int main(){

    yylex();

    return 0;
}
