%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "pile.h"
  #include "quadreples.h"
  #include "codeObjet.h"
  #include "optimisation.h"
  int yylex();  
  void yyerror(char*msg);
  int count=0; 
  char temp1[100];
  char temp2[100];
  char op[100];
  int cond1=0;
  int cond2=0;
  int nbEspace=0;
  int nbElse= 0;
  int init=0;
  int lignes=1;
%}
%union {
char *str;
int ent;
}

%token mcIf espace saut dp egale <str>idf parOuv parFerm mcInt <str>cteInt vg pl
%token mi not sup inf mcElse mcElif dv mul commentaire tab

%start debut
%%
debut : espacesDebut debut |  { ajouterQdr("" ,"", "" , ""); 
                                                   lieuElif(-10, qc-1);
                                                    sauvQdr(-10,qc-1);afficher_qdr();propagationCopie(quad,qc);afficher_qdr();codeObjet(quad);}

espacesDebut : espacess instruction saut { if(nbElse==1){
                                          sauvQdr(count,qc); nbElse=0;}                                         
                                         else{
                                          lieuElif (count, qc-1);
                                          sauvQdr(count,qc-1);}
                                         if(nbEspace==1){
                                          nbEspace=0;
                                          ajoutSauv(count, qc-1);}
                                          count=0;}sauts
;
instruction :  affectation {garderEspace( "inst" ,count,0);  } | condIfElif   | commentaire  | condElse | decl {garderEspace( "inst" ,count,0);}

condIfElif : mcCond cond  espaces      

cond : espaces parOuv espaces expLo parFerm  espaces  dp  
   
condElse : mcElse {garderEspace( "else" ,count,0);  ajouterQdr("BR" ,"", "" , "");nbElse=1; nbEspace=1;}  espaces dp espaces 

expLo    : expLo2  exp { cond2=priorite(1); 
                       strcpy(op,operateur(op));  
                       nbEspace=1;                     
                       if(cond2==1){
                       strcpy(temp2,quad[qc-1].op1); 
                       qc--;}else{
                        strcpy(temp2,quad[qc-1].res);

                       }
                       cond1=0;
                       cond2=0;                         
                       ajouterQdr(op,temp1 ,temp2 ,""); }
  
expLo2 : expLo1 opComparaison espaces 

expLo1  : exp { cond1=priorite(1);if(cond1==1){strcpy(temp1,quad[qc-1].op1);
                                                                            qc--;}else{
                                                                            strcpy(temp1,quad[qc-1].res);}  }  
       
affectation   : idf   espaces egale espaces exp  {priorite(0); ajour_quad(qc-1, 3, $1);}  
 
exp:val espaces op espaces exp|val espaces|expEntrePar2  parFerm  { push(")");} | expEntrePar  op espaces exp

expEntrePar :  expEntrePar2 parFerm  { push(")");}

expEntrePar2 : expEntrePar1 exp

expEntrePar1 : parOuv   { push("(");}

mcCond : mcIf {garderEspace( "if" ,count,0); }   | mcElif {garderEspace( "elif" ,count,0);ajouterQdr("BR" ,"", "" , "elif");
                                                                            ajoutSauv(count, qc-1);                 
                                                                                               }
 
decl : TYPE declaration 

declaration : indentation espaces idf espaces initialisation {if(init==1){priorite(0); ajour_quad(qc-1, 3, $3); init=0;}}  
                                                      aprDeclaration 
 
aprDeclaration : vg espaces idf espaces initialisation {
                                                       if(init==1){ priorite(0); ajour_quad(qc-1, 3, $3);
                                                            init=0;
                                                         }
                                                       }  
                                                     aprDeclaration | 

initialisation :  initi { init=1;} | 

initi : egale espaces exp 

//Les Type Exist
TYPE : mcInt 

val : cte | idf {push($1);}
 
cte : cteInt {push($1);}

opComparaison : not egale {strcpy(op,"!=");} | 
egale egale {strcpy(op,"==");}   | inf  {strcpy(op,"<");}  | 
sup {strcpy(op,">");} | sup egale {strcpy(op,"<=");} | inf egale {strcpy(op,">=");} 

op : pl { push("+");} | mi { push("-");} | dv { push("/");} | mul { push("*");}

indentation : espace | tab

espacess : espace espacess {count++;}  | tab espacess { count=count+8;  } |

espaces : espace espaces   | tab espaces  |

sauts : saut sauts |
            

%%

void yyerror(char* s){
  printf ("erreur syntaxique : ligne %d\n",lignes);
}

int yywrap(){
    return 1;
}

int main(void){ return yyparse();}
