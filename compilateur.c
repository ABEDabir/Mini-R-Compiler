#include "global.h"
#include "analyseur_syntaxique.h"


int main(int argc, char **argv)
{  
    if (argc != 2){
        printf("no input file\n");
        printf("Usage : %s FILE\n", argv[0]);
        exit(0);
    }
    file = fopen(argv[1], "r+");
    Car_Cour = fgetc(file);
    do
    {
        sym_suiv();
        INST();
    } while(Car_Cour!=EOF);
}