#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "functions.c"


int main(){

    int choice;
    do{
                printf("\n\t\t+----------------------------------------+\n");
                printf("\t\t|            MENU PRINCIPALE             |\n");
                printf("\t\t+----------------------------------------+\n");
                printf("\t\t|                                        |\n");
                printf("\t\t|     1- Ajouter une tache(s)            |\n");
                printf("\t\t|     2- Menu des taches                 |\n");            
                printf("\t\t|     3- Gestion des taches              |\n");
                printf("\t\t|     4- Statistiques                    |\n");
                printf("\t\t|     5- Quittez                         |\n");
                printf("\t\t|                                        |\n");
                printf("\t\t+----------------------------------------+\n");

                        saisir:
                            printf("\n\tChoix :");
                            
                            if ( scanf("%d", &choice) != 1) {
                                printf("Entree invalide. Veuillez saisir un entier valide.\n\n");
                                    // Clear the input buffer
                                while (getchar() != '\n');
                                goto saisir;
                            }

                            if (choice <= 0 || choice >= 6){
                                printf("Choix invalide. Veuillez saisir une option valide (1-5).\n\n");
                                goto saisir;
                            }
                            switch (choice)
                            {
                            case 1:
                                addTask();
                                system("pause");
                                break;
                            case 2:    
                                taskMenu();
                                break;
                            case 3:
                                managementMenu();
                                break;
                            case 4:
                                statsMenu();
                                break;
                            case 5:
                                exit(0);
                                break;
                            
                            }
    }while (choice <=6);
    return 0;
}

