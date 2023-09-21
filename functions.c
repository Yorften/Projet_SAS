#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct Date {
    int j,m,a;
};
typedef struct tache {
    int id;
    char title[20];
    char desc[20];
    struct Date date;
    char status[11];
}tache;

int tach_comp = 0;
tache T[100];

int syntaxDate(tache T[],int i){
check:
    switch ((char)T[i].date.m){
    case 2: 
        if(T[i].date.j >= 29 || T[i].date.j <= 0){
            printf("Entree invalide. Veuillez saisir un jour valid (1-28).\n");
            while (getchar() != '\n');
            return 1;}else return 0;
        break;
    case 4:  case 6:  case 9:  case 11:
        if(T[i].date.j >= 31 || T[i].date.j <= 0){
            printf("Entree invalide. Veuillez saisir un jour valid (1-30).\n");
            while (getchar() != '\n');
        return 1;}else return 0;
        break;
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        if(T[i].date.j >= 32 || T[i].date.j <= 0){
            printf("Entree invalide. Veuillez saisir un jour valid (1-31).\n");
            while (getchar() != '\n');
        return 1;}else return 0;
        break;
    default:
        printf("Mois invalide. Veuillez saisir un mois valid (1-12).\n");
        while (getchar() != '\n');
        return 1;
        break;
    }
}

void addTask(){
    int i,n,p,choice2;
input:
        printf("Combien des taches vous souhaitez ajouter : ");
        if ( scanf("%d", &n) != 1) {
                    printf("Entree invalide. Veuillez saisir un entier valide.\n");
                            // Clear the input buffer
                        while (getchar() != '\n');
                        goto input;
        }
        p = n + tach_comp;
        for (i = tach_comp; i < p ; i++){
            getchar();
            printf("\nSaisir les informations du tache n%d \n", i+1);
            T[i].id=i+1;
            printf("Titre : ");
            scanf(" %[^\n]",T[i].title);
            printf("Description : ");
            scanf(" %[^\n]",T[i].desc);
            do{
                date:
                printf("Date limite (ex: 11/03/2024) : ");
                if (scanf("%d/%d/%d", &T[i].date.j, &T[i].date.m, &T[i].date.a) != 3){
                    printf("Format d\'entree invalide. Veuillez utiliser le format jj/mm/aaaa.\n");
                    while (getchar() != '\n');
                    goto date; // Exit with an error code
                }
            }while(syntaxDate(T,i));
            status:
            printf("Status du tache :\n \t1- A realiser | 2- En cours | 3- Finalisee  : ");
            if ( scanf("%d", &choice2) != 1) {
                printf("Entree invalide. Veuillez saisir un entier valide.\n");
                    // Clear the input buffer
                while (getchar() != '\n');
                goto status;
            }
            if (choice2 <= 0 || choice2 >= 4){
                printf("Choix invalide. Veuillez saisir une option valide (1-3).\n");
                goto status;
            }
            switch (choice2){
                case 1:
                    strcpy(T[i].status,"A realiser");
                    break;
                case 2:
                    strcpy(T[i].status,"En cours");
                    break;
                case 3:
                    strcpy(T[i].status,"Finalisee");
                    break;    
            }
            tach_comp++;
        }
}

void showTask(tache T[]){
    int i;
        printf("\t\t+------------------------------------------------------------------------------+\n");
        printf("\t\t| Id |        Tache         |      Description     | Date limite |    Status   |\n");
        printf("\t\t+------------------------------------------------------------------------------+\n");
    for (i = 0; i < tach_comp; i++){

        printf("\t\t| %-2d | %-20s | %-20s | %2d-%2d-%4d  | %-11s |\n",T[i].id,T[i].title,T[i].desc,T[i].date.j,T[i].date.m,T[i].date.a,T[i].status);
    }
        printf("\t\t+------------------------------------------------------------------------------+\n");
}

void triAlpha(tache T[]){
    int i,j;
    tache temp;
    tache F[100];
    for (i = 0; i < 100; i++){
        F[i]=T[i];
    }
    
    for(i=0;i<tach_comp;i++){
        for(j=i+1;j<tach_comp;j++){
            if(strcmp(F[i].title,F[j].title)>0){
                temp=F[i];
                F[i]=F[j];
                F[j]= temp;
            }
        }
    }   
printf("\t\tLes taches triees par titre: \n");
showTask(F);
}

