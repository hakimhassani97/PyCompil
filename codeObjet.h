/***********************************generer le code objet************************************************/
//parcours de la liste des quadreplets
int etiqueUtilise(int et){
  int utilise=0;
  int i = 0;
  char etiq[2];
  sprintf(etiq,"%d",et);
  while (i < qc) {
    if(strcmp(quad[i].res,etiq) == 0) {
      utilise=1;
      break;
    }
    i++;
  }
  return utilise;
}
void codeObjet(QDR listeQuad[]){
  int i,type;
  printf("DATA SEGMENT \n");
  printf("DATA ENDS\n");
  printf("CODE SEGEMENT\n");
  printf("ASSUME CS:CODE, DS:DATA\n");
  printf("MAIN :\n");
  printf("MOV AX,DATA\n");
  printf("MOV DS,AX\n");
  for(i=0;i<qc;i++){
        if(etiqueUtilise(i)==1)printf("etiq %d : \n",i);
        if(strcmp(listeQuad[i].oper,"BNE")==0){
        printf("\tMOV AX, %s\n",listeQuad[i].op1);
        printf("\tCMP AX, %s\n",listeQuad[i].op2);
        printf("\tJNE etiq %s\n",listeQuad[i].res);}
    
        if(strcmp(listeQuad[i].oper,"BE")==0){
        printf("\tMOV AX, %s\n",listeQuad[i].op1);
        printf("\tCMP AX, %s\n",listeQuad[i].op2);
        printf("\tJE etiq %s\n",listeQuad[i].res);}

        if(strcmp(listeQuad[i].oper,"BG")==0){
        printf("\tMOV AX, %s\n",listeQuad[i].op1);
        printf("\tCMP AX, %s\n",listeQuad[i].op2);
        printf("\tJG etiq %s\n",listeQuad[i].res);}

        if(strcmp(listeQuad[i].oper,"BL")==0){
        printf("\tMOV AX, %s\n",listeQuad[i].op1);
        printf("\tCMP AX, %s\n",listeQuad[i].op2);
        printf("\tJL etiq %s\n",listeQuad[i].res);}
       

         if(strcmp(listeQuad[i].oper,"BNL")==0){
        printf("\tMOV AX, %s\n",listeQuad[i].op1);
        printf("\tCMP AX, %s\n",listeQuad[i].op2);
        printf("\tJNL etiq %s\n",listeQuad[i].res);}

         if(strcmp(listeQuad[i].oper,"BNG")==0){
        printf("\tMOV AX, %s\n",listeQuad[i].op1);
        printf("\tCMP AX, %s\n",listeQuad[i].op2);
        printf("\tJNG etiq %s\n",listeQuad[i].res);}

        if(strcmp(listeQuad[i].oper,"BR")==0){
        printf("\tJMP AX, %s\n",listeQuad[i].res);}
      
        if(strcmp(listeQuad[i].oper,"+")==0){
        printf("\tMOV AX, %s\n",listeQuad[i].op1);
        printf("\tADD AX, %s\n",listeQuad[i].op2);
        printf("\tMOV %s, AX\n",listeQuad[i].res);}

        if(strcmp(listeQuad[i].oper,"-")==0){
        printf("\tMOV AX, %s\n",listeQuad[i].op1);
        printf("\tSUB AX, %s\n",listeQuad[i].op2);
        printf("\tMOV %s, AX\n",listeQuad[i].res);}

        if(strcmp(listeQuad[i].oper,"*")==0){
        printf("\tMOV AX, %s\n",listeQuad[i].op1);
        printf("\tMUL AX, %s\n",listeQuad[i].op2);
        printf("\tMOV %s, AX\n",listeQuad[i].res);}

        if(strcmp(listeQuad[i].oper,"/")==0){
        printf("\tMOV AX, %s\n",listeQuad[i].op1);
        printf("\tDIV AX, %s\n",listeQuad[i].op2);
        printf("\tMOV %s, AX\n",listeQuad[i].res);}

        if(strcmp(listeQuad[i].oper,"=")==0){
        printf("\tMOV AX, %s\n",listeQuad[i].op1);
        printf("\tMOV %s, AX\n",listeQuad[i].res);}
  }
  printf("MOV AH,4CH\n");
  printf("INT 21h\n");
  printf("CODE ENDS\n");
  printf("END MAIN\n");
}
