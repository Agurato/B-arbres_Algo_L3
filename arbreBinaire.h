#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define Degre 5

typedef int Key
typedef struct noeud{
  int key[2*Degre+1];
  int nbKeys;
  struct noeud *Son[2*Degre+1];
}*B_arbre;

B_arbre createBArbre();
B_arbre addKey(B_arbre,Key);
B_arbre removeKey(B_arbre,Key);
B_arbre belongKey(B_arbre,Key);
int voidBArbre(B_arbre);
