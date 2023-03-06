#include "visualisationT.h"

#include <unistd.h>

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
