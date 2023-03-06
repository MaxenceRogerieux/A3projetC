#include <stdio.h>
#include <unistd.h>
#include "consigne.h"
#include "visualisationT.h"
#include "visualisationC.h"
#include "regulation.h"
#include <math.h>
float testConsigne(){
	
	float score=0.0;
	// Variables declaration
	FILE* pf;
	
	float consigne_val[2];
	consigne_val[0]=10.0;
	consigne_val[1]=16.0;
	
	float consigne_read;

	int test_reader = 0;
	int test_lock = 0;
	/*********************************************
	Data file initialisation
	**********************************************/
	pf=fopen("consigne.txt","w");
	if(pf==NULL){
		perror("in autotests.c, file not found");
	}
	fprintf(pf,"%.2f\n",consigne_val[0]);
	fclose(pf);
	/**********************************************
	Remove verrou if exists
	**********************************************/
	if( access( ".verrouConsigne", F_OK )!=-1)
	{
		remove(".verrouConsigne");
	}

	/*******************************
	Check consigne function: Reading consigne.txt
	*********************************/
	consigne_read=consigne(consigne_val[1]);
	if(consigne_read==consigne_val[0]){
		score +=0.5; 
		//CU_PASS("test_consigne_reader");
		#ifdef DISPLAY_DEBUG
		printf("test_consigne_reader OK\n");
		#endif
		test_reader=1;
	}else{
		//CU_FAIL("test_consigne_reader");
		#ifdef DISPLAY_DEBUG
		printf("test_consigne_reader failed\n");
		#endif
		test_reader=0;
	}

	if(test_reader==1){
		/*********************************************
		Data file initialisation
		**********************************************/
		pf=fopen("consigne.txt","w");
		if(pf==NULL){
			perror("in testu_consigne.c, file not found");
		}
		fprintf(pf,"%.2f\n",consigne_val[0]);
		fclose(pf);
		// Create lock file
		pf = fopen(".verrouConsigne","w");
		fclose(pf);
		/**********************************
		 Check consigne function: lock file .verrouConsigne
		 ***********************************/
		// Read in the consigne.txt file (should not work)
		consigne_read=consigne(consigne_val[1]);

		if( access( ".verrouConsigne", F_OK ) != -1 )
		{ 
			//End of test: remove lock
			remove(".verrouConsigne");
		}

		if(consigne_read==consigne_val[1]){
			test_lock = 1;
		}else{
			test_lock = 0;
		}
	}else{
		test_lock=0;
	}

	if(test_lock == 1){
		score+=0.5;
		//CU_PASS("test_consigne_lock");
		#ifdef DISPLAY_DEBUG
		printf("test_consigne_lock OK\n");
		#endif
	}else{
		//CU_FAIL("test_consigne_lock");
		#ifdef DISPLAY_DEBUG
		printf("test_consigne_lock failed\n");
		#endif
	}
	return score;
}

