#define DEGREE 2

typedef struct node {
    int keys[2*DEGREE+1];
    int nbKeys;
    struct node *sons[2*DEGREE+1];
}*B_tree;

typedef enum {false, true} Boolean;

B_tree createTree();
Boolean emptyTree(B_tree tree);
B_tree deleteTree(B_tree tree);
B_tree explodeNode(B_tree tree, Boolean addOnLeft);
B_tree splitNode(B_tree tree);
B_tree addKey(B_tree tree, int key);
B_tree addKey2(B_tree tree, int key);
Boolean isInLeaf(B_tree tree, int key);
B_tree switchKeys(B_tree tree, int key);
B_tree removeKey(B_tree tree, int key);
B_tree removeKeyInLeaf(B_tree tree, int x);
Boolean keyBelongs(B_tree tree, int key);
void displayTree(B_tree tree, int height);
B_tree voidTree(B_tree tree);
