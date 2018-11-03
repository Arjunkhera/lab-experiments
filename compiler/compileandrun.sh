
commonname=example
filename="example$1"
yaccornot=$2

if [[ $yaccornot -eq "yes" ]];
then
    echo "Compiling the lex file"
    lex "${filename}.l"

    echo "Compiling the yacc file"
    yacc -d "${filename}.y"

    echo "Generating the executable"
    cc lex.yy.c y.tab.c -o "${filename}" 

else
    echo "Compiling the lex file"
    lex "${filename}.l"

    echo "Generating the executable"
    cc lex.yy.c -o "${filename}" -ll
fi


echo -e "Running the executable\n\n" 
./${filename}
