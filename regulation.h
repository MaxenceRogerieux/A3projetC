    #include <stdio.h>
	#include <stdlib.h>
	#include "define.h" 

    float TOR(float consigne, float temperature);
    float PID(float temp, float tempPrev, float consigne, float* errorSum);
    float regulationTest(int regul,float consigne,float* tabT, int nT);
