#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "constants.h"

// Vérifie si une chaîne représente un entier positif valide
int estEntier(char *str)
{
    int len_str = strlen(str);
    for (int i = 0; i < len_str; i++)
    {
        // Si un caractère n'est pas numérique, retourner 0 (faux)
        if (!isdigit(str[i]))
        {
            return 0;
        }
    }
    return 1; // Tous les caractères sont numériques
}

// Vérifie si une chaîne représente un nombre négatif valide
int estNegative(char *str)
{
    int len_str = strlen(str), count_moins = 0, index_moins;

    for (int i = 0; i < len_str; i++)
    {
        // Compte le nombre de signes '-' et enregistre sa position
        if (str[i] == '-')
        {
            count_moins++;
            index_moins = i;
        }
    }

    // Retourne 1 si exactement un '-' est en première position et la chaîne a au moins un chiffre
    if (count_moins != 1 || index_moins != 0 || len_str < 2)
    {
        return 0;
    }
    return 1; // Nombre négatif valide
}

// Extrait une sous-chaîne d'une chaîne donnée entre deux indices inclusifs
char *extraireSousChaine(char *str, int start, int end)
{
    // Vérifie la validité des paramètres
    if (!str || start < 0 || end < start || end >= strlen(str))
    {
        return NULL;
    }

    int i, size = (end - start + 1);
    char *output = (char *)malloc((size + 1) * sizeof(char)); // Alloue de la mémoire pour la sous-chaîne

    for (i = 0; i < size; i++)
    {
        output[i] = str[start + i]; // Copie les caractères dans la nouvelle chaîne
    }
    output[i] = '\0'; // Ajoute le caractère de fin de chaîne
    return output;
}

// Complète une chaîne au début avec un caractère donné pour atteindre une longueur spécifiée
char *completerDebut(char *str, char c, int len)
{
    if (!str)
    {
        return NULL;
    }

    int str_len = strlen(str);

    // Si la longueur souhaitée est inférieure ou égale à la chaîne d'entrée, renvoyer une copie de celle-ci
    if (len <= str_len)
    {
        char *output = (char *)malloc((str_len + 1) * sizeof(char));
        if (!output)
        {
            return NULL;
        }
        strcpy(output, str);
        return output;
    }

    // Alloue de la mémoire pour la nouvelle chaîne
    char *output = (char *)malloc((len + 1) * sizeof(char));
    int nb_remplissage = len - str_len;

    // Ajoute les caractères de remplissage au début
    for (int i = 0; i < nb_remplissage; i++)
    {
        output[i] = c;
    }

    // Ajoute les caractères de la chaîne d'entrée
    for (int i = 0; i < str_len; i++)
    {
        output[nb_remplissage + i] = str[i];
    }
    output[len] = '\0'; // Ajoute le caractère de fin de chaîne
    return output;
}

// Modifie un entier pour qu'il soit divisible par 3
int rendreDivisiblePar3(int n)
{
    if (n % 3 == 0)
    {
        return n; // L'entier est déjà divisible par 3
    }
    return n + (3 - n % 3); // Ajoute le complément pour atteindre un multiple de 3
}

int FILE__getindexStr(int index)
{
    FILE *p = fopen("NBRS.txt", "r");
    for (int i = 1; i < index; i++)
    {
        while (fgetc(p) != '\n')
        {
            fseek(p, 1, SEEK_CUR);
        }
    }
    int pos = ftell(p);
    fclose(p);
    return pos;
}

// Convertit un entier en texte en utilisant des tableaux TableauLettre et T ;
void convertir_nbre_1(char *str, int option)
{
    if (strlen(str) > 12)
    {
        printf("le nombre est tres long ");
        return;
    }

    if (!estEntier(str))
    {
        printf("le string n'est pas un entier ");
        return;
    }

    int len_str = rendreDivisiblePar3(strlen(str));    // Ajuste la longueur pour être divisible par 3
    int len_str_partie = (len_str) / 3;                // Nombre de groupes de trois chiffres
    char *strtemp = completerDebut(str, '0', len_str); // Complète avec des zéros si nécessaire

    if (atoi(strtemp) == 0)
    {
        printf("%s ", TableauLettre[0]); // Traite le cas du zéro
        return;
    }

    // Parcourt les groupes de trois chiffres
    for (int i = 0; i < len_str; i += 3, len_str_partie--)
    {
        int index_str = atoi(extraireSousChaine(strtemp, i, i + 2));
        if (index_str == 0)
        {
            continue; // Ignore les groupes contenant uniquement des zéros
        }
        if (!option)
        {
            printf("%s %s ", TableauLettre[index_str], TableauUnite[len_str_partie]); // Affiche la conversion
        }
        else
        {
            FILE *p = fopen("NBRS.txt", "r");
            char str[100];
            fseek(p, FILE__getindexStr(index_str), SEEK_SET);
            int i = 0;
            while (fgetc(p) != '\n')
            {
                i++;
            }
            fseek(p, FILE__getindexStr(index_str), SEEK_SET);
            fgets(str, i + 1, p);
            printf("%s %s ", str, TableauUnite[len_str_partie]); // Affiche la conversion
        }
    }
}

