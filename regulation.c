    #include <stdio.h>
	 #include <stdlib.h>
    #include "regulation.h"

	float TOR(float consigne, float temperature){
        if(temperature<consigne){
            return 40;
        } else {
            return 0;
        }
}
    float PID(float consigne, float tempA, float tempB, float temperature){
        float P = consigne-temperature;
        float I = 0;
        float D = (tempB-tempA)/4;

        if(temperature<consigne){

        } else {

        }
    }
	 
	/* regul : type de régulation (1:Tout ou Rien, 2:PID)
		csgn : température de consigne
		tabT : tableau de températures intérieures successives en entrée de la régulation
		nT : nombre d’entrées dans le tableau tabT*/
	float regulationTest(int regul,float consigne,float* tabT, int nT){
		float cmd;
        if(regul == 1){
            for (int i = 0; i < nT; i++) {
                cmd = TOR(consigne,tabT[i]);
            }
        }

        if(regul == 2){
            for (int i = 0; i < nT; ++i) {
                cmd = PID(consigne,tabT[i-2],tabT[i-1],tabT[i]);
            }
        }
		return cmd;
	}
	/*
	retourne cmd après nT appels à la fonction regulation()
	*/
  
