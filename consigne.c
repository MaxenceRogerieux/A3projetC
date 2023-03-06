#include <unistd.h>
#include "consigne.h"
#include <unistd.h>


   float consigne(float thermostatPrec_f)
   {
       if( access( ".verrouConsigne", F_OK ) != 1 ){
// Fichier existe
            return thermostatPrec_f; //si pas de fichier verrou, la valeur précedente du thermostat est return
       }else{
// Fichier n'existe pas
           fopen(".verrouConsigne","w+"); //mode w+ pour créer le fichier s'il n'existe pas
           float consigne;
           FILE* data;
           data = fopen("consigne.txt", "r");
           fscanf(data, "%f", consigne);
           remove(".verrouConsigne");
           return consigne;
   }



      //float thermostat_f=0;
      //return thermostat_f;
   
   }
