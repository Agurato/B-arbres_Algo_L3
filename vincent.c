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
    tree->tempSon = NULL;
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
        tree->keys[tree->nbKeys ++] = key;
    }
    else if(emptyTree(tree->sons[0])){
        int pos;
        for(pos=0 ; (pos < tree->nbKeys) && (key > tree->keys[pos]) ; pos++) {
        }
        printf("tree->sons[0] == NULL : pos=%d\n", pos);
        int i;
        for(i=tree->nbKeys ; i>pos ; i--) {
            tree->keys[i] = tree->keys[i-1];
        }
        tree->keys[pos] = key;
        tree->nbKeys ++;
        printf("\nTree after adding %d :\n", key);
        displayTree(tree, 10);
    }
    else {
        int pos;
        for(pos=0 ; (pos < tree->nbKeys) && (key > tree->keys[pos]) ; pos++) {
        }
        printf("tree->sons[0] != NULL : pos=%d\n", pos);
        tree->sons[pos] = addKey(tree->sons[pos], key);

        if(tree->sons[pos]->nbKeys == 2*DEGREE+1) {
            printf("\ntree->sons[pos]->nbKeys == 2*DEGREE+1\n");
            B_tree temp = splitNode(tree->sons[pos]);
            int i;
            for(i=tree->nbKeys ; i>pos ; i--) {
                tree->keys[i] = tree->keys[i-1];
            }
            tree->keys[pos] = temp->keys[0];
            tree->nbKeys++;
            if(tree->nbKeys == 2*DEGREE+1) {
                tree->tempSon = tree->sons[4];
                for(i=tree->nbKeys-1 ; i>pos ; i--) {
                    tree->sons[i] = tree->sons[i-1];
                }
            }
            tree->sons[pos] = temp->sons[0];
            tree->sons[pos+1] = temp->sons[1];
            printf("temp created !\n");
        }

        if(! emptyTree(tree->tempSon)) {
            B_tree temp = splitNode(tree);
            temp->sons[1]->sons[DEGREE] = tree->tempSon;

            tree = temp;

            free(tree->tempSon);
            tree->tempSon = NULL;
        }
    }

    return tree;
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
