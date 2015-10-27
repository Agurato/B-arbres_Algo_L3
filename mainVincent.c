#include <stdio.h>
#include <stdlib.h>
#include "libVincent.h"

int main(int argc, char const *argv[]) {

    /* This is an example of a tree
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

    displayTree(tree);

    tree = deleteTree(tree);

    printf("\nAfter deletion :\n");
    */

    B_tree tree = createTree();
    tree->nbKeys = 5;
    tree->keys[0] = 9;
    tree->keys[1] = 20;
    tree->keys[2] = 60;
    tree->keys[3] = 85;
    tree->keys[4] = 100;

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
    tree->sons[3]->nbKeys = 2;
    tree->sons[3]->keys[0] = 75;
    tree->sons[3]->keys[1] = 80;

    tree->sons[4] = createTree();
    tree->sons[4]->nbKeys = 2;
    tree->sons[4]->keys[0] = 95;
    tree->sons[4]->keys[1] = 99;

    tree->sons[5] = createTree();
    tree->sons[5]->nbKeys = 3;
    tree->sons[5]->keys[0] = 115;
    tree->sons[5]->keys[1] = 135;
    tree->sons[5]->keys[2] = 145;

    tree = splitNode(tree);

    displayTree(tree, 0);

    return 0;
}
