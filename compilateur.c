#include "global.h"

// |--> Didn't understand! <--|
// Erreurs Sym_Erreur;


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