#include "consigne.h"

   float consigne(float thermostatPrec_f)
   {
        float consigne;
        FILE* data;
        data = fopen("consigne.txt", "r");
        fscanf(data, "%f", consigne);
        return consigne;


      //float thermostat_f=0;
      //return thermostat_f;
   
   }
