#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "visualisationC.h"


// Ecriture du témoin de chauffe dans le fichier data.txt
void visualisationC(float puissance_f) {
    if(access( ".verrouData", F_OK ) != -1){
        // Fichier verrou existe
    }
    else{
        // Fichier verrou n'existe pas
        // Création du fichier verrou
        FILE* fichier_verrou = fopen(".verrouData", "w+");
        fclose(fichier_verrou);
        // 1- Lecture du fichier et extraction des températures intérieures et extérieures
        FILE* fluxDataC=NULL;
        fluxDataC = fopen("data.txt", "r+"); // r+ : les données précédentes ne sont pas effacées si le fichier existe
        if(fluxDataC == NULL){
            printf("Error in opening file");
            fclose(fluxDataC);
        }
        else{
            // Extraction des températures ext et int
            char exterieure[8];
            char interieure[8];
            char ligne[8];
            int ligne_num = 1;
            while(fgets(ligne, 8, fluxDataC) != NULL) {
                if (ligne_num == 1) {
                    strcpy(exterieure, ligne);
                }
                else{
                    if(ligne_num == 2){
                        strcpy(interieure, ligne);
                    }
                }
                ligne_num++;
            }
            fclose(fluxDataC);
            // 2- Ecriture des informations (témoin de chauffe, températures) dans le fichier
            fluxDataC = fopen("data.txt", "w+"); // w+ : les données précédentes sont effacées si le fichier existe
            float exte = atof(exterieure); // str to float
            float inte = atof(interieure); // str to float
            if(puissance_f == 0){
                fprintf(fluxDataC, "%.2f\n%.2f\n%s", exte, inte, "false");
            }
            else{
                fprintf(fluxDataC, "%.2f\n%.2f\n%s", exte, inte, "true");
            }
            fclose(fluxDataC);
        }
        remove(".verrouData"); // Suppression du fichier verrou
    }
}