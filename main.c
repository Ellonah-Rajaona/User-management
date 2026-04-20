#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    int choix;
    char ligne[500];
    FILE *f, *t;
    char nom[50], prenom[50], add[50], tel[10];
    char sexe;
    char rech[50];

    do {
        // Affichage du menu mis à jour avec le 5ème choix
        printf("\n--- GESTION UTILISATEURS ---\n");
        printf("1: Ajouter\n2: Afficher\n3: Rechercher\n4: Supprimer\n5: Modifier\n0: Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        if (choix == 1) { // AJOUT PAR L'UTILISATEUR
            // Mode "a" (append) pour ajouter sans effacer l'existant
            f = fopen("file_m.csv", "a");
            if (f == NULL) return 1;

            printf("Nom : ");
            scanf("%s", nom);
            printf("Prenom : ");
            scanf("%s", prenom);
            printf("Tel : ");
            scanf("%s", tel);
            printf("Addresse : ");
            scanf("%s", add);
            printf("Sexe (M/F) : ");
            scanf(" %c", &sexe);


            fprintf(f, "%s;%s;%s;%s;%c\n", nom, prenom, tel, add, sexe);
            fclose(f);
            printf("Ajout reussi !\n");

        } else if (choix == 2) { // AFFICHAGE DU CONTENU DU FICHIER
            f = fopen("file_m.csv", "r");
            if (f == NULL)
                { printf("Aucune donnee.\n"); }
            else {
                while (fgets(ligne, sizeof(ligne), f) != NULL)
                 { printf("%s", ligne); }
                fclose(f);
            }

        } else if (choix == 3) { //RECHERCHER DANS LE CONTENU DU FICHIER
            f = fopen("file_m.csv", "r");
            printf("Rechercher :  ");
            scanf("%s", rech);
            while (fgets(ligne, sizeof(ligne), f) != NULL) {
                if (strstr(ligne, rech) != NULL)
                    { printf("Resultat de recherche: %s", ligne); }
            }
            fclose(f);

        } else if (choix == 4 || choix == 5) { //OU MODIFICATION DE CONTENU  (choix = 4) ou SUPPRESSION D'UNE LIGNE (choix = 5)
            f = fopen("file_m.csv", "r");
            t = fopen("tempo.csv", "w"); // Fichier temporaire pour stocker les modifications

            printf("Nom a chercher : ");
             scanf("%s", rech);
            int trouve = 0;

            while (fgets(ligne, sizeof(ligne), f) != NULL) {
                if (strstr(ligne, rech) != NULL) {//on cherche d'abord la ligne à mettre à jour(à modifier) ou à la supprimer
                    trouve = 1;//si trouvé (trouve==1), on procède à la modification ou à la suppression
                    if (choix == 5) { // MODIFICATION
                        printf("processus de modification\n");
                        printf("Nom : ");
                        scanf("%s", nom);
                        printf("Prenom : ");
                         scanf("%s", prenom);
                        printf("Tel : ");
                        scanf("%s", tel);
                        printf("Add : ");
                        scanf("%s", add);
                        printf("Sexe : ");
                        scanf(" %c", &sexe);
                        // On écrit la modification dans le fichier temporaire
                        fprintf(t, "%s;%s;%s;%s;%c\n", nom, prenom, tel, add, sexe);
                    }


                 else if(choix==4){//notre approche c'est de trouver la ligne à supprimer mais ne fait aucune modification dans le fichier temporaire
                    fputs(ligne, t);
                }
              }
            }
            fclose(f); fclose(t);
            remove("file_m.csv"); // Supprime l'original
            rename("tempo.csv", "file_m.csv"); // Renomme le temporaire
            if (trouve==1){
                    printf( "Operation reussie ...\n");
            }
            else{
                printf( "echec \n");
            }

        }

    } while (choix != 0);

    return 0;
}


