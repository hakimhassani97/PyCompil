typedef struct indentation indentation;
struct indentation {
  char nom[50];
  
  int count;
  int fin;
  int instruction;
  int eliff;
  int elsee;
};

indentation indentations[1000];

int tailleIndentations = 0;

typedef struct QDR QDR;
struct QDR {
  char oper[100];
  char op1[100];
  char op2[100];
  char res[100];
};

QDR quad[1000];

int qc = 0;
int nombre = 1;
typedef struct sauvIndexQdr sauvIndexQdr;
struct sauvIndexQdr {
  int count;
  int qc;
};

sauvIndexQdr tableIndexQdr[1000];
int taileTableIndexQdr = 0;

void ajoutSauv(int count, int qc) {
  tableIndexQdr[taileTableIndexQdr].count = count;
  tableIndexQdr[taileTableIndexQdr].qc = qc;
  taileTableIndexQdr++;
};

void SauverElifElse(int count, int qcc) {
  int i;
  char sauv[10];
  char num_sauv[10];

  for (i = 0; i < taileTableIndexQdr; i++) {
    if (count == tableIndexQdr[i].count) {
      if (strcmp(quad[tableIndexQdr[i].qc].res, "elif") == 0) {

        strcpy(sauv, "");
        sprintf(num_sauv, "%d", qcc);
        strcpy(quad[tableIndexQdr[i].qc].res, strcat(sauv, num_sauv));
      }
    }
  }
}

void lieuElif(int count, int qcc) {
  int i;
  char sauv[10];
  char num_sauv[10];
  int j;
  int YES = 0;
  int qctmp;
  int counttmp;
  for (j = taileTableIndexQdr - 1; j >= 0; j--) {
    if (YES == 0) {
      if (count <= tableIndexQdr[j].count) {
        if (strcmp(quad[tableIndexQdr[j].qc].res, "elif") == 0 && strcmp(quad[qcc - 1].res, "elif") != 0) {
          YES = 1;
          counttmp = tableIndexQdr[j].count;
          strcpy(sauv, "");
          sprintf(num_sauv, "%d", qcc);
          strcpy(quad[tableIndexQdr[j].qc].res, strcat(sauv, num_sauv));

        }
      }
    } else {
      if (YES == 1) {
        if (counttmp == tableIndexQdr[j].count && strcmp(quad[tableIndexQdr[j].qc].res, "elif") == 0) {
          strcpy(sauv, "");
          sprintf(num_sauv, "%d", qcc);
          strcpy(quad[tableIndexQdr[j].qc].res, strcat(sauv, num_sauv));

        }
      }
    }
  }

}

void sauvQdr(int count, int qcc) {
  int i;
  char sauv[10];
  char num_sauv[10];

  for (i = 0; i < taileTableIndexQdr; i++) {
    if (count <= tableIndexQdr[i].count) {
      if (strcmp(quad[tableIndexQdr[i].qc].res, "") == 0) {
        strcpy(sauv, "");
        sprintf(num_sauv, "%d", qcc);
        strcpy(quad[tableIndexQdr[i].qc].res, strcat(sauv, num_sauv));
      }
    }

  }

}

void ajour_quad(int num_quad, int colon_quad, char val[]) {
  if (colon_quad == 0) strcpy(quad[num_quad].oper, val);
  else if (colon_quad == 1) strcpy(quad[num_quad].op1, val);
  else if (colon_quad == 2) strcpy(quad[num_quad].op2, val);
  else if (colon_quad == 3) strcpy(quad[num_quad].res, val);
}

typedef struct INSTRUCTION INSTRUCTION;
struct INSTRUCTION {

  char valeur[100];
};

INSTRUCTION instruction[1000];
int SizeInstruction = 0;

void remplireInstruction(char valeur[]) {
  strcpy(instruction[SizeInstruction].valeur, valeur);
  SizeInstruction++;

}

void ajouterQdr(char oper[], char op1[], char op2[], char res[]) {

  strcpy(quad[qc].oper, oper);
  strcpy(quad[qc].op1, op1);
  strcpy(quad[qc].op2, op2);
  strcpy(quad[qc].res, res);

  qc++;
}

