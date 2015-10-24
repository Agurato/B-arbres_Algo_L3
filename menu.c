#include "arbreBinaire.h"
#include "menu.h"

void menu(void){
  int choice = 0;
  B_arbre tree = createBArbre();
  while(choice != 8){
    afficherMenu();
    switch(choice){
      case 1 :

        break;
      case 2 :
        break;
      case 3:
        break;
      case 4 :
        break;
      case 5 :
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
    }
  }

}


void displayMenu(void){
  printf("1) Add key in the tree\n");
  printf("2) Delete a key from the tree\n");
  printf("3) Display the tree\n");
  printf("4) Check if a key belongs to the tree\n");
  printf("5) Remove the tree\n");
  printf("6) Save the tree in a file\n", );
  printf("7) Load a tree from a file\n", );
  printf("8) Quit the program\n", );
}
