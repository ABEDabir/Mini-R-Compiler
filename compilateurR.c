#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE *file;
char Car_Cour, Car_Prec;

int ligne = 1, col = 1, i;
char *chaine_p, chaine[100];

void EXPR();
void INSTS();
void INST();
void COND();


typedef enum
{
  TYPE_VAR,
  TYPE_CONST,
  TYPE_PROGRAM
} type_symoble;

typedef struct
{
  type_symoble type;
  char nom[20];
  int adresse_val;
} Symbole;

typedef struct
{
  Symbole *tab;
  int taille;
} _tab_symbole;

_tab_symbole tab_symbole;


char *ErreurNames[] = {
    "ERR_FICH_VID",
    "ERR_CAR_INC",
    "ERR_ID_LONG",
    "ERR_NUM_LONG",
    "ERR_END_COM",
};

typedef enum
{
  NUM_TOKEN,
  VAR_TOKEN,
  IF_TOKEN,
  ELSE_TOKEN,
  WHILE_TOKEN,
  FOR_TOKEN,
  IN_TOKEN,
  PV_TOKEN,
  PT_TOKEN,
  PLUS_TOKEN,
  MOINS_TOKEN,
  MULT_TOKEN,
  DIV_TOKEN,
  VIR_TOKEN,
  AFF_TOKEN,
  INF_TOKEN,
  INFEG_TOKEN,
  SUP_TOKEN,
  SUPEG_TOKEN,
  DIFF_TOKEN,
  PO_TOKEN,
  PF_TOKEN,
  ID_TOKEN,
  ERREUR_TOKEN,
  EOF_TOKEN,
  EG_TOKEN,
  REPEAT_TOKEN,
  OF_TOKEN,
  PP_TOKEN,
  AO_TOKEN,
  AF_TOKEN,
  RETURN_TOKEN,
  FUNCTION_TOKEN,
  HASH_TOKEN,
  IFELSE_TOKEN,
  TRUE_TOKEN,
  FALSE_TOKEN,
  AND_TOKEN,
  OR_TOKEN

} CODES_TOKENS;
//CODES_TOKENS Sym_Cour, Sym_Prec;

typedef struct
{
  CODES_TOKENS cls;
  char nom[25];
} CODES_LEX;
CODES_LEX Sym_Cour, Sym_Prec;
typedef enum
{
  PROGRAM_ERR,
  NUM_ERR,
  CONST_ERR,
  VAR_ERR,
  BEGIN_ERR,
  END_ERR,
  IF_ERR,
  THEN_ERR,
  WHILE_ERR,
  DO_ERR,
  READ_ERR,
  WRITE_ERR,
  PV_ERR,
  PT_ERR,
  PLUS_ERR,
  MOINS_ERR,
  MULT_ERR,
  DIV_ERR,
  VIR_ERR,
  AFF_ERR,
  INF_ERR,
  INFEG_ERR,
  SUP_ERR,
  SUPEG_ERR,
  DIFF_ERR,
  PO_ERR,
  PF_ERR,
  FIN_ERR,
  ID_ERR,
  ERREUR_ERR,
  EOF_ERR,
  EG_ERR,
  ELSE_ERR,
  FOR_ERR,
  INTO_ERR,
  DOWNTO_ERR,
  REPEAT_ERR,
  UNTIL_ERR,
  CASE_ERR,
  OF_ERR,
  PP_ERR,
  CONST_VAR_BEGIN_ERR,
  VAR_BEGIN_ERR,
  MOINS_PLUS_ERR,
  MULT_DIV_ERR,
  FACT_ERR,
  INTO_DOWNTO_ERR,
  SYMBOLE_EXIST_ERR,
  SYMBOLE_NOT_DECLARED_ERR,
  SYMBOLE_CONST_MODIF_ERR,
  SYMBOLE_PROGID_MODIF_ERR,AO_ERR,AF_ERR,
  IN_ERR,FUNCTION_ERR
} ERREUR_TOKENS;

