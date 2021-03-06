#include "b_tree.h"

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
    //rightSon->sons[DEGREE] = tree->sons[2*DEGREE+1];

    // We rearrange the sons of the tree to return
    temp->sons[0] = leftSon;
    temp->sons[1] = rightSon;

    return temp;
}

B_tree addKey(B_tree tree, int key) {
    // If the tree is empty, we had the key
    if(emptyTree(tree)) {
        tree = createTree();
        tree->keys[tree->nbKeys ++] = key;
    }
    else {
        if(! emptyTree(tree->sons[0])) {
            int i = 0;
            while((key > tree->keys[i]) && i < tree->nbKeys) {
                i ++;
            }
            tree->sons[i] = addKey(tree->sons[i], key);

            // If we had to split the node, we assemble with tree
            if(tree->sons[i]->nbKeys == 1) {
                // If there is room for another number
                if(tree->nbKeys < 2*DEGREE) {
                    int j = 0;
                    for(j=tree->nbKeys ; j>i ; j--) {
                        tree->keys[j] = tree->keys[j-1];
                        tree->sons[j+1] = tree->sons[j];
                    }
                    tree->keys[i] = tree->sons[i]->keys[0];
                    tree->sons[i+1] = tree->sons[i]->sons[1];
                    tree->sons[i] = tree->sons[i]->sons[0];
                    tree->nbKeys ++;
                }
                else {
                    B_tree temp = tree->sons[2*DEGREE];

                    int j = 0;
                    for(j=tree->nbKeys ; j>i ; j--) {
                        tree->keys[j] = tree->keys[j-1];
                        tree->sons[j+1] = tree->sons[j];
                    }
                    tree->keys[i] = tree->sons[i]->keys[0];
                    tree->sons[i+1] = tree->sons[i]->sons[1];
                    tree->sons[i] = tree->sons[i]->sons[0];
                    tree->nbKeys ++;

                    tree = splitNode(tree);

                    tree->sons[1]->sons[DEGREE] = temp;
                }
            }
        }
        else {
            int i = 0;
            while((key > tree->keys[i]) && i < tree->nbKeys) {
                i ++;
            }
            int j;
            for(j=tree->nbKeys ; j>i ; j--) {
                tree->keys[j] = tree->keys[j-1];
            }
            tree->keys[i] = key;
            tree->nbKeys ++;

            if(tree->nbKeys == 2*DEGREE+1) {
                tree = splitNode(tree);
            }
        }
        // Here CHECK IF NOMBRE CLES > 2*DEGREE
        // OU PAS ! PUTAIN J'AI OUBLIE !!
    }
    return tree;
}

Boolean keyBelongs(B_tree tree, int key) {
    // If the tree isn't empty
    if(! emptyTree(tree)) {
        int pos;
        // We stop at the right key
        for(pos=0 ; (pos < tree->nbKeys) && (key > tree->keys[pos]) ; pos++) {
        }
        // If the key of the tree we stop at is the key we search, we found it !!
        if(key == tree->keys[pos]) {
            return true;
        }
        // Else, we try with the son
        else {
            return (keyBelongs(tree->sons[pos], key));
        }

    }

    return false;
}
