#include <unistd.h>
#include "consigne.h"
#include <unistd.h>

float consigne(float thermostatPrec_f)
{
   if( access( ".verrouConsigne", F_OK ) != 1 ){
      // Fichier existe
      return thermostatPrec_f; //si pas de fichier verrou, la valeur précedente du thermostat est return
   }
   else{
      // Fichier n'existe pas
      // création fichier verrou
      FILE* fichier_verrou = fopen(".verrouConsigne", "w+");
      fclose(fichier_verrou);
      // récupération de la consigne
      float consigne;
      FILE* data=NULL;
      data = fopen("consigne.txt", "r");
      if(data == NULL){
            printf("Error in opening file");
            return 1;
      }
      else{
         fscanf(data, "%f", consigne);
         fclose(data);
         // suppression fichier verrou
      }
      remove(".verrouConsigne");
      return consigne;
   }
//float thermostat_f=0;
//return thermostat_f;
}