char *TokenNames[] = {
  "NUM_TOKEN",
  "VAR_TOKEN",
  "IF_TOKEN",
  "ELSE_TOKEN",
  "WHILE_TOKEN",
  "FOR_TOKEN",
  "IN_TOKEN",
  "PV_TOKEN",
  "PT_TOKEN",
  "PLUS_TOKEN",
  "MOINS_TOKEN",
  "MULT_TOKEN",
  "DIV_TOKEN",
  "VIR_TOKEN",
  "AFF_TOKEN",
  "INF_TOKEN",
  "INFEG_TOKEN",
  "SUP_TOKEN",
  "SUPEG_TOKEN",
  "DIFF_TOKEN",
  "PO_TOKEN",
  "PF_TOKEN",
  "ID_TOKEN",
  "ERREUR_TOKEN",
  "EOF_TOKEN",
  "EG_TOKEN",
  "REPEAT_TOKEN",
  "OF_TOKEN",
  "PP_TOKEN",
  "AO_TOKEN",
  "AF_TOKEN",
  "RETURN_TOKEN",
  "FUNCTION_TOKEN",
  "HASH_TOKEN",
  "IFELSE_TOKEN",
  "TRUE_TOKEN",
  "FALSE_TOKEN",
  "AND_TOKEN",
  "OR_TOKEN",

  };

  typedef enum
{
  ERR_FICH_VID,
  ERR_CAR_INC,
  ERR_ID_LONG,
  ERR_NUM_LONG,
  ERR_END_COM,
} Erreurs;
Erreurs Sym_Erreur;
char *Erreur[] = {
    "PROGRAM_ERR", "NUM_ERR",
    "CONST_ERR", "VAR_ERR",
    "BEGIN_ERR", "END_ERR",
    "IF_ERR", "THEN_ERR",
    "WHILE_ERR", "DO_ERR",
    "READ_ERR", "WRITE_ERR",
    "PV_ERR", "PT_ERR",
    "PLUS_ERR", "MOINS_ERR",
    "MULT_ERR", "DIV_ERR",
    "VIR_ERR", "AFF_ERR",
    "INF_ERR", "INFEG_ERR",
    "SUP_ERR", "SUPEG_ERR",
    "DIFF_ERR", "PO_ERR",
    "PF_ERR", "FIN_ERR",
    "ID_ERR", "ERREUR_ERR",
    "EOF_ERR", "EG_ERR",
    "ELSE_ERR", "FOR_ERR",
    "INTO_ERR", "DOWNTO_ERR",
    "REPEAT_ERR", "UNTIL_ERR",
    "CASE_EE", "OF_ERR",
    "PP_ERR", "CONST_VAR_BEGIN_ERR",
    "VAR_BEGIN_ERR", "MOINS_PLUS_ERR",
    "MULT_DIV_ERR", "FACT_ERR",
    "INTO_DOWNTO_ERR", "SYMBOLE_EXIST_ERR",
    "SYMBOLE_NOT_DECLARED_ERR", "SYMBOLE_CONST_MODIF_ERR",
    "SYMBOLE_PROGID_MODIF_ERR",
    "AO_ERR","AF_ERR","IN_ERR","FUNCTION_ERR"};

void afficher_Token()
{
  if (Sym_Cour.cls != EOF)
  {
    if (Sym_Cour.cls != ERREUR_TOKEN)
      printf("%s \n", TokenNames[Sym_Cour.cls]);
    else
      printf("%s \n", ErreurNames[Sym_Erreur]);
  }
}

int lire_comm()
{
  if (Car_Cour == '#')
  {
    while ((fgetc(file) != '\n'))
    {
    }
    ligne++;
    Car_Cour = fgetc(file);
    return 1;
  }
  return 0;
}

int isseparateur()
{
  if (isspace(Car_Cour) || Car_Cour == '#')
  {
    col++;
    if (Car_Cour == '\n')
    {
      col = 1;
      ligne++;
    }
    if (Car_Cour == '#')
      return lire_comm();
    else
      Car_Cour = fgetc(file);
    return 1;
  }
  return 0;
}

void lire_nombre()
{
  while (isdigit(Car_Cour))
  {
    *chaine_p++ = Car_Cour;
    Car_Cour = fgetc(file);
    col++;
  }
  *chaine_p = '\0';
  strcpy(Sym_Cour.nom, chaine);

    Sym_Cour.cls = NUM_TOKEN;
}

void lire_mot()
{
  while (isdigit(Car_Cour) || isalpha(Car_Cour))
  {
    *chaine_p++ = Car_Cour;
    Car_Cour = fgetc(file);
    col++;
  }
  *chaine_p = '\0';
  strcpy(Sym_Cour.nom, chaine);
   if (!strcasecmp(chaine, "if"))
    Sym_Cour.cls = IF_TOKEN;
  else if (!strcasecmp(chaine, "else"))
    Sym_Cour.cls = ELSE_TOKEN;
  else if (!strcasecmp(chaine, "while"))
    Sym_Cour.cls = WHILE_TOKEN;
  else if (!strcasecmp(chaine, "else"))
    Sym_Cour.cls = ELSE_TOKEN;
  else if (!strcasecmp(chaine, "for"))
    Sym_Cour.cls = FOR_TOKEN;
  else if (!strcasecmp(chaine, "in"))
    Sym_Cour.cls = IN_TOKEN;
  else if (!strcasecmp(chaine, "repeat"))
    Sym_Cour.cls = REPEAT_TOKEN;
  else if (!strcasecmp(chaine, "ifelse"))
    Sym_Cour.cls = IFELSE_TOKEN;
  else if (!strcasecmp(chaine, "function"))
    Sym_Cour.cls = FUNCTION_TOKEN;
  else if (!strcasecmp(chaine, "TRUE"))
    Sym_Cour.cls = TRUE_TOKEN;
  else if (!strcasecmp(chaine, "FALSE"))
    Sym_Cour.cls = FALSE_TOKEN;
  else
    Sym_Cour.cls = ID_TOKEN;
}

