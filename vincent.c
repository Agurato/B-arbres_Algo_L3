#include <stdio.h>
#include <stdlib.h>
#include "libVincent.h"

B_tree createTree() {
    int i;
    B_tree tree = malloc(sizeof(struct node));
    tree->nbKeys = 0;
    for(i=0 ; i<2*DEGREE+1 ; i++) {
        tree->sons[i] = NULL;
    }
    return tree;
}

Boolean emptyTree(B_tree tree) {
    return (tree == NULL);
}

B_tree deleteTree(B_tree tree) {
    if(! emptyTree(tree)) {
        int i;
        for(i=0 ; i<2*DEGREE+1 ; i++) {
            tree->sons[i] = deleteTree(tree->sons[i]);
        }
        free(tree);
    }

    return NULL;
}

B_tree splitNode(B_tree tree) {
    int i;
    B_tree temp = createTree();
    // We put the middle value in the new root
    temp->keys[tree->nbKeys ++] = tree->keys[DEGREE];

    B_tree leftSon, rightSon;

    // We keep only the values on the left to put in the left son
    for(i=2*DEGREE ; i>=DEGREE ; i--) {
        leftSon = deleteTree(tree->sons[i]);
        leftSon->keys[-- tree->nbKeys] = 0;
    }
    // We keep only the values on the right to put in the right son
    for(i=0 ; i<=DEGREE ; i++) {
        rightSon = deleteTree(tree->sons[i]);
        rightSon->keys[-- tree->nbKeys] = 0;
    }

    // We rearrange the sons of the tree to return
    temp->sons[0] = leftSon;
    temp->sons[1] = rightSon;

    return temp;
}

B_tree addKey(B_tree tree, int key) {
    if(emptyTree(tree)) {
        tree = createTree();
    }
    /*
    // ERREUR : il faut ajouter aux feuilles avant d'ajouter à la racine !!!
    // If the tree is empty
    if(emptyTree(tree)) {
        // We create it, add the key in the keys tab, and increment the nb of keys
        tree = createTree();
        tree->keys[tree->nbKeys ++] = key;
    }
    else if(tree->nbKeys < 2*DEGREE) {
        tree->keys[tree->nbKeys ++] = key;
    }
    else if(tree->nbKeys == 2*DEGREE) {
        tree->keys[tree->nbKeys ++] = key;
        B_tree temp = createTree();
        temp->keys[temp->nbKeys ++] = tree->keys[tree->nbKeys /2];
    }
    else {
        printf("Error : tree->nbKeys > 2*DEGREE");
    }
    */
}

B_tree deleteKey(B_tree tree, int key) {

}

B_tree keyBelongs(B_tree tree, int key) {

}

void displayTree(B_tree tree) {

}
