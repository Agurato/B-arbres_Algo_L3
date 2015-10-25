#define DEGREE 2

typedef struct node {
    int keys[2*DEGREE+1];
    int nbKeys;
    struct node *sons[2*DEGREE+1];
}*B_tree;

typedef enum {false, true} Boolean;

B_tree createTree();
Boolean emptyTree(B_tree tree);
B_tree addKey(B_tree tree, int key);
B_tree deleteKey(B_tree tree, int key);
B_tree keyBelongs(B_tree tree, int key);
void displayTree(B_tree);