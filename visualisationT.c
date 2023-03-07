#include "visualisationT.h"

#include <unistd.h>
#include <stdio.h>

void visualisationT(temp_t myTemp)
{
    if(access( ".verrouData", F_OK ) != -1){
        // Fichier verrou existe
    }
    else{
        // Fichier verrou n'existe pas
        // crée le fichier verrou
        FILE* fichier_verrou = fopen(".verrouData", "w+");
        fclose(fichier_verrou);
        // écrit les températures intérieures et extérieures dans le fichier data.txt
        FILE* fluxDataT=NULL;
        fluxDataT = fopen("data.txt", "r+"); // r+ : les données précédentes ne sont pas effacées si le fichier existe
        if(fluxDataT == NULL){
            printf("Error in opening file");
            return 1;
        }
        else{
            // extrait du fichier le témoin de chauffe
            char temoin_de_chauffe[8];
            char ligne[8];
            char temoin_de_chauffe[8];
            int ligne_num = 1;
            while(fgets(ligne, 8, fluxDataT) != NULL) {
                if (ligne_num == 3) {
                    strcpy(exterieure, ligne);
                }
                ligne_num++;
            }
            fclose(fluxDataT);
            fluxDataT = fopen("data.txt", "w+"); // w+ : les données précédentes sont effacées si le fichier existe
            // écrit dans le fichier
            float exterieure = myTemp.exterieure;
            float interieure = myTemp.interieure;
            fprintf(fluxDataT, "%f\n%f\n%s", exterieure, interieure, temoin_de_chauffe);
            fclose(fluxDataT);
        }
        remove(".verrouData");// supprime fichier verrou
    }
}