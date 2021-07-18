/*----------------------------------------------------------------------
*  File: 3.0. query_inputlayer.c
*  Project: GeneralNN_GUI_1.0
*  Version: V1.0
*  Created on: 08.11.2020, 18:35:16
*  Author: N. Kornel
*  Company: Nensys
*
*  Copyright © 2020 by Nensys GbR
*  Use of this file and all called functions requires a license.
*  Further distribution in any form is prohibited.
*
*  Description:
*
*
*
*---------------------------------------------------------------------*/
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "main.h"

extern float dop_i;
extern int input_nodes;

extern float z[input_nodesmax][mustzmax];
extern float dopz[input_nodesmax][mustzmax];
extern int hidden_nodes[layermax];
extern float w[layermax][input_nodesmax][hidden_nodesmax];
extern float act[layermax][hidden_nodesmax];
extern float doprop[2];


void query_inputlayer (int m){

    srand (time(0));		//Randomized Timer: Zufallszahlen nach jedem Start neu
    float zp; 				// Zufallszahl Dropout
    float s = 0; 				// Summe aller a(i) * w(ij)
    int y, i;

    for(i = 0; i < input_nodes; i++){
//		printf("IPUT %d: %f\n",i,z[i][m]*255);  // für GUI ausgabe
        dopz[i][m] = z[i][m];
        zp = (float) rand() / (1);
        if(zp < dop_i){
            dopz[i][m] = 0;
        }
    }

    //-- Ermittlung des Aktivation der Hidden-Units Layer 1 (Abhängigkeit von Hidden-Unit-Nr. und Muster(x = mustz))
    for (y = 0; y <hidden_nodes[0]; y++){
        for (i = 0; i<input_nodes; i++){
            s += dopz[i][m] * w[0][i][y];		// Multiplikation Input-Wert und Gewicht
        }

        //-- Verrechnung der Aktivation mit Sigmoidfunktion und Ermittlung der Unit-Ausgabe
        act[0][y] = 1 / (1+exp(-s));			// Ermittlung Aktivation: Verrechnung Summe aller Inputs und Sigmoidfunktion
        s = 0;
    }
}

void query_inputlayerq (int m){

    float s = 0; 	// Summe aller a(i) * w(ij)
    int y, i;

    //-- Ermittlung des Aktivation der Hidden-Units Layer 1 (Abhängigkeit von Hidden-Unit-Nr. und Muster(x = mustz))
    for (y = 0; y <hidden_nodes[0]; y++){
        for (i = 0; i<input_nodes; i++){
            s += z[i][m] * w[0][i][y] * (1-doprop[0]);	// Gesamtenergie im Query an Energie im Training anpassen; Kehrwert, da do... Wahrscheinlichkeit für 0 amgibt
        }

        //-- Verrechnung der Aktivation mit Sigmoidfunktion und Ermittlung der Unit-Ausgabe
        act[0][y] = 1 / (1+exp(-s));			// Ermittlung Aktivation: Verrechnung Summe aller Inputs und Sigmoidfunktion
        s = 0;
    }
}


