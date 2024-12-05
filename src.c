#include "fonctions.h"

int main()
{
    // main
    int choix = 0;
    char str[25], entier[12], reel[12];
    do
    {
        printf("\n------------------menu-----------------------\n\n");
        printf("1. convertir entier de 0 a 999999999999 a letrre ;\n");
        printf("2. convertir reel de 0 a 999999999999 a letrre ;\n");
        printf("3. exit ;\n");
        printf("\nleur choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            printf("Enter un nombre entier :  ");
            scanf("%s", str);
            getchar();
            printf("%s => ", str);
            convertir_nbre_1(str);
            break;
        case 2:
            printf("Enter un nombre reel ");
            scanf("%s", str);
            getchar();
            printf("%s => ", str);
            convertir_nbre_2(str);
            break;
        case 3:
            break;
        default:
            printf("quelque chose est mal ressayer");
            break;
        }
    } while (choix != 3);
    return 0;
}