void triDate(tache T[]){
    int i,j,temp,days;;
    tache temp2;
    tache R[100];
    int delaiTable[100];
    for (i = 0; i < 100; i++){
        R[i]=T[i];
    }
    time_t seconds=time(NULL);
    struct tm* current_time=localtime(&seconds); 
    int currentYear = (current_time->tm_year + 1900);
    int currentMonth =(current_time->tm_mon + 1);
    int currentDay =current_time->tm_mday;

    for (i = 0; i < tach_comp; i++){
        days = R[i].date.a*365+R[i].date.m*30+R[i].date.j;
        delaiTable[i]=days-(currentYear*365+currentMonth*30+currentDay); 
    }
    for(i=0;i<tach_comp;i++){
        for(j=i+1;j<tach_comp;j++){
            if(delaiTable[i]>delaiTable[j]){
                temp=delaiTable[i];
                delaiTable[i]=delaiTable[j];
                delaiTable[j]= temp;

                temp2=R[i];
                R[i]=R[j];
                R[j]=temp2;
            }
        }
    }
printf("\t\tLes taches triees par deadline : \n");
showTask(R);
}

void tasksDeadline(){
    int i;

    int c=0;
    time_t seconds=time(NULL);
    struct tm* current_time=localtime(&seconds); 
    int currentYear = (current_time->tm_year + 1900);
    int currentMonth =(current_time->tm_mon + 1);
    int currentDay =current_time->tm_mday;

    for (i = 0; i < tach_comp; i++){
        if(T[i].date.a != currentYear){
            c++;
            continue;
        }else if (T[i].date.m != currentMonth){
            c++;
            continue;
        }else if(T[i].date.j - currentDay <= 3 && T[i].date.j - currentDay>0){
            printf("\t\t+-----------------------------------------+\n");
            printf("\t\t|Id : %-34d  |\n",T[i].id);
            printf("\t\t|Tache : %-31s  |\n", T[i].title);
            printf("\t\t|Description : %-26s |\n", T[i].desc);
            printf("\t\t|Deadline : %-02d/%02d/%-23d |\n", T[i].date.j, T[i].date.m, T[i].date.a);
            printf("\t\t|Jours avant deadline: %-3ld                |\n", T[i].date.j - currentDay);
            printf("\t\t+-----------------------------------------+\n");
        }else c++;
    }
    if(c==tach_comp) printf("\t\tIl n\'y a pas des taches qu'on 3 jours ou mins do delai.\n");
}

void tasksNumber(tache T[]){
    int i,num;
    for (i = 0; i < tach_comp; i++){
        num++;
    }
    printf("Le nombre total des taches : %d\n", num);
}

void completedTasks(tache T[]){
    int complete = 0;
    int incomplete = 0;
    int i;
    for ( i = 0; i < tach_comp; i++){
        if(strcmp(T[i].status,"A realiser")==0 || strcmp(T[i].status,"En cours")==0){
            incomplete++;
        }else complete++;
    }
    printf("Le nombre des taches complets : %d\n",complete);
    printf("Le nombre des taches incomplets : %d\n",incomplete);

}

void showTasksDeadline(tache T[]){
    int i,delai,days;
    time_t seconds=time(NULL);
    struct tm *current_time=localtime(&seconds); 
    int currentYear = (current_time->tm_year + 1900);
    int currentMonth =(current_time->tm_mon + 1);
    int currentDay =current_time->tm_mday;
    printf("\t\t+----------------------------------------------------------------------+\n");
    for (i = 0; i < tach_comp; i++)
    {
        days = T[i].date.a*365+T[i].date.m*30+T[i].date.j;
        delai = days-(currentYear*365+currentMonth*30+currentDay); 
        if (delai > 0){
        printf("\t\t| Id : %2d | Titre : %-20s | Delai :%3d jour(s)         |\n",T[i].id,T[i].title,delai);
        }else if(delai < 0) {
            printf("\t\t| Id : %2d | Titre : %-20s | Delai : il y a %3d jour(s)  |\n",T[i].id,T[i].title,abs(delai));
        }else printf("\t\t| Id : %2d | Titre : %-20s | Delai : Aujourd\'hui         |\n",T[i].id,T[i].title);

        printf("\t\t+----------------------------------------------------------------------+\n");
    }
    
}

void modDesc(tache T[]){
    int id;
    int c=0;
    printf("\t\tDonnez l'id de la tache :");
    scanf("%d",&id);

    for (int i = 0; i < tach_comp; i++){
        if (T[i].id==id){
            c++;
            printf("\t\tEntrez la nouvelle description :");
            scanf(" %[^\n]",T[i].desc);
        }
    }
    if(c==0) printf("\t\tIl n\'y a pas de tache avec l\'Id %d\n",id);
}

