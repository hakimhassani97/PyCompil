%{  
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>	
	#include "syntaxique.tab.h"
	extern int lignes;
%}
num [0-9]
idf [A-Z_][a-zA-Z0-9_]*
%%

int {return(mcInt);}
if {return(mcIf);}
elif {return(mcElif);}
else {return(mcElse);}
{num}+ {yylval.str=strdup(yytext);return(cteInt);}
[ ] {return(espace);}
[\t] {return(tab);}
[\n] {lignes++;return(saut);}
\( {return(parOuv);}
\) {return(parFerm);}
= {return(egale);}
[\!] {return(not);}
\> {return(sup);}
\< {return(inf);}
{idf} {yylval.str=strdup(yytext);return(idf);}
#[^\n]* {lignes++;return(commentaire);}
: {return(dp);}
, {return(vg);}
\+ {return(pl);}
- {return(mi);}
\* {return(mul);}
\/ {return(dv);}
. printf("erreur lexicale : \"%s\" dans la ligne %d\n",yytext,lignes);
