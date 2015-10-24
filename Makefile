all : arbreBinaire

main.o : main.c arbreBinaire.h menu.h arbreBinaire.c
	gcc -c main.c arbreBinaire.c

arbreBinaire.o : arbreBinaire.c arbreBinaire.h
	gcc -c arbreBinaire.c

menu.o : arbreBinaire.h menu.h
	gcc -c menu.c arbreBinaire.c

arbreBinaire : main.o arbreBinaire.o menu.o
 	gcc -o arbreBinaire menu.o main.o arbreBinaire.o
clean :
	rm -rf ./*.o arbreBinaire
