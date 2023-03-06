#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "visualisationC.h"


   void visualisationC(float puissance_f) {
       if (access(".verrouData", F_OK) != 1) {
// Fichier existe
           //return puissance_f; //si pas de fichier verrou, la valeur précedente de la puissance est return
       } else {
// Fichier n'existe pas
           fopen(".verrouData", "w+"); //mode w+ pour créer le fichier s'il n'existe pas
           fclose(".verrouData");
           float consigne;
           FILE *data;
           data = fopen("data.txt", "r");
           //fscanf(data, "%f", consigne);
           remove(".verrouData");
       }
   }