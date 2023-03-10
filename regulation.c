    #include <stdio.h>
	 #include <stdlib.h>
    #include "regulation.h"

	float TOR(float consigne, float temperature){ // fonction tout ou rien
        if(temperature<consigne){
            return 40; // 40%
        } else {
            return 0; // 0%
        }
}
    float PID(float temp, float tempPrev, float consigne, float* errorSum){ // fonction proportionnelle integrale dérivée
        float error; // e(t)
        float errorVar; // derivée(e(t))
        float errorPrev; // e(t-1)

        error = consigne - temp;
        errorPrev = consigne - tempPrev;

        if(tempPrev-temp<0){
            *errorSum += error*10-((tempPrev-temp)*10/2); // temp decroissante
        } else {
            *errorSum += error*10+((tempPrev-temp)*10/2); // temp croissante
        }
        errorVar = (error-errorPrev)/10; // intégrale e(t)

        // def coeff
        float Kp = 1;
        float Ki = 0.1;
        float Kd = 0.1;

        // def P,I,D
        float P = error * Kp;
        float I = *errorSum * Ki;
        float D = errorVar * Kd;

        // def PID
        float pid = P + I + D;

        // Saturation
        if (pid > 100) {
            pid=100;
        }
        if (pid < 0) {
            pid = 0;
        }
            return pid;
    }
	 
	/* regul : type de régulation (1:Tout ou Rien, 2:PID)
		csgn : température de consigne
		tabT : tableau de températures intérieures successives en entrée de la régulation
		nT : nombre d’entrées dans le tableau tabT*/
	float regulationTest(int regul,float consigne,float* tabT, int nT){
		float cmd;

		// TOR
        if(regul == 1){
            // nT tests
            for (int i = 0; i < nT; i++) {
                cmd = TOR(consigne,tabT[i]);
            }
        }

        // PID
        if(regul == 2){
            float errorSum = 0; // initialisation de l'intergale
            // nT tests
            for (int i = 1; i < nT; ++i) {
                cmd = PID(tabT[i],tabT[i-1],consigne,&errorSum);
            }
        }
		return cmd;
	}
	//retourne cmd après nT appels à la fonction regulation()
  
