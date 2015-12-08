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
    //tree->tempSon = NULL;
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

B_tree explodeNode(B_tree tree, Boolean addOnLeft) {
    int i = 0, limit = DEGREE;
    B_tree father = createTree();
    B_tree leftSon = createTree();
    B_tree rightSon = createTree();

    if(addOnLeft) {
        limit = DEGREE-1;
    }

    father->keys[father->nbKeys ++] = tree->keys[limit];
    for(i=0 ; i<limit ; i++) {
        leftSon->keys[i] = tree->keys[i];
        leftSon->sons[i] = tree->sons[i];
        leftSon->nbKeys ++;
    }
    leftSon->sons[i] = tree->sons[i];

    for(i=limit+1 ; i<2*DEGREE ; i++) {
        rightSon->keys[rightSon->nbKeys] = tree->keys[i];
        rightSon->sons[rightSon->nbKeys] = tree->sons[i];
        rightSon->nbKeys ++;
    }
    rightSon->sons[rightSon->nbKeys] = tree->sons[i];

    father->sons[0] = leftSon;
    father->sons[1] = rightSon;

    return father;
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

B_tree addKey2(B_tree tree, int key) {
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
            tree->sons[i] = addKey2(tree->sons[i], key);

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

Boolean isInLeaf(B_tree tree, int key) {
    int i;
    Boolean found = false;

    while(! found) {
        i = 0;
        while((key < tree->keys[i]) && (i < tree->nbKeys)) {
            i++;
        }
        if(key != tree->keys[i]) {
            tree = tree->sons[i];
        }
        else {
            found = true;
        }
    }

    if(emptyTree(tree->sons[0])) {
        return true;
    }

    return false;
}

B_tree switchKeys(B_tree tree, int key) {
    if(!emptyTree(tree)) {
        int i = 0;
        // Get to the right position
        while((key > tree->keys[i]) && (i < tree->nbKeys)) {
            i ++;
        }
        // If we didn't find it, search in the son
        if(key != tree->keys[i]) {
            tree->sons[i] = switchKeys(tree->sons[i], key);
        }
        // else, we found it !!
        else {
            if(emptyTree(tree->sons[0])) {
                return tree;
            }
            else {
                int temp = tree->keys[i];
                int index;
                // If it's better to switch with the left son, we switch the max value of the left son
                if(tree->sons[i]->nbKeys >= tree->sons[i+1]->nbKeys) {
                    tree->keys[i] = tree->sons[i]->keys[tree->sons[i]->nbKeys-1];
                    tree->sons[i]->keys[tree->sons[i]->nbKeys-1] = temp;
                    index = i;
                }
                // else, we switch with the min value of the right son
                else {
                    tree->keys[i] = tree->sons[i+1]->keys[0];
                    tree->sons[i+1]->keys[0] = temp;
                    index = i+1;
                }

                // If where we switched the keys is a inner node, we re-call the function
                if(! emptyTree(tree->sons[index]->sons[0])) {
                    tree->sons[index] = switchKeys(tree->sons[index], key);
                }
            }
        }
    }

    return tree;
}

B_tree removeKey2(B_tree tree, int key) {
    tree = voidTree(tree);

    

    return tree;
}

B_tree removeKey(B_tree tree, int key) {
    if(! emptyTree(tree)) {
        int i = 0;
        // Get to the right position
        while((key > tree->keys[i]) && (i < tree->nbKeys)) {
            i ++;
        }
        // If we didn't find it, search in the son
        if(key != tree->keys[i]) {
            tree->sons[i] = switchKeys(tree->sons[i], key);
        }
        // else, we found it !!
        else {
            // We delete the key if there is enough keys
            if(tree->nbKeys > DEGREE) {
                int j;
                tree->nbKeys --;
                for(j=i ; j<tree->nbKeys ; j++) {
                    tree->keys[j] = tree->keys[j+1];
                }
            }
        }

        // If we didn't manage to delete it
        int j=0;
        while((key > tree->sons[i]->keys[j]) && (j < tree->sons[i]->nbKeys)) {
            j++;
        }

        if(key == tree->sons[i]->keys[j]) {
            int prevKeys = 0, nextKeys = 0;
            if(i > 0) {
                prevKeys = tree->sons[i-1]->nbKeys;
            }
            if(i < tree->nbKeys) {
                nextKeys = tree->sons[i+1]->nbKeys;
            }

            if(prevKeys >= nextKeys) {
                if(prevKeys > DEGREE) {
                    // We shift all the keys
                    int k;
                    for(k=j ; k<tree->nbKeys-1 ; j++) {
                        tree->sons[i]->keys[k] = tree->sons[i]->keys[k+1];
                    }
                    tree->sons[i]->nbKeys --;
                    // We add the replacing key to the left;
                    tree->sons[i] = addKey2(tree->sons[i], tree->keys[i-1]);
                    // We put the left son's right key on the father
                    tree->keys[i-1] = tree->sons[i-1]->keys[prevKeys-1];
                    tree->sons[i-1]->nbKeys --;
                }
            }
            else {
                if(nextKeys > DEGREE) {
                    // We shift all the keys
                    int k;
                    for(k=j ; k<tree->nbKeys-1 ; j++) {
                        tree->sons[i]->keys[k] = tree->sons[i]->keys[k+1];
                    }
                    tree->sons[i]->nbKeys --;
                    // We add the replacing key to the left;
                    tree->sons[i] = addKey2(tree->sons[i], tree->keys[i]);
                    // We put the right son's left key on the father
                    tree->keys[i] = tree->sons[i+1]->keys[0];
                    tree->sons[i+1]->nbKeys --;
                    for(k=0 ; k<tree->sons[i+1]->nbKeys ; k++) {
                        tree->sons[i+1]->keys[k] = tree->sons[i+1]->keys[k+1];
                    }
                }
            }
        }

    }

    return tree;
}

B_tree mergeNode(B_tree tree) {
    return NULL;
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

B_tree voidTree(B_tree tree) {
    if(! emptyTree(tree)) {
        if(! emptyTree(tree->sons[0])) {
            int i;
            for(i=0 ; i<2*DEGREE+1 ; i++) {
                tree->sons[0] = voidTree(tree->sons[0]);
            }
        }
        int i;
        for(i=0 ; i<2*DEGREE+1 ; i++) {
            free(tree);
            tree = NULL;
        }
    }
    return tree;
}

/*
B_tree addKey(B_tree tree, int key) {
    // If the tree is empty, we simply add the new key
    if(emptyTree(tree)) {
        tree = createTree();
        tree->keys[tree->nbKeys ++] = key;
    }
    // If the sons of the tree are empty
    else if(emptyTree(tree->sons[0])){
        int pos;
        for(pos=0 ; (pos < tree->nbKeys) && (key > tree->keys[pos]) ; pos++) {
        }
        int i;
        // We shift all the values to add the new one in the right place
        for(i=tree->nbKeys ; i>pos ; i--) {
            tree->keys[i] = tree->keys[i-1];
        }
        tree->keys[pos] = key;
        tree->nbKeys ++;
    }
    // Else
    else {
        int pos;
        // We had the value via the right son
        for(pos=0 ; (pos < tree->nbKeys) && (key > tree->keys[pos]) ; pos++) {
        }
        tree->sons[pos] = addKey(tree->sons[pos], key);

        // If the son where we added is full, we split the son
        if(tree->sons[pos]->nbKeys == 2*DEGREE+1) {
            B_tree temp = splitNode(tree->sons[pos]);
            int i;
            // We shift all the values, and add the root of the split to the right place
            for(i=tree->nbKeys ; i>pos ; i--) {
                tree->keys[i] = tree->keys[i-1];
            }
            tree->keys[pos] = temp->keys[0];
            tree->nbKeys++;
            // If the tree where the split root was added is full
            if(tree->nbKeys == 2*DEGREE+1) {
                // We save the last son apart from the list
                tree->tempSon = tree->sons[4];
            }
            // We shift the sons and add the 2 split sons
            for(i=tree->nbKeys-1 ; i>pos ; i--) {
                tree->sons[i] = tree->sons[i-1];
            }
            tree->sons[pos] = temp->sons[0];
            tree->sons[pos+1] = temp->sons[1];
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
*/
