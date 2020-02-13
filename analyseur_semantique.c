#include "analyseur_semantique.h"


// initialiser la table de symbole
void init_table_symbole() {
    taille_table_symbole = 0;
    taille_max_table_symbole = 10;
    adresse_actuelle = 0;

    table_symbole = malloc(taille_max_table_symbole * sizeof(struct symbole_stocke));
}

// changer la taille de la table de symbole
static void changer_taille() {
    taille_max_table_symbole += 10;
    table_symbole = realloc(table_symbole, taille_max_table_symbole * sizeof(struct symbole_stocke));
}

// ajouter un symbole à la table de symbole
boolean ajouter_symbole() {
    // Vérifier d'abord que le symbole existe dans la table des symboles
    if (symbole_existe() == -1) {
        // If there are no more space in the symbol table
        if (taille_table_symbole > taille_max_table_symbole) {
            changer_taille();
        }
        // ajout du symbole à la table
        strcpy(table_symbole[taille_table_symbole].nom, Sym_Cour.nom);
        table_symbole[taille_table_symbole].offset   = addresse_offset;
        table_symbole[taille_table_symbole].end      = 0;

        table_symbole[taille_table_symbole].addresse = addresse_offset + adresse_actuelle++;

        // Incrémentation de la taille de la table des symboles
        taille_table_symbole++;
    }
    else
        return false;
}

int symbole_existe() {
    for (int i = 0; i < taille_table_symbole; i++) {
        if ( strcmp(table_symbole[i].nom, Sym_Cour.nom) == 0 )
            return i;
    }
    return -1;
}

// Obtenir l'adresse du symbole actuel

int get_address() {
    for (int i = 0; i < taille_table_symbole; i++) {
        if ( strcmp(table_symbole[i].nom, Sym_Cour.nom) == 0 )
            return table_symbole[i].addresse;
    }

    return -1;
}

/* Vérifier si un symbole spécifique existe déjà dans la table des symboles
 * renvoie l'index du symbole dans le tableau s'il existe
 * ou retourner -1 si le symbole n'existe pas dans le tableau
 */

int symbole_specifique_existe(char *symbole) {
    for (int i = 0; i < taille_table_symbole; i++) {
        if ( strcmp(table_symbole[i].nom, symbole) == 0 )
            return i;
    }
    return -1;
}