// envoi le nombre de zero dans le string
int estZero(char *str)
{
    int len_str = strlen(str);
    for (int i = 0; i < len_str; i++)
    {
        if (str[i] != '0') // Si un caractère n'est pas '0', retourne faux
        {
            return 0;
        }
    }
    return 1; // Tous les caractères sont des zéros
}

// ajouter des zero au debut
void ZeroDebut(char *str)
{
    int len_str = strlen(str), count_zero = 0;
    for (int i = 0; i < len_str && str[i] == '0'; i++)
    {
        printf("zero ");
    }
}

// elimene le zero apres le virgule
char *elimineZeroAuFin(char *str)
{
    if(str == NULL)
    {
        return NULL;
    }
    int len_str = strlen(str);
    int i;
    for (i = len_str - 1; i >= 0 && str[i] == '0'; i--)
    {
    }
    return extraireSousChaine(str, 0, i);
}

// Vérifie si une chaîne représente un nombre réel et sépare les parties entière et décimale
int estReel(char *str, char entier[], char reel[])
{
    int len_str = strlen(str), count_vircule = 0;
    int index_vircule = len_str;

    // Compte les occurrences de '.' et enregistre sa position
    for (int i = 0; i < len_str; i++)
    {
        if (str[i] == '.')
        {
            count_vircule++;
            index_vircule = i;
        }
    }

    if (count_vircule > 1)
    {
        return 0; // Trop de points décimaux, invalide
    }

    // Extrait les parties entière et décimale
    char *str_entier = extraireSousChaine(str, 0, index_vircule -1);
    char *str_float = elimineZeroAuFin(extraireSousChaine(str, index_vircule + 1, len_str - 1));

    // Gère les cas où une des parties est vide
    if (str_entier == NULL && str_float == NULL)
    {
        return 0;
    }
    if (str_entier == NULL)
    {
        strcpy(reel, str_float);
        strcpy(entier, "");
        return 1;
    }
    
    if (str_float == NULL)
    {
        strcpy(entier, str_entier);
        strcpy(reel, "");
        return 1;
    }

    // Vérifie que les deux parties sont des entiers
    if (estEntier(str_entier) && estEntier(str_float))
    {
        strcpy(entier, str_entier);
        strcpy(reel, str_float);
        return 1;
    }
    return 0; // Invalide si l'une des parties n'est pas un entier
}

// Convertit un nombre réel ou négatif en texte
void convertir_nbre_2(char *str, int option)
{
    char entier[12], reel[12];
    int estNegati = 0;

    // Vérifie si le nombre est négatif
    if (estNegative(str))
    {
        ++str; // Ignore le signe '-'
        estNegati++;
        
    }

    // Vérifie si la chaîne est un nombre réel valide
    if (!estReel(str, entier, reel))
    {
        printf("le string n'est pas un nombre ;");
        return;
    }


    // Vérifie la longueur des parties entière et décimale
    if (strlen(entier) > 12 || strlen(reel) > 12)
    {
        printf("le nombre est tres long ;");
        return;
    }

    // Gestion des cas négatifs
    if (estNegati)
    {
        if (!(estZero(entier) && estZero(reel)))
        {
            printf("moins ");
        }
    }

    // Cas : pas de partie décimale
    if (!strcmp("", reel))
    {
        convertir_nbre_1(entier, option);
        return;
    }

    // Cas : pas de partie entière
    if (!strcmp("", entier))
    {
        printf("zero ");
        if (!estZero(reel))
        {
            printf("virgule ");
            ZeroDebut(reel);
            convertir_nbre_1(reel, option);
        }
        return;
    }

    // Cas : zéro entier et décimal
    if (estZero(entier) && estZero(reel))
    {
        printf("zero");
        return;
    }

    // Conversion de la partie entière
    convertir_nbre_1(entier, option);
    printf("virgule ");
    ZeroDebut(reel);
    // Conversion de la partie décimale

    convertir_nbre_1(reel, option);
}
