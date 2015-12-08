#include "b_tree.h"

int type_n();
int displayMenu(void);

int main(int argc, char *argv[]){
    int choice = 0;
    int values[1000] = {0};
    int valuesSize = 0, userValue = 0;

    int i;

    B_tree tree = createTree();
    while(choice != 8){
        choice = displayMenu();
        switch(choice){
            case 1 :
                do {
                    printf("Enter the key you want to add (must be > 0) : ");
                    scanf("%d", &userValue);
                } while(userValue <= 0);

                if(keyBelongs(tree, userValue)) {
                    printf("\x1b[31mError : the key already exists\x1b[0m\n\n");
                }
                else {
                    tree = addKey(tree, userValue);
                    values[valuesSize ++] = userValue;
                    printf("\x1b[32mSucceeded !\x1b[0m\n\n");
                }
                userValue = 0;
                break;
            case 2 :
                do {
                    printf("Enter the key you want to delete (must be > 0) : ");
                    scanf("%d", &userValue);
                } while(userValue <= 0);

                if(! keyBelongs(tree, userValue)) {
                    printf("\x1b[31mError : the key does not exists\x1b[0m\n\n");
                }
                else {
                    for(i=0 ; i<valuesSize ; i++) {
                        if(userValue == values[i]) {
                            int j;
                            valuesSize --;
                            for(j=i ; j<valuesSize ; j++) {
                                values[j] = values[j+1];
                            }
                        }
                    }

                    tree = deleteTree(tree);
                    tree = createTree();

                    for(i=0 ; i<valuesSize ; i++) {
                        tree = addKey(tree, values[i]);
                    }
                    printf("\x1b[32mSucceeded !\x1b[0m\n\n");
                }
                userValue = 0;
                break;
            case 3:
                displayTree(tree, 0);
                printf("\n");
                break;
            case 4 :
                do {
                    printf("Enter the key you want to search (must be > 0) : ");
                    scanf("%d", &userValue);
                } while(userValue <= 0);
                if(keyBelongs(tree, userValue)) {
                    printf("\x1b[34mThe values exists\n\n\x1b[0m");
                }
                else {
                    printf("\x1b[34mThe values does not exist\n\n\x1b[0m");
                }
                userValue = 0;
                break;
            case 5 :
                tree = deleteTree(tree);
                for(i=0 ; i<1000 ; i++) {
                    values[i] = 0;
                }
                tree = createTree();
                printf("\x1b[32mSucceeded !\x1b[0m\n\n");
                break;
            case 6:
                break;
            case 7 :
                break;
            case 8 :
                printf("\n\n\t\t\tGood Bye !! See you soon\n\n");
                printf("\tMade by Vincent MONOT and Paul VALENTIN\n");
                break;
            default :
                break;
        }
    }

    return 0;
}

int type_n() {
    char *c = malloc(sizeof(char));

    scanf("%s",c);
    if(isdigit(*c))
        return (int) *c - '0';
    return -1;
}

int displayMenu(void) {
	int choice = 0;

	do {
        printf("1) Add key in the tree\n");
        printf("2) Delete a key from the tree\n");
        printf("3) Display the tree\n");
        printf("4) Check if a key belongs to the tree\n");
        printf("5) Remove the tree\n");
        printf("6) Save the tree in a file\n");
        printf("7) Load a tree from a file\n");
        printf("8) Quit the program\n");

		printf("Enter your choice : ");
        choice = type_n();
		printf("choice : %d\n",choice);
	} while((choice < 1 || choice > 8));

	return choice;
}