float testVisualisationT(){
	float score=0.0;
	// Variables declaration
	FILE* pf;

	temp_t temperature[3];
	temperature[0].exterieure=2.0;
	temperature[0].interieure=9.0;
	temperature[1].exterieure=12.0;
	temperature[1].interieure=22.0;
	temperature[2].exterieure=10.0;
	temperature[2].interieure=20.0;
	char* temoin_chauffe=malloc(8*sizeof(char));
	
	float exterieure_read;
	float interieure_read;
	char* temoin_chauffe_read=malloc(8*sizeof(char));

	int test_display=0;
	int test_lock = 0;
	strcpy(temoin_chauffe,"true");
	
	/*********************************************
	Data file initialisation
	**********************************************/
	pf=fopen("data.txt","w");
	if(pf==NULL){
		perror("in testu_visualisationT.c, file not found");
	}
	fprintf(pf,"%.2f\n%.2f\n",temperature[0].exterieure,temperature[0].interieure);
	fprintf(pf,"%s",temoin_chauffe);
	fclose(pf);
	/**********************************************
	Remove verrou if exists
	**********************************************/
	if( access( ".verrouData", F_OK )!=-1)
	{
		remove(".verrouData");
	}

	/*******************************
	Check visualisationT function: writing data.txt
	*********************************/
	visualisationT(temperature[1]);
	pf=fopen("data.txt","r");
	if(pf==NULL){
		test_display=0;
	}
	else
	{
		fscanf(pf,"%f\n%f",&exterieure_read,&interieure_read);
		fscanf(pf,"%s",temoin_chauffe_read);
		fclose(pf);
		if(exterieure_read==temperature[1].exterieure && interieure_read==temperature[1].interieure && strcmp(temoin_chauffe,temoin_chauffe_read)==0){
			test_display=1;
		}else{
			test_display=0;
		}
	}

	if(test_display==1){
		#ifdef DISPLAY_DEBUG
		printf("test visualisationT_display OK\n");
		#endif 
		score+=0.5;
		//CU_PASS("test_visualisationT_display");

	}else{
		//CU_FAIL("test_visualisationT_display");
		#ifdef DISPLAY_DEBUG
		printf("test visualisationT_display failed\n");
		#endif
	}

	if(test_display==1){
		/*********************************************
		Data file initialisation
		**********************************************/
		pf=fopen("data.txt","w");
		if(pf==NULL){
			perror("in testu_visualisationT.c, file not found");
		}
		fprintf(pf,"%.2f\n%.2f\n",temperature[0].exterieure,temperature[0].interieure);
		fprintf(pf,"%s",temoin_chauffe);
		fclose(pf);
		// Create lock file
		pf = fopen(".verrouData","w");
		fclose(pf);
		/**********************************
		 Check visualisationT function: lock file .verrouData
		 ***********************************/
		// Data to write in the data.txt file (should not work)
		visualisationT(temperature[2]);

		if( access( ".verrouData", F_OK ) != -1 )
		{ 
			//End of test: remove lock
			remove(".verrouData");
		}

		// Check value from data.txt
		pf=fopen("data.txt","r");
		if(pf==NULL){
			test_lock=0;
		}
		else
		{
			fscanf(pf,"%f\n%f",&exterieure_read,&interieure_read);
			fscanf(pf,"%s",temoin_chauffe_read);
			fclose(pf);
			// Values in data.txt should not have changed: mes
			if(exterieure_read==temperature[0].exterieure && interieure_read==temperature[0].interieure && strcmp(temoin_chauffe,temoin_chauffe_read)==0){
				test_lock=1;
			}else{
				test_lock=0;
			}
		}
	}else{
		test_lock = 0;
	}
	
	if(test_lock==1){
		//CU_PASS("test_visualisationT_lock");
		score+=0.5;
		#ifdef DISPLAY_DEBUG
		printf("test visualisationT_lock OK\n");
		#endif

	}else{
		//CU_FAIL("test_visualisationT_lock");
		#ifdef DISPLAY_DEBUG
		printf("test visualisationT_lock failed\n");
		#endif
	}

	free(temoin_chauffe);
	free(temoin_chauffe_read);
	return score;
}

float testVisualisationC(){
	float score = 0.0;

	// Variables declaration
	FILE* pf;
	int i;
	int test_display=0;
	int test_lock=0;

	float puissance[2]={35.0,0.0};
	float exterieure[2]={11.0,10.0};
	float interieure[2]={17.0,18.0};
	char* temoin_chauffe=malloc(8*sizeof(char));

	float puissance_read;
	float exterieure_read;
	float interieure_read;
	char* temoin_chauffe_read=malloc(8*sizeof(char));

	strcpy(temoin_chauffe,"not");
	/**********************************************
	Remove verrou if exists
	**********************************************/
	if( access( ".verrouData", F_OK )!=-1)
	{
		remove(".verrouData");
	}

	for(i=0;i<=1;i++){
		/*********************************************
		Data file initialisation
		**********************************************/

		pf=fopen("data.txt","w");
		if(pf==NULL){
			perror("in testu_visualisationC.c, file not found");
		}
		fprintf(pf,"%.2f\n%.2f\n",exterieure[i],interieure[i]);
		fprintf(pf,"%s",temoin_chauffe);
		fclose(pf);

		/*******************************
		Check visualisationC function: writing data.txt
		*********************************/	
		visualisationC(puissance[i]);
		if(puissance[i]==0.0)
		{
			strcpy(temoin_chauffe,"false");
		}
		else
		{
			strcpy(temoin_chauffe,"true");
		}
		pf=fopen("data.txt","r");
		if(pf!=NULL){
			fscanf(pf,"%f\n%f",&exterieure_read,&interieure_read);
			fscanf(pf,"%s",temoin_chauffe_read);
			fclose(pf);
			if(exterieure[i]==exterieure_read && interieure[i]==interieure_read && strcmp(temoin_chauffe,temoin_chauffe_read)==0){
				test_display++;
			}
		}

	}
	if(test_display==2){
		
		//CU_PASS("test_visualisationC_display");
		score+=0.5;
		#ifdef DISPLAY_DEBUG
		printf("test visualisationC_display OK\n");
		#endif
	}else{
		
		//CU_FAIL("test_visualisationC_display");
		#ifdef DISPLAY_DEBUG
		printf("test visualisationT_display failed [%d/2 succeeded]  \n",test_display);
		#endif
	}

	/**********************************
	 Check visualisationC function: lock file .verrouData
	 ***********************************/
	 // Test lock file only if display test succeeded
	if(test_display==2){	
		 /*********************************************
		Data file initialisation
		**********************************************/
		strcpy(temoin_chauffe,"not");
		pf=fopen("data.txt","w");
		if(pf==NULL){
			perror("in testu_visualisationC.c, file not found");
		}
		fprintf(pf,"%.2f\n%.2f\n",exterieure[0],interieure[0]);
		fprintf(pf,"%s",temoin_chauffe);
		fclose(pf);
	
		// Create lock file
		pf = fopen(".verrouData","w");
		fclose(pf);

		// data to write in the data.txt file (should not work)
		visualisationC(puissance[0]);

		if( access( ".verrouData", F_OK ) != -1 ){ 
			//End of test: remove lock
			remove(".verrouData");
		}

		// Check value from data.txt
		pf=fopen("data.txt","r");
		if(pf==NULL){
			test_lock = 0;
		}else{		
			fscanf(pf,"%f\n%f",&exterieure_read,&interieure_read);
			fscanf(pf,"%s",temoin_chauffe_read);
			fclose(pf);
			// Values in data.txt should not have changed
			if(exterieure[0]==exterieure_read && interieure[0]==interieure_read && strcmp(temoin_chauffe,temoin_chauffe_read)==0){
				test_lock = 1;
			}else{
				test_lock = 0;
			}
		}
	}else{
		test_lock = 0;
	}
	
	if(test_lock==1){
		
		//CU_PASS("test_visualisationC_lock");
		score+=0.5;
		#ifdef DISPLAY_DEBUG
		printf("test visualisationC_lock OK\n");
		#endif
	}else{

		
		//CU_FAIL("test_visualisationC_lock");
		#ifdef DISPLAY_DEBUG
		printf("test visualisationC_lock failed\n");
		#endif
	}		

	free(temoin_chauffe);
	free(temoin_chauffe_read);

	return score;

}

