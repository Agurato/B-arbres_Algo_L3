#include <stdio.h>
#include <stdlib.h>
#include "libVincent.h"

int main(int argc, char const *argv[]) {

    B_tree tree = createTree();
    tree->nbKeys = 4;
    tree->keys[0] = 9;
    tree->keys[1] = 20;
    tree->keys[2] = 60;
    tree->keys[3] = 100;

    tree->sons[0] = createTree();
    tree->sons[0]->nbKeys = 2;
    tree->sons[0]->keys[0] = 5;
    tree->sons[0]->keys[1] = 8;

    tree->sons[1] = createTree();
    tree->sons[1]->nbKeys = 3;
    tree->sons[1]->keys[0] = 11;
    tree->sons[1]->keys[1] = 17;
    tree->sons[1]->keys[2] = 19;

    tree->sons[2] = createTree();
    tree->sons[2]->nbKeys = 3;
    tree->sons[2]->keys[0] = 41;
    tree->sons[2]->keys[1] = 53;
    tree->sons[2]->keys[2] = 57;

    tree->sons[3] = createTree();
    tree->sons[3]->nbKeys = 3;
    tree->sons[3]->keys[0] = 75;
    tree->sons[3]->keys[1] = 95;
    tree->sons[3]->keys[2] = 99;

    tree->sons[4] = createTree();
    tree->sons[4]->nbKeys = 3;
    tree->sons[4]->keys[0] = 115;
    tree->sons[4]->keys[1] = 135;
    tree->sons[4]->keys[2] = 145;

    int keyAdd[] = {80, 105, 85, 110};
    int i;
    for(i=0 ; i<sizeof(keyAdd)/sizeof(int) ; i++) {
        if(! keyBelongs(tree, keyAdd[i])) {
            tree = addKey(tree, keyAdd[i]);
        }
        /*
        if(tree->nbKeys == 2*DEGREE+1) {
            tree = splitNode(tree);
        }
        */
    }

    displayTree(tree, 0);

    int keyTest;
    printf("\nType in a key to test : ");
    scanf("%d", &keyTest);
    if(keyBelongs(tree, keyTest)) {
        printf("%d belongs to tree\n", keyTest);
    }
    else {
        printf("%d doesn't belong to tree\n", keyTest);
    }

    /*
    B_tree tree = createTree();
    tree->nbKeys = 3;
    tree->keys[0] = 9;
    tree->keys[1] = 20;
    tree->keys[2] = 60;

    tree->sons[0] = createTree();
    tree->sons[0]->nbKeys = 2;
    tree->sons[0]->keys[0] = 5;
    tree->sons[0]->keys[1] = 8;

    tree->sons[1] = createTree();
    tree->sons[1]->nbKeys = 3;
    tree->sons[1]->keys[0] = 11;
    tree->sons[1]->keys[1] = 17;
    tree->sons[1]->keys[2] = 19;

    tree->sons[2] = createTree();
    tree->sons[2]->nbKeys = 3;
    tree->sons[2]->keys[0] = 41;
    tree->sons[2]->keys[1] = 53;
    tree->sons[2]->keys[2] = 57;

    tree->sons[3] = createTree();
    tree->sons[3]->nbKeys = 3;
    tree->sons[3]->keys[0] = 75;
    tree->sons[3]->keys[1] = 80;
    tree->sons[3]->keys[2] = 95;

    tree = addKey(tree, 99);
    tree = addKey(tree, 100);

    displayTree(tree, 0);
    */
    return 0;
}