char * operateur(char opr[100]) {
  if (strcmp(opr, "<") == 0) {
    return "BNL";
  }
  if (strcmp(opr, ">") == 0) {
    return "BNG";
  }
  if (strcmp(opr, "==") == 0) {
    return "BNE";
  }
  if (strcmp(opr, "<=") == 0) {
    return "BG";
  }
  if (strcmp(opr, ">=") == 0) {
    return "BL";
  }
  if (strcmp(opr, "!=") == 0) {
    return "BE";
  }
  return "";
}

void decaler(i) {
  int count = 2;
  int pos;
  while (count != 0) {
    pos = i;
    while (pos < SizeInstruction - 1) {
      instruction[pos] = instruction[pos + 1];
      pos++;
    }
    SizeInstruction = SizeInstruction - 1;
    count--;
  }

}
char * getSauv(int nombre) {
  char sauv[10];
  char num_sauv[10];

  strcpy(sauv, "t");
  sprintf(num_sauv, "%d", nombre);

  return strcat(sauv, num_sauv);
}

char * resulta() {

  char val[10];
  int i = 1;
  char t[10];

  if (SizeInstruction == 1) {

    ajouterQdr("=", instruction[0].valeur, "", "");

    SizeInstruction = 0;
  }

  while (i < SizeInstruction) {

    if (ordrePriorite(instruction[i].valeur) == 2) {
      strcpy(t, getSauv(nombre));
      nombre++;
      ajouterQdr(instruction[i].valeur, instruction[i - 1].valeur, instruction[i + 1].valeur, t);
      strcpy(instruction[i - 1].valeur, t);
      decaler(i);

      i = i - 2;
    }

    i = i + 2;
  }

  i = 1;

  while (i < SizeInstruction) {

    if (ordrePriorite(instruction[i].valeur) == 1) {
      strcpy(t, getSauv(nombre));
      nombre++;
      ajouterQdr(instruction[i].valeur, instruction[i - 1].valeur, instruction[i + 1].valeur, t);
      strcpy(instruction[i - 1].valeur, t);
      decaler(i);

      i = i - 2;
    }

    i = i + 2;
  }

  SizeInstruction = 0;

  char sauv[10];
  char num_sauv[10];

  nombre--;
  return getSauv(nombre);
}

void afficher_qdr() {
  printf("********************* Les Quadruplets ***********************\n");
  int i;
  for (i = 0; i < qc; i++) {
    printf("\n %d - ( %s , %s , %s , %s)", i, quad[i].oper, quad[i].op1, quad[i].op2, quad[i].res);
    printf("\n---------------------------------------------------\n");
  }
}

int ordrePriorite(char nom[]) {
  if (strcmp(nom, "+") == 0) return 1;
  if (strcmp(nom, "-") == 0) return 1;
  if (strcmp(nom, "/") == 0) return 2;
  if (strcmp(nom, "*") == 0) return 2;
  return 0;
}

int priorite(int Condition) {
  int PrO = 0;
  int PrF = 0;
  int exist = 0;
  char valeur[100];
  char valeur2[100];
  char OneValeurAndCondition = 0;
  strcpy(valeur, pop());
  if (pile == NULL && Condition == 1) {
    OneValeurAndCondition = 1;

  }

  push(valeur);

  while (pile != NULL) {

    strcpy(valeur, pop());
    push2(valeur);

    if (strcmp(")", valeur) == 0) {
      exist = 1;

      while (pile != NULL && strcmp(valeur, "(") != 0) {

        strcpy(valeur, pop());
        if (strcmp(valeur, "(") != 0) {
          push2(valeur);
        }
      }
      if (strcmp(valeur, "(") == 0) {

        strcpy(valeur2, pop2());

        while (pile2 != NULL && exist == 1) {
          if (strcmp(valeur2, ")") != 0) {
            remplireInstruction(valeur2);
            strcpy(valeur2, pop2());
          } else {
            exist = 0;
          }

        }

        //IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIILLLLLLLLLLLLLLLLLLLLLLLLLLL YYYYYYYYYYYYYYYYYYYYYYYYYA UN PROBLEM CAR RESULTA NO  return pas t +"nombre"             
        push2(resulta());
        nombre++;

        while (pile2 != NULL) {
          strcpy(valeur2, pop2());
          push(valeur2);
        }

      }
    }

  }

  while (pile2 != NULL) {

    strcpy(valeur, pop2());
    remplireInstruction(valeur);
  }

  resulta();
  nombre++;

  return OneValeurAndCondition;

}

void fini(int count, char nom[]) {
  int i = 0;

  while (i < tailleIndentations) {
    if (indentations[i].count >= count) {
      indentations[i].fin = 1;
      if (strcmp("elif", nom) == 0) {
        int y = indentations[i].count - count;
        if (y == 0) {
          indentations[i].eliff++;
        }
      }

      if (strcmp("else", nom) == 0) {

        int y = indentations[i].count - count;

        if (y == 0) {
          indentations[i].elsee++;
        }
      }

    }

    i++;
  }

}
int ExistElifOrIf(int count) {
  int i = 0;
  while (i < tailleIndentations) {
    if (strcmp("if", indentations[i].nom) == 0 || strcmp("elif", indentations[i].nom) == 0) {

      if (indentations[i].count == count && indentations[i].elsee == 1) {

        indentations[i].elsee = 2;

        return 1;
      }

      if (indentations[i].count == count && indentations[i].elsee == 0 && indentations[i].eliff == 1) {

        indentations[i].eliff = 2;

        return 2;
      }
    }
    i++;
  }
  return 0;

}

int VerifierElse(char nom[]) {

  if (strcmp("else", nom) == 0) {
    return 1;
  }
  return 0;
}

int garderEspace(char nom[], int count, int fin) {
  fini(count, nom);
  if (tailleIndentations == 0 && count != 0) {

    printf("\erreur syntaxique : pas d\'espaces au debut d\'instruction \n");
    exit(0);
  } else {
    if (AllInstructionBefor() == 1 && count != indentations[tailleIndentations - 1].count) {
      printf("\erreur syntaxique : erreur d\'indentation  \n");
      exit(0);
    } else {
      if (DebutIfOrElifOrElse(count) == 0) {
        printf("\erreur syntaxique :  l instruction %s est vide  \n", indentations[tailleIndentations - 1].nom);
        exit(0);
      } else {
        if (InIfOrElifOrElse(count) == 0 && count != 0) {

          printf("\erreur syntaxique : erreur d\'indentation \n");
          exit(0);
        } else {

          if (VerifierElse(nom) == 1 && ExistElifOrIf(count) != 1) {
            printf("\erreur syntaxique : else sans if ou bien elif \n");
            exit(0);
          } else {

            if (VerifierElif(nom) == 1 && ExistElifOrIf(count) != 2) {
              printf("\erreur syntaxique : elif sans if ou bien elif \n");
              exit(0);
            }

          }
        }

      }
    }

  }

  strcpy(indentations[tailleIndentations].nom, nom);
  indentations[tailleIndentations].count = count;
  indentations[tailleIndentations].fin = 0;
  indentations[tailleIndentations].instruction = 0;
  indentations[tailleIndentations].eliff = 0;
  indentations[tailleIndentations].elsee = 0;
  tailleIndentations++;
}

int VerifierElif(char nom[]) {
  if (strcmp("elif", nom) == 0) {
    return 1;
  }
  return 0;
}

int AllInstructionBefor() {
  int i = 0;
  while (i < tailleIndentations) {
    if (strcmp("inst", indentations[i].nom) != 0) {
      return 0;
    }
    i++;
  }
  return 1;
}

int DebutIfOrElifOrElse(int count) {
  int i = 0;
  while (i < tailleIndentations) {
    if (strcmp("if", indentations[i].nom) == 0 || strcmp("elif", indentations[i].nom) == 0 ||
      strcmp("else", indentations[i].nom) == 0) {
      if (i == (tailleIndentations - 1)) {
        if (count <= indentations[tailleIndentations - 1].count) {

          return 0;
        } else {

          indentations[tailleIndentations - 1].instruction = count;
        }
      }
    }
    i++;
  }

  return 1;
}

int InIfOrElifOrElse(int count) {
  int i = 0;
  while (i < tailleIndentations) {
    if (strcmp("if", indentations[i].nom) == 0 || strcmp("elif", indentations[i].nom) == 0 ||
      strcmp("else", indentations[i].nom) == 0) {

      if (count == indentations[i].instruction && indentations[i].fin == 0) {

        return 1;
      }

    }
    i++;

  }

  return 0;

}
void supprimer(QDR liste[], int i) {

  while (i < qc) {
    liste[i] = liste[i + 1];
    i++;
  }
  int m = 0;
  while (m < i) {
    //decrementer
    int to = atoi(liste[m].res);
    if (to != 0) {
      to--;
      sprintf(liste[m].res, "%d", to);
    }
    m++;
  }
  qc--;
}
