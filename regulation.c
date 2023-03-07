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
    float PID(float error,float errorSum,float errorVar){
        float Kp = 1;
        float Ki = 0.1;
        float Kd = 0.1;

        float sum = 0;

        float P = error*Kp;
        float I = errorSum*Ki;
        float D = errorVar*Kd;

//        if(posnT >= 0){
//            D = (( (consigne-(tabT[nT])) - (consigne-tabT[nT-1])) /4)*Kd;
//        } else {
//            D = (( (consigne-(tabT[0])) - (consigne-tabT[1])) /4)*Kd;
//        }

        float pid = P+I+D;

        //printf("PID :%f/%f/%f\n",P,I,D);

        return pid;
    }
	 
	/* regul : type de régulation (1:Tout ou Rien, 2:PID)
		csgn : température de consigne
		tabT : tableau de températures intérieures successives en entrée de la régulation
		nT : nombre d’entrées dans le tableau tabT*/
	float regulationTest(int regul,float consigne,float* tabT, int nT){
		float cmd;
		float error = 0;
        float errorSum = 0;
        float errorVar = 0;
        float errorPrev = 0;

        if(regul == 1){
            for (int i = 0; i < nT; i++) {
                cmd = TOR(consigne,tabT[i]);
            }
        }

        if(regul == 2){
            //printf("%f\n",tabT[0]);
            for (int i = 0; i < nT; ++i) {
                error = consigne - tabT[i];
                errorSum += error;
                errorVar = error-errorPrev;
                printf("%f\n",tabT[i]);
                //printf("Errors : %f/%f/%f/%f\n",error,errorSum,errorVar,errorPrev);
                cmd = PID(error,errorSum,errorVar);
                errorPrev = error;
            }
        }
		return cmd;
	}
	/*
	retourne cmd après nT appels à la fonction regulation()
	*/
  
