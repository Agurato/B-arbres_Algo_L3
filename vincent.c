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
    temp->keys[temp->nbKeys ++] = tree->keys[DEGREE];

    // We create the left and right sons
    B_tree leftSon = createTree();
    B_tree rightSon = createTree();

    // We had the keys and sons to the left son
    for(i=0 ; i<DEGREE ; i++) {
        leftSon->keys[leftSon->nbKeys ++] = tree->keys[i];
        leftSon->sons[i] = tree->sons[i];
    }
    leftSon->sons[DEGREE] = tree->sons[DEGREE];

    // We had the keys and sons to the right son
    for(i=DEGREE+1 ; i<2*DEGREE+1 ; i++) {
        rightSon->keys[rightSon->nbKeys ++] = tree->keys[i];
        rightSon->sons[i-DEGREE-1] = tree->sons[i];
    }
    rightSon->sons[DEGREE] = tree->sons[2*DEGREE+1];

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

void displayTree(B_tree tree, int height) {
    if(! emptyTree(tree)) {
        int i;
        printf("%d \\ ", height);
        for(i=0 ; i<tree->nbKeys ; i++) {
            printf("%d - ", tree->keys[i]);
        }
        printf("\n");
        for(i=0 ; i<DEGREE*2+1 ; i++) {
            displayTree(tree->sons[i], height+1);
        }
    }
}