float testRegulationTOR(){
	float score = 0.0;
	int nPassedTest=0;
	float consigne = 19.0;
	float tInt0 = 19.5;
	float deltaT = -0.5;
	int nT = 3;
	float tabT[nT];
	int i=0;
	float cmd=0;
	float cmd_target = 40;
	tabT[0] = tInt0;
	for(i=1;i<nT;i++){
		tabT[i] = tabT[i-1]+deltaT;
	}
	cmd = regulationTest(1,19,tabT,nT);
	if(fabs(cmd-cmd_target)>0.1){
		#ifdef DISPLAY_DEBUG
		printf("test regulation PID 1/2 failed [cmd=%f cmd_target=%f]\n",cmd,cmd_target);
		#endif
	}else{
		nPassedTest++;
		#ifdef DISPLAY_DEBUG
		printf("test regulation PID 1/2 passed\n");
		#endif
	}
	tInt0 = 18.5;
	deltaT = 0.5;
	cmd_target = 0.0;
	tabT[0] = tInt0;
	for(i=1;i<nT;i++){
		tabT[i] = tabT[i-1]+deltaT;
	}
	cmd = -100;
	cmd = regulationTest(1,19,tabT,nT);
	if(fabs(cmd-cmd_target)>0.1){
		#ifdef DISPLAY_DEBUG
		printf("test regulation TOR 2/2 failed [cmd=%f cmd_target=%f]\n",cmd,cmd_target);
		#endif
	}else{
		nPassedTest++;
		#ifdef DISPLAY_DEBUG
		printf("test regulation TOR 2/2 passed\n");
		#endif
	}
	if(nPassedTest == 2){
		//CU_PASS("test_regulation_TOR");
		score+=1;
		#ifdef DISPLAY_DEBUG
		printf("test regulation TOR passed\n");
		#endif
	}else{
		//CU_FAIL("test_regulation_TOR");
		#ifdef DISPLAY_DEBUG
		printf("test regulation TOR failed\n");
		#endif
	}

	return score;
}

float testRegulationPID(){
	float score=0.0;
	float consigne = 19.0;
	float tInt0 = 15.0;
	float deltaT = 0.1;
	int nT = 30;
	float tabT[nT];
	int i=0;
	float cmd=0;
	float cmd_target = 75.05;
	tabT[0] = tInt0;
	for(i=1;i<nT;i++){
		tabT[i] = tabT[i-1]+deltaT;
	}
	cmd = regulationTest(2,19,tabT,nT);
	if(fabs(cmd-cmd_target)>0.1){
		//CU_FAIL("test_regulation_PID");
		#ifdef DISPLAY_DEBUG
		printf("test regulation PID failed [cmd=%f cmd_target=%f]\n",cmd,cmd_target);
		#endif
	}else{
		//CU_PASS("test_regulation_PID");
		score+=1;
		#ifdef DISPLAY_DEBUG
		printf("test regulation PID passed\n");
		#endif
	}

	return score;

}