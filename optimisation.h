//optimiser le code
//verifier la probagation de copie
//verifier la probagation d'expression
//verifier le code inutile
//simplifications algebriques
//exprissions redondantes

void propagationCopie(QDR liste[], int qcmax) {
  int i = 0;
  int j = 0;
  while (i < qc) {
    if (strcmp(liste[i].oper, "=") == 0 &&
      strcmp(liste[i].op1, liste[i].res) == 0 &&
      strcmp(liste[i].op2, "") == 0) {
      supprimer(liste, i);
    } else {
      i++;
    }
  }
  i = 0;
  while (i < qc) {
    if (strcmp(liste[i].oper, "-") == 0 || strcmp(liste[i].oper, "=") == 0 || strcmp(liste[i].oper, "/") == 0) {
      j = i + 1;
      while (j < qc) {
        if (strcmp(liste[i].res, liste[j].res) == 0) {
          if (strcmp(liste[i].op1, liste[j].op1) == 0 && strcmp(liste[i].op2, liste[j].op2) == 0 &&
            strcmp(liste[i].oper, liste[j].oper) == 0) {
            supprimer(liste, j);
            j--;
          } else {
            break;
          }
        }
        j++;
      }
    } else {
      if (strcmp(liste[i].oper, "+") == 0 || strcmp(liste[i].oper, "*") == 0) {
        j = i + 1;
        while (j < qc) {
          if (strcmp(liste[i].res, liste[j].res) == 0) {
            if (((strcmp(liste[i].op1, liste[j].op1) == 0 && strcmp(liste[i].op2, liste[j].op2) == 0) ||
                strcmp(liste[i].op1, liste[j].op2) == 0 && strcmp(liste[i].op2, liste[j].op1) == 0) &&
              strcmp(liste[i].oper, liste[j].oper) == 0) {
              supprimer(liste, j);
              j--;
            } else {
              break;
            }
          }
          j++;
        }
      }
    }
    i++;
  }
  i = 0;
  j = 0;
  while (i < qc) {
    if (strcmp(liste[i].oper, "*") == 0) {
      if (strcmp(liste[i].op1, "2") == 0) {
        strcpy(liste[i].op1, liste[i].op2);
        strcpy(liste[i].oper, "+");
      }
      if (strcmp(liste[i].op2, "2") == 0) {
        strcpy(liste[i].op2, liste[i].op1);
        strcpy(liste[i].oper, "+");
      }
    }

    if (strcmp(liste[i].oper, "+") == 0 || strcmp(liste[i].oper, "-") == 0 ||
      strcmp(liste[i].oper, "/") == 0 || strcmp(liste[i].oper, "*") == 0) {
      j = i + 1;
      while (j < qc) {
        if (strcmp(liste[j].res, liste[i].res) != 0) {
          if (strcmp(liste[j].oper, liste[i].oper) == 0 && strcmp(liste[j].op1, liste[i].op1) == 0 &&
            strcmp(liste[j].op2, liste[i].op2) == 0) {
            strcpy(liste[j].oper, "=");
            strcpy(liste[j].op1, liste[i].res);
            strcpy(liste[j].op2, "");
          }
        } else {
          if (strcmp(liste[j].oper, liste[i].oper) == 0 && strcmp(liste[j].op1, liste[i].op1) == 0 &&
            strcmp(liste[j].op2, liste[i].op2) == 0) {
            strcpy(liste[j].oper, "=");
            strcpy(liste[j].op1, liste[i].res);
            strcpy(liste[j].op2, "");
          } else {
            j = qc;
          }
        }
        j++;
      }
    }
    i++;
  }
  /////////////////suppresion du code inutile///////////////////////
  int n = 0;
  for (n = 0; n < 3; n++) {
    i = 0;
    j = 0;
    while (i < qc) {
      if (strcmp(liste[i].oper, "=") == 0) {
        j = i + 1;
        int b = 0;
        while (j < qc && b == 0) {
          if (strcmp(liste[i].res, liste[j].op1) == 0 || strcmp(liste[i].res, liste[j].op2) == 0) {
            b = 1;
          }
          j++;
        }
        if (b == 0) {
          supprimer(liste, i);
        }
      }
      i++;
    }
  }
  ////////////////////////suppresion du code inutile////////////////////////
  i = 0;
  while (i < qc) {
    if (strcmp(liste[i].oper, "=") == 0 && strcmp(liste[i].op1, liste[i].res) == 0 && strcmp(liste[i].op2, liste[i].res) == 0)
      supprimer(liste, i);
    else
      i++;
  }
}