void modStatus(tache T[]){
    int id,choice2;
    int c=0;
    printf("\t\tDonnez l'id de la tache :");
    scanf("%d",&id);

    for (int i = 0; i < tach_comp; i++){
        if (T[i].id==id){
            c++;
            status:
            printf("\t\t\t\tStatus du tache :\n \t1- A realiser | 2- En cours | 3- Finalisee  : ");
            if ( scanf("%d", &choice2) != 1) {
                printf("\t\tEntree invalide. Veuillez saisir un entier valide.\n");
                    // Clear the input buffer
                while (getchar() != '\n');
                goto status;
            }
            if (choice2 <= 0 || choice2 >= 4){
                printf("\t\tChoix invalide. Veuillez saisir une option valide (1-3).\n");
                goto status;
            }
            switch (choice2){
                case 1:
                    strcpy(T[i].status,"A realiser");
                    break;
                case 2:
                    strcpy(T[i].status,"En cours");
                    break;
                case 3:
                    strcpy(T[i].status,"Finalisee");
                    break;    
            }
        }
    }
    if(c==0) printf("\t\tIl n\'y a pas de tache avec l\'Id %d\n",id);
}

void modDeadline(tache T[]){
    int id;
    int c=0;
    printf("\t\tDonnez l'id de la tache :");
    scanf("%d",&id);

    for (int i = 0; i < tach_comp; i++){
        if (T[i].id==id){
            c++;
            do{
                date:
                printf("\t\tDate limite (ex: 11/03/2024) : ");
                if (scanf("%d/%d/%d", &T[i].date.j, &T[i].date.m, &T[i].date.a) != 3){
                    printf("\t\tFormat d\'entree invalide. Veuillez utiliser le format jj/mm/aaaa.\n");
                    while (getchar() != '\n');
                    goto date; // Exit with an error code
                }
            }while(syntaxDate(T,i));
        }
    }
    
}

int deleteTask(tache T[]){
    int id;
    int c=0;
    int choix;
    printf("\t\tDonnez l'id de la tache :");
    scanf("%d",&id);
confirm:
    printf("\t\tConfirmer (1- Oui | 0- Non) : ");
    if ( scanf("%d", &choix) != 1) {
        printf("Entree invalide. Veuillez saisir un entier valide (1- Oui | 0- Non).\n");
            // Clear the input buffer
        while (getchar() != '\n');
        goto confirm;
    }
    if (choix < 0 || choix >= 3){
        printf("Choix invalide. Veuillez saisir une option valide (1-7).\n");
        goto confirm;
    }
    switch (choix){
    case 0:
        return 0;
        break;
    case 1:
        for (int i = 0; i < tach_comp; i++){
            if(T[i].id==id){
                c++;
                for (int j = i; i < tach_comp - 1; i++){
                    T[i]=T[j+1];
                    i++;
                }
                tach_comp--;
            }
        }
        if(c==0) printf("\t\tIl n\'y a pas de tache avec l\'Id %d\n",id);
        break;
    } 
}

void findById(tache T[]){
    int id;
    int c=0;
    time_t seconds=time(NULL);
    struct tm* current_time=localtime(&seconds); 
    int currentDay =current_time->tm_mday;
    printf("\t\tDonnez l'id de la tache :");
    scanf("%d",&id);

    for (int i = 0; i < tach_comp; i++){
            if(T[i].id==id){
                c++;
                printf("\t\t+-----------------------------------------+\n");
                printf("\t\t|Id : %-34d |\n",T[i].id);
                printf("\t\t|Tache : %-31s  |\n", T[i].title);
                printf("\t\t|Description : %-26s |\n", T[i].desc);
                printf("\t\t|Deadline : %-02d/%02d/%-23d |\n", T[i].date.j, T[i].date.m, T[i].date.a);
                printf("\t\t|Jours avant deadline: %-3ld jour(s)        |\n", abs(T[i].date.j - currentDay));
                printf("\t\t+-----------------------------------------+\n");
            }
    }
    if(c==0) printf("\t\tIl n\'y a pas de tache avec l\'Id %d\n",id);
}

void findByTitle(tache T[]){
    char toFind[20];
    int c=0;
    time_t seconds=time(NULL);
    struct tm* current_time=localtime(&seconds); 
    int currentDay =current_time->tm_mday;

    printf("\t\tDonnez le titre de la tache :");
    scanf(" %[^\n]",toFind);
    for (int i = 0; i < tach_comp; i++){
        if(strcmp(T[i].title,toFind)==0){
            c++;
            printf("\t\t+-----------------------------------------+\n");
            printf("\t\t|Id : %-34d  |\n",T[i].id);
            printf("\t\t|Tache : %-31s  |\n", T[i].title);
            printf("\t\t|Description : %-26s |\n", T[i].desc);
            printf("\t\t|Deadline : %-02d/%02d/%-23d |\n", T[i].date.j, T[i].date.m, T[i].date.a);
            printf("\t\t|Jours avant deadline: %-3ld jour(s)        |\n", abs(T[i].date.j - currentDay));
            printf("\t\t+-----------------------------------------+\n");
        }
    }
    if(c==0) printf("\t\tIl n\'y a pas de tache avec le titre %s\n",toFind);
}

int taskMenu(){
int choice;
do{
            printf("\t\t+----------------------------------------+\n");
            printf("\t\t|            MENU DES TACHES             |\n");
            printf("\t\t+----------------------------------------+\n");
            printf("\t\t|                                        |\n");
            printf("\t\t|     1- Afficher les taches             |\n");
            printf("\t\t|     2- Tri alphabetique                |\n");
            printf("\t\t|     3- Tri par deadline                |\n");
            printf("\t\t|     4- Taches expirant bientot         |\n");
            printf("\t\t|     5- Menu precedent                  |\n");
            printf("\t\t|                                        |\n");
            printf("\t\t+----------------------------------------+\n");

saisir:
                        printf("\n\tChoix :");
                        if ( scanf("%d", &choice) != 1) 
                        {
                            printf("Entree invalide. Veuillez saisir un entier valide.\n");
                                 // Clear the input buffer
                             while (getchar() != '\n');
                             goto saisir;
                         }
                        if (choice <= 0 || choice >= 6)
                        {
                            printf("Choix invalide. Veuillez saisir une option valide (1-5).\n");
                            goto saisir;
                        }
                        switch (choice)
                        {
                        case 1:
                            showTask(T);
                            system("pause");
                            break;
                        case 2:    
                            triAlpha(T);
                            system("pause");
                            break;
                        case 3:
                            triDate(T);
                            system("pause");
                            break;
                        case 4:
                            tasksDeadline();
                            system("pause");
                            break;
                        case 5:
                            return 0;
                            break;
                        }
}while (choice <= 6);
}

int managementMenu(){
    int choice;
    do{
            printf("\t\t+----------------------------------------+\n");
            printf("\t\t|           GESTION DES TACHES           |\n");
            printf("\t\t+----------------------------------------+\n");
            printf("\t\t|                                        |\n");
            printf("\t\t|     1- Modifier la description         |\n");
            printf("\t\t|     2- Modifier le status              |\n");
            printf("\t\t|     3- Modifier le deadline            |\n");
            printf("\t\t|     4- Supprimer une tache             |\n");
            printf("\t\t|     5- Rechercher par Id               |\n");
            printf("\t\t|     6- Rechercher par titre            |\n");
            printf("\t\t|     7- Menu precedent                  |\n");
            printf("\t\t|                                        |\n");
            printf("\t\t+----------------------------------------+\n");

                saisir:
                            printf("\n\tChoix :");
                            if ( scanf("%d", &choice) != 1) {
                                printf("Entree invalide. Veuillez saisir un entier valide.\n");
                                    // Clear the input buffer
                                while (getchar() != '\n');
                                goto saisir;
                            }
                            if (choice <= 0 || choice >= 8){
                                printf("Choix invalide. Veuillez saisir une option valide (1-7).\n");
                                goto saisir;
                            }
                            switch (choice){
                            case 1:
                                modDesc(T);
                                system("pause");
                                break;
                            case 2:    
                                modStatus(T);
                                system("pause");
                                break;
                            case 3:
                                modDeadline(T);
                                system("pause");
                                break;
                            case 4:
                                deleteTask(T);
                                system("pause");
                                break;
                            case 5:
                                findById(T);
                                system("pause");
                                break;
                            case 6:
                                findByTitle(T);
                                system("pause");
                                break;
                            case 7:
                                return 0;
                                break;
                            }
    }while(choice<= 8);
}

int statsMenu(){
int choice;
do{
            printf("\t\t+----------------------------------------+\n");
            printf("\t\t|              Statistiques              |\n");
            printf("\t\t+----------------------------------------+\n");
            printf("\t\t|                                        |\n");
            printf("\t\t|     1- Le nombre total des taches      |\n");
            printf("\t\t|     2- Nombre des taches(compl/incompl)|\n");
            printf("\t\t|     3- Le delai des taches             |\n");
            printf("\t\t|     4- Menu precedent                  |\n");
            printf("\t\t|                                        |\n");
            printf("\t\t+----------------------------------------+\n");

saisir:
                        printf("\n\tChoix :");
                        if ( scanf("%d", &choice) != 1) 
                        {
                            printf("Entree invalide. Veuillez saisir un entier valide.\n");
                                 // Clear the input buffer
                             while (getchar() != '\n');
                             goto saisir;
                         }
                        if (choice <= 0 || choice >= 5)
                        {
                            printf("Choix invalide. Veuillez saisir une option valide (1-4).\n");
                            goto saisir;
                        }
                        switch (choice)
                        {
                        case 1:
                            tasksNumber(T);
                            system("pause");
                            break;
                        case 2:    
                            completedTasks(T);
                            system("pause");
                            break;
                        case 3:
                            showTasksDeadline(T);
                            system("pause");
                            break;
                        case 4:
                            return 0;
                            break;
                        }
}while (choice <= 5);
}
