#include "visualisationT.h"

#include <unistd.h>

// mettre les valeurs de myTemp dans le file
void visualisationT(temp_t myTemp)
{
    if( access( ".verrouData", F_OK ) != -1 ){
        // Fichier existe
    }
    else{
        // Fichier n'existe pas
    }
    remove(".verrouData")
}
