#include <stdio.h>
#include <stdlib.h>
#include "simulateur.h"
#include "autotests.h"

int main(){
	temp_t temperature;
	temperature.exterieure = 14.0;
	temperature.interieure = 15.0;
	struct simParam_s*  monSimulateur_ps = simConstruct(temperature); // creation du simulateur, puissance intialis�e � 0%
	int i=0; // increment de boucle
	float puissance = 70.0; // puissance de chauffage
	for(i=0;i< 30;i++){
		temperature=simCalc(puissance,monSimulateur_ps); // simulation de l'environnement

	}

	simDestruct(monSimulateur_ps); // destruction de simulateur


    // AUTOTESTS
    // float score1=0,score2=0,score3=0,score4=0,score5=0;

    // score1 = testVisualisationT();
    // score2 = testConsigne();
    // score3 = testVisualisationC();

    // score4 = testRegulationTOR();
    // score5 = testRegulationPID();
    // printf("----- Auto tests results: -----\n");
    // printf("testVisualisationT\t:score=%g%%\n",score1*100);
    // printf("testConsigne \t\t:score=%g%%\n",score2*100);
    // printf("testVisualisationC\t:score=%g%%\n",score3*100);
    // printf("testRegulationTOR\t:score=%g%%\n",score4*100);
    // printf("testRegulationPID\t:score=%g%%\n",score5*100);

	return EXIT_SUCCESS;
}
