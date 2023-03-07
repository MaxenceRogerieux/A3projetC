#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "visualisationC.h"




void visualisationC(float puissance_f) {
    if(access( ".verrouData", F_OK ) != -1){
        // Fichier verrou existe
    }
    else{
        // Fichier verrou n'existe pas
        // crée le fichier verrou
        FILE* fichier_verrou = fopen(".verrouData", "w+");
        fclose(fichier_verrou);
        // écrit le témoin de chauffe dans le fichier data.txt
        FILE* fluxDataC;
        fluxDataC = fopen("data.txt", "r+"); // r+ : les données précédentes ne sont pas effacées si le fichier existe
        if(fluxDataC == NULL){
            printf("Error in opening file");
            //return 1;
        }
        else{
            // extrait du fichier les températures ext et int
            float exterieure;
            float interieure;
            fscanf(fluxDataC, "%f\n%f", exterieure, interieure);
            fclose(fluxDataC);
            fluxDataC = fopen("data.txt", "w+"); // w+ : les données précédentes sont effacées si le fichier existe
            // écrit dans le fichier
            if(puissance_f == 0){
                fprintf(fluxDataC, "%f\n%f\n%s", exterieure, interieure, "false");
            }
            else{
                fprintf(fluxDataC, "%f\n%f\n%s", exterieure, interieure, "true");
            }
            fclose(fluxDataC);


            fclose(flux);
            // supprime fichier verrou
        }
        remove(".verrouData");// supprime fichier verrou
        remove(".verrouData");
    }
}