#include "visualisationT.h"

#include <unistd.h>
#include <stdio.h>

// Ecriture des températures intérieures et extérieures dans le fichier data.txt
void visualisationT(temp_t myTemp)
{
    if(access( ".verrouData", F_OK ) != -1){
        // Fichier verrou existe
    }
    else{
            // Fichier verrou n'existe pas
            // Création du fichier verrou
            FILE* fichier_verrou = fopen(".verrouData", "w+");
            fclose(fichier_verrou);
            // 1- Lecture du fichier et extraction du témoin de chauffe
            FILE* fluxDataT=NULL;
            fluxDataT = fopen("data.txt", "r+"); // r+ : les données précédentes ne sont pas effacées si le fichier existe
            if(fluxDataT == NULL){
                printf("Error in opening file");
                fclose(fluxDataT);
            }
            else{
                // Extraction du témoin de chauffe
                char temoin_de_chauffe[8];
                char ligne[8];
                int ligne_num = 1;
                while(fgets(ligne, 8, fluxDataT) != NULL) {
                    if (ligne_num == 3) {
                        strcpy(temoin_de_chauffe, ligne);
                    }
                    ligne_num++;
                }
                fclose(fluxDataT);
                // 2- Ecriture des informations (témoin de chauffe, températures) dans le fichier
                fluxDataT = fopen("data.txt", "w+"); // w+ : les données précédentes sont effacées si le fichier existe
                float exterieure = myTemp.exterieure;
                float interieure = myTemp.interieure;
                fprintf(fluxDataT, "%.2f\n%.2f\n%s", exterieure, interieure, temoin_de_chauffe);
                fclose(fluxDataT);
        }
        remove(".verrouData");// Suppression du fichier verrou
    }
}