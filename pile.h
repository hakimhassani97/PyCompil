typedef struct Pile Pile;
struct Pile {
  char nom[50];
  Pile * svt;
};

Pile * pile;
Pile * pile2;

void push(char nom[]) {
  Pile * tmp = malloc(sizeof( * tmp));
  strcpy(tmp->nom, nom);
  tmp->svt = pile;
  pile = tmp;
}

char * pop() {
  char nom[50];
  Pile * tmp = pile;
  if (pile != NULL) {
    strcpy(nom, tmp->nom);
    pile = tmp->svt;
    free(tmp);
  }
  return strdup(nom);
}

void push2(char nom[]) {
  Pile * tmp = malloc(sizeof( * tmp));
  strcpy(tmp->nom, nom);
  tmp->svt = pile2;
  pile2 = tmp;
}

char * pop2() {
  char nom[50];
  Pile * tmp = pile2;
  if (pile2 != NULL) {
    strcpy(nom, tmp->nom);
    pile2 = tmp->svt;
    free(tmp);
  }
  return strdup(nom);
}
