    #include <stdio.h>
	 #include <stdlib.h>
    #include "regulation.h"

#include "math.h"
	float TOR(float consigne, float temperature){
        if(temperature<consigne){
            return 40;
        } else {
            return 0;
        }
}
    float PID(float temp, float tempPrev, float consigne, float* errorSum) {
        float error;
        float errorVar;
        float errorPrev;

        error = consigne - temp;
        errorPrev = consigne - tempPrev;

        if (tempPrev - temp < 0) {
            *errorSum += error * 10 - ((tempPrev - temp) * 10 / 2); //temp decroissante
        } else {
            *errorSum += error * 10 + ((tempPrev - temp) * 10 / 2); //temp croissante
        }
        errorVar = (error - errorPrev) / 10;

        // def coeff
        float Kp = 1;
        float Ki = 0.1;
        float Kd = 0.1;
        // def P,I,D
        float P = error * Kp;
        float I = *errorSum * Ki;
        float D = errorVar * Kd;

        float pid = P + I + D;
        //saturation
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


        if(regul == 1){
            for (int i = 0; i < nT; i++) {
                cmd = TOR(consigne,tabT[i]);
            }
        }

        if(regul == 2){
            float errorSum = 0;
            for (int i = 1; i < nT; ++i) {
                cmd = PID(tabT[i],tabT[i-1],consigne,&errorSum);
            }
        }
		return cmd;
	}
	/*
	retourne cmd après nT appels à la fonction regulation()
	*/
//hello
/*
BACKUP (ANCIENNE VERSION)
float PID(float error,float errorSum,float errorVar){
        // def coeff
        float Kp = 1;
        float Ki = 0.1;
        float Kd = 0.1;
        // def P,I,D
        float P = error*Kp;
        float I = errorSum*Ki;
        float D = errorVar*Kd;

        float pid = P+I+D;

        return pid;
    }
	 
	
	float regulationTest(int regul,float consigne,float* tabT, int nT){
		float cmd;
		float error = 0;
        float errorSum = 0;
        float errorVar = 0;
        float errorPrev = 0;
        float tempPrev = 0;

        if(regul == 1){
            for (int i = 0; i < nT; i++) {
                cmd = TOR(consigne,tabT[i]);
            }
        }

        if(regul == 2){
            for (int i = 1; i < nT; ++i) {
                error = consigne - tabT[i];
                if(tabT[i-1]-tabT[i]<0){
                    errorSum += error*10-((tabT[i-1]-tabT[i])*10/2); //temp decroissante
                } else {
                    errorSum += error*10+((tabT[i-1]-tabT[i])*10/2); //temp croissante
                }
                errorVar = (error-errorPrev)/10;
                cmd = PID(error,errorSum,errorVar);
                errorPrev = error;
            }
        }
		return cmd;
	}


*/
  
