//
// Created by AIT RAMI on 2/10/2020.
//

#include "analyseur_syntaxique.h"

void FUNCTION(){

    Test_Symbole(PO_TOKEN,PO_ERR);
    do{
        Test_Symbole(ID_TOKEN, ID_ERR);
        //   if(Sym_Cour.cls==AFF_TOKEN){
        //     Test_Symbole(NUM_TOKEN, NUM_ERR);
        // }
    }
    while(Sym_Cour.cls==VIR_TOKEN);
    Test_Symbole(PF_TOKEN,PF_ERR);
    Test_Symbole(AO_TOKEN,AO_ERR);
    INST();
    Test_Symbole(AF_TOKEN,AF_ERR);
}
void AFF(){
    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(AFF_TOKEN, AFF_ERR);

    Test_Symbole(NUM_TOKEN, NUM_ERR);

}
void FACT()
{
    switch (Sym_Cour.cls)
    {
        case ID_TOKEN:
            sym_suiv();
            break;
        case NUM_TOKEN:
            sym_suiv();
            break;
        case PO_TOKEN:
            sym_suiv();
            EXPR();
            Test_Symbole(PF_TOKEN, PF_ERR);
            break;
        default:
            afficher_Erreur(FACT_ERR);
    }
}
void MULT_DIV(){
    switch (Sym_Cour.cls)
    {
        case MULT_TOKEN:
            sym_suiv();
            break;
        case DIV_TOKEN:
            sym_suiv();
            break;
        default:
            afficher_Erreur(MULT_DIV_ERR);
    }
}

void PLUS_MOINS(){
    switch (Sym_Cour.cls)
    {
        case PLUS_TOKEN:
            sym_suiv();
            break;
        case MOINS_TOKEN:
            sym_suiv();
            break;
        default:
            afficher_Erreur(MOINS_PLUS_ERR);
    }
}
void TERM(){
    FACT();
    if (Sym_Cour.cls == DIV_TOKEN || Sym_Cour.cls == MULT_TOKEN)
    {
        MULT_DIV();
        FACT();
    }
}
void EXPR(){
    TERM();
    if (Sym_Cour.cls == PLUS_TOKEN || Sym_Cour.cls == MOINS_TOKEN)
    {
        PLUS_MOINS();
        TERM();
    }

}

void COND(){
    EXPR();
    sym_suiv();
    EXPR();
}
//SI := IF(COND){INST} [ELSE{INST}|e]
void SI()
{
    Test_Symbole(IF_TOKEN, IF_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR);
    COND();
    Test_Symbole(PF_TOKEN,PF_ERR);
    Test_Symbole(AO_TOKEN,AO_ERR);
    INST();
    Test_Symbole(AF_TOKEN,AF_ERR);
    if (Sym_Cour.cls == ELSE_TOKEN) {
        Test_Symbole(AO_TOKEN,AO_ERR);
        sym_suiv();
        INST();
        Test_Symbole(AF_TOKEN,AF_ERR);
    }
}
void TANTQUE(){
    Test_Symbole(WHILE_TOKEN, WHILE_ERR);
    Test_Symbole(PO_TOKEN,PO_ERR);
    COND();
    Test_Symbole(PF_TOKEN,PF_ERR);
    Test_Symbole(AO_TOKEN, AO_ERR);
    INST();
    Test_Symbole(AF_TOKEN,AF_ERR);
}
void POUR()
{
    Test_Symbole(FOR_TOKEN, FOR_ERR);
    Test_Symbole(PO_TOKEN,PO_ERR);
    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(IN_TOKEN, IN_ERR);
    Test_Symbole(NUM_TOKEN, NUM_ERR);
    Test_Symbole(PP_TOKEN,PP_ERR);
    Test_Symbole(NUM_TOKEN,NUM_ERR);
    Test_Symbole(PF_TOKEN,PF_ERR);
    Test_Symbole(AO_TOKEN,AO_ERR);
    INST();
    Test_Symbole(AF_TOKEN,AF_ERR);
}

void INST()
{
    switch(Sym_Cour.cls)
    {
        case ID_TOKEN: AFF(); break;
        case IF_TOKEN: SI(); break;
        case WHILE_TOKEN:   TANTQUE(); break;
        case FOR_TOKEN: POUR(); break;
        case FUNCTION_TOKEN: FUNCTION();break;
    }
}