bison -d syntaxique.y
flex lexical.l
gcc -o pyCompil syntaxique.tab.c lex.yy.c -lfl