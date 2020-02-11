#include "global.h"
#include "analyseur_syntaxique.h"


int main(int argc, char **argv)
{
    file = fopen("test.txt", "r+");
    Car_Cour = fgetc(file);
    do
    {
        sym_suiv();
        INST();
    }while(Car_Cour!=EOF);
}