#include <stdio.h>
#include <stdlib.h>
#include "simulateur.h"
#include "autotests.h"
#include "regulation.h"
#include "visualisationC.h"
#include "visualisationT.h"
#include "consigne.h"
#include <unistd.h>

int main(){
    remove(".verrouConsigne");// supprime fichier verrou
    remove(".verrouData");// supprime fichier verrou

    float errorSum = 0;
    float puissance = 0;
	temp_t temperature;
	temperature.exterieure = 14.0;
	temperature.interieure = 15.0;

	float temp;
	float tempPrev;

    float csgn = 20;
    float csgnPrev = consigne(20);

	struct simParam_s*  monSimulateur_ps = simConstruct(temperature); // creation du simulateur, puissance intialis�e � 0%
	while(csgn>5){
        temp = temperature.interieure;

        //consigne
        //csgn = consigne(csgnPrev);
        csgn = consigne(csgnPrev);
        //puissance
        puissance = PID(temp,tempPrev,csgn,&errorSum);


		temperature=simCalc(puissance,monSimulateur_ps); // simulation de l'environnement

		// visuT
        visualisationT(temperature);
        //visuC
        visualisationC(PID(temp,tempPrev,csgn,&errorSum)); // témoin de chauffe

        //printf("%f\n",puissance);
        tempPrev = temp;
        csgnPrev = csgn;
        sleep(0.5);
	}
	puissance = 0;
	simDestruct(monSimulateur_ps); // destruction de simulateur

     //AUTOTESTS
//     float score1=0,score2=0,score3=0,score4=0,score5=0;
//
//     score1 = testVisualisationT();
//     score2 = testConsigne();
//     score3 = testVisualisationC();
//
//     score4 = testRegulationTOR();
//     score5 = testRegulationPID();
//     printf("----- Auto tests results: -----\n");
//     printf("testVisualisationT\t:score=%g%%\n",score1*100);
//     printf("testConsigne \t\t:score=%g%%\n",score2*100);
//     printf("testVisualisationC\t:score=%g%%\n",score3*100);
//     printf("testRegulationTOR\t:score=%g%%\n",score4*100);
//     printf("testRegulationPID\t:score=%g%%\n",score5*100);

	return EXIT_SUCCESS;
}
