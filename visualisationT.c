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
        FILE* fluxDataT;
        fluxDataT = fopen("data.txt", "r+"); // r+ : les données précédentes ne sont pas effacées si le fichier existe
        if(fluxDataT == NULL){
            printf("Error in opening file");
            return 1;
        }
        else{
            // extrait du fichier le témoin de chauffe
            char temoin_de_chauffe[8];
            fscanf(flux, "\n\n%s", temoin_de_chauffe);
            fclose(flux);
            flux = fopen("data.txt", "w+"); // w+ : les données précédentes sont effacées si le fichier existe
            char* temoin_de_chauffe;
            fscanf(fluxDataT, "\n\n%s", temoin_de_chauffe);
            fclose(fluxDataT);
            fluxDataT = fopen("data.txt", "w+"); // w+ : les données précédentes sont effacées si le fichier existe
            // écrit dans le fichier
            float exterieure = myTemp.exterieure;
            float interieure = myTemp.interieure;
            fprintf(flux, "%f\n%f\n%s", exterieure, interieure, temoin_de_chauffe);
            fclose(flux);
            // supprime fichier verrou
        }
        remove(".verrouData");
    }
}