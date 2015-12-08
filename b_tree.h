#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define DEGREE 2

typedef struct node {
    int keys[2*DEGREE+1];
    int nbKeys;
    struct node *sons[2*DEGREE+1];
}*B_tree;

typedef enum {false, true} Boolean;

B_tree createTree();
Boolean emptyTree(B_tree tree);
void displayTree(B_tree tree, int height);
B_tree deleteTree(B_tree tree);
B_tree splitNode(B_tree tree);
B_tree addKey(B_tree tree, int key);
Boolean keyBelongs(B_tree tree, int key);
