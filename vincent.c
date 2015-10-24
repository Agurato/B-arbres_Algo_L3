#include <stdio.h>
#include <stdlib.h>

B_tree createTree() {
    B_tree tree = malloc(sizeof(struct node));
    tree->nbKeys = 0;
    return tree;
}

Boolean emptyTree(B_tree tree) {
    return (tree == NULL);
}

B_tree addKey(B_tree tree, int key) {
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
    else
        printf("Error : tree->nbKeys > 2*DEGREE");
    }
}

B_tree deleteKey(B_tree tree, int key) {

}

B_tree keyBelongs(B_tree tree, int key) {

}

void displayTree(B_tree) {

}
