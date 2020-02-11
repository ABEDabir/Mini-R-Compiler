#include "analyseur_lexical.h"
#include "errors.h"



void afficher_Token()
{
    if (Sym_Cour.cls != EOF)
    {
        if (Sym_Cour.cls != ERREUR_TOKEN)
            printf("%s \n", TokenNames[Sym_Cour.cls]);
        else
            afficher_Erreur(ERREUR_TOKEN);
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
    afficher_Token();
}

