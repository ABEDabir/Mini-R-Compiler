#ifndef COMPILATEURR_ANALYSEUR_LEXICAL_H
#define COMPILATEURR_ANALYSEUR_LEXICAL_H

#include "global.h"
#include "errors.h"


void afficher_Token();
int lire_comm();
int isseparateur();
void lire_nombre();
void lire_mot();
void sym_suiv();
void Test_Symbole(CODES_TOKENS cl, ERREUR_TOKENS COD_ERR);



#endif //COMPILATEURR_ANALYSEUR_LEXICAL_H