void sym_suiv()
{
  chaine_p = chaine;
  int res;
  while(isblank(Car_Cour))
  {
    //printf("skip");
    Car_Cour=fgetc(file);
  }
  
  while ((res = isseparateur()))
  {
    if (res == 2)
      return;
  };

  if (isdigit(Car_Cour))
    lire_nombre();
  else
  {
    if (isalpha(Car_Cour))
      lire_mot();
    else
    {
      switch (Car_Cour)
      {
      case '(':
        Sym_Cour.cls = PO_TOKEN;
        break;
      case ')':
        Sym_Cour.cls = PF_TOKEN;
        break;
      case ';':
        Sym_Cour.cls = PV_TOKEN;
        break;
      case '{':
        Sym_Cour.cls = AO_TOKEN;
        break;
      case ':':
        Sym_Cour.cls = PP_TOKEN;
        break;
      case '}':
        Sym_Cour.cls = AF_TOKEN;
        break;
      case ',':
        Sym_Cour.cls = VIR_TOKEN;
        break;
      case '=':
        Car_Cour = fgetc(file);
        if (Car_Cour == '=')
          {
            col++;
            Sym_Cour.cls = EG_TOKEN;
          }
        else{
          Sym_Cour.cls = AFF_TOKEN;
          fseek(file, -1, SEEK_CUR);
        }
        break;
      case '+':
        Sym_Cour.cls = PLUS_TOKEN;
        break;
      case '-':
        Car_Cour = fgetc(file);
        if(Car_Cour== '>'){
        Sym_Cour.cls = AFF_TOKEN;
        }
        else
        {
          Sym_Cour.cls=MOINS_TOKEN;
        }
        break;
      case '*':
        Sym_Cour.cls = MULT_TOKEN;
        break;
      case '/':
        Sym_Cour.cls = DIV_TOKEN;
        break;
      case '.':
        Sym_Cour.cls = PT_TOKEN;
        break;
      case '<':
        Car_Cour = fgetc(file);
        if (Car_Cour == '-')
        {
          col++;
          Sym_Cour.cls = AFF_TOKEN;
        }
         else 
         if (Car_Cour == '=')
          { col++;
            Sym_Cour.cls = INFEG_TOKEN;}
        
        else
          {
            Sym_Cour.cls = INF_TOKEN;
          }
        break;
      case '>':
        Car_Cour = fgetc(file);
        if (Car_Cour == '=')
        {
          col++;
          Sym_Cour.cls = SUPEG_TOKEN;
        }
        else
          Sym_Cour.cls = SUP_TOKEN;
        break;
      case '!':
        Car_Cour = fgetc(file);
        if (Car_Cour == '=')
        {
          col++;
          Sym_Cour.cls = DIFF_TOKEN;
        }
        break;
      case '&':
        Sym_Cour.cls = AND_TOKEN;
        break;
      case '|':
        Sym_Cour.cls = OR_TOKEN;
        break;
      default:
        Sym_Cour.cls = ERREUR_TOKEN;
        Sym_Erreur = ERR_CAR_INC;
        Car_Cour = fgetc(file);
      }
      col++;
      Sym_Erreur = ERR_CAR_INC;
      if (Sym_Cour.cls != ERREUR_TOKEN && Sym_Cour.cls != INF_TOKEN && Sym_Cour.cls != SUP_TOKEN)
        Car_Cour = fgetc(file);
    }
  }
 //afficher_Token();
}

void afficher_Erreur(ERREUR_TOKENS COD_ERR)
{
  printf("%s (%d,%d) \n", Erreur[COD_ERR], ligne, col);
  printf("%s\n",Sym_Cour.nom);
  exit(EXIT_FAILURE);
}

void Test_Symbole(CODES_TOKENS cl, ERREUR_TOKENS COD_ERR)
{
  if (Sym_Cour.cls == cl)
  {
    sym_suiv();
  }
  else
    afficher_Erreur(COD_ERR);
}
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
