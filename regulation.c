    #include <stdio.h>
	 #include <stdlib.h>
    #include "regulation.h"
	 
	float regulationTest(int regul,float consigne,float* tabT, int nT){
		float cmd;
		
		return cmd;
	}
//     Cette fonction retourne la valeur de la commande de chauffage obtenue après
// nT appels à la fonction regulation() :
// • regul : type de régulation (1:Tout ou Rien, 2:PID)
// • csgn : température de consigne
// • tabT : tableau de températures intérieures successives en entrée de la
// régulation
// • nT : nombre d’entrées dans le tableau tabT
// Pour la régulation PID, les gains sont fixés à Kp=1, Ki=0.1 et Kd=0.1. La loi de
// saturation entre la valeur de PID et la commande de chauffage est linéaire.

// Points essentiels
// • Déterminer la puissance de chauffage
// ▪ Valeurs possibles
// • Tout ou rien : 0 (éteint) ou 40% de la puissance maximale (allumé)
// • PID : 0 à 100 %	
// TINT+TCONSIGNE-->Puissance de
// chauffage en %
// (0 à 100)


// Points essentiels
// • Calcul du PID
// • Déterminer la puissance de chauffage
// ▪ Points critiques
// • Calcul du terme intégral et dérivé
// • Lien entre le PID et la puissance de chauffage : loi + saturation
// • Gains optimisant la régulation (KP, KI, KD)
  
