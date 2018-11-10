
all: token parse compile run

token: 
	lex "${filename}.l"

parse:
	yacc -d "${filename}.y"

compile:
	cc lex.yy.c y.tab.c -o "${filename}"

run: ${filename}
	./${filename}

clean:
	rm lex.yy.c y.tab.c y.tab.h ${filename}

tester: 
	echo "${filename}.l"

