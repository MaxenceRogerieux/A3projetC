#include <unistd.h>
#include "consigne.h"
#include <unistd.h>

float consigne(float thermostatPrec_f)
{
   float consigne;
   if( access( ".verrouConsigne", F_OK ) != -1 ){
      // Fichier existe
      return thermostatPrec_f; //si pas de fichier verrou, la valeur précedente du thermostat est return
   }
   else{
      // Fichier n'existe pas
      // création fichier verrou
      FILE* fichier_verrou = fopen(".verrouConsigne", "w+");
      fclose(fichier_verrou);
      // récupération de la consigne

      FILE* dataFile=NULL;
       dataFile = fopen("consigne.txt", "r+");
      if(dataFile == NULL){
            printf("Error in opening file\n");

      }
      else{
          char ligne[8];
          fgets(ligne, 8, dataFile);
          consigne = strtof(ligne,NULL);
          fclose(dataFile);
      }
      remove(".verrouConsigne");// suppression fichier verrou
      return consigne;
   }
//float thermostat_f=0;
//return thermostat_f;
}