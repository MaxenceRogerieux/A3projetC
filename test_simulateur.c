#include <stdio.h>
#include <stdlib.h>
#include "simulateur.h"
#include "autotests.h"
#include "regulation.h"
#include "visualisationC.h"
#include "visualisationT.h"

int main(){
//    float errorSum = 0;
//    float puissance = 0;
//	temp_t temperature;
//	temperature.exterieure = 14.0;
//	temperature.interieure = 15.0;
//	struct simParam_s*  monSimulateur_ps = simConstruct(temperature); // creation du simulateur, puissance intialis�e � 0%
//	int i=0; // increment de boucle
//	//puissance = TOR(30,15); // puissance de chauffage
//
//    //printf("PID : %f\n",PID(15,14,30,&errorSum));
//    //float puissance = 70; // puissance de chauffage
//	for(i=0;i< 750;i++){
//		temperature=simCalc(puissance,monSimulateur_ps); // simulation de l'environnement
//        printf("%f\n",puissance);
//		puissance = PID(15,14,30,&errorSum); // puissance de chauffage
//	}
//	simDestruct(monSimulateur_ps); // destruction de simulateur


     //AUTOTESTS
     float score1=0,score2=0,score3=0,score4=0,score5=0;

     score1 = testVisualisationT();
     score2 = testConsigne();
     score3 = testVisualisationC();

     score4 = testRegulationTOR();
     score5 = testRegulationPID();
     printf("----- Auto tests results: -----\n");
     printf("testVisualisationT\t:score=%g%%\n",score1*100);
     printf("testConsigne \t\t:score=%g%%\n",score2*100);
     printf("testVisualisationC\t:score=%g%%\n",score3*100);
     printf("testRegulationTOR\t:score=%g%%\n",score4*100);
     printf("testRegulationPID\t:score=%g%%\n",score5*100);

	return EXIT_SUCCESS;
}
