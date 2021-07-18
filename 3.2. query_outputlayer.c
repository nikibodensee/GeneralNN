/*----------------------------------------------------------------------
*  File: 3.2. query_outputlayer.c
*  Project: GeneralNN_GUI_1.0
*  Version: V1.0
*  Created on: 08.11.2020, 19:53:44
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
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "main.h"

extern float dop_h;
extern int amounthiddenlayers;
extern int output_nodes;
extern int mustz;
extern int epoche;

extern int hidden_nodes[layermax];
extern float act[layermax][hidden_nodesmax];
extern float dopact[layermax][hidden_nodesmax];
extern float w[layermax][input_nodesmax][hidden_nodesmax];
extern float oe[output_nodesmax];
extern float soe[mustzmax];
extern float serr[epochemax+1];
extern float om[output_nodesmax][mustzmax];
extern float doprop[2];

void query_outputlayer (int m, int e){

    srand (time(NULL));		//Randomized Timer: Zufallszahlen nach jedem Start neu
    float zp; 				// Zufallszahl Dropout
    float s = 0; 				// Summe aller a(i) * w(ij)
    int y, i;

    for(y=0;y<hidden_nodes[amounthiddenlayers-1];y++){
        dopact[amounthiddenlayers-1][y] = act[amounthiddenlayers-1][y];
        zp = (float) rand() / (RAND_MAX);
        if(zp < dop_h){
            dopact[amounthiddenlayers-1][y] = 0;
        }
    }

    //-- Ermittlung des Aktivation der Hidden-Units Layer 1 (Abhängigkeit von Hidden-Unit-Nr. und Wort(x = mustz))
    soe[m] = 0;
    for (y=0;y<output_nodes;y++){
        for (i=0;i<hidden_nodes[amounthiddenlayers-1];i++){
            s += dopact[amounthiddenlayers-1][i] * w[amounthiddenlayers][i][y];			// Multiplikation Input-Wert und Gewicht
//			printf("%f\n",w3[i][y]);
        }

        //-- Verrechnung der Aktivation mit Sigmoidfunktion und Ermittlung der Unit-Ausgabe
        act[amounthiddenlayers][y] = 1 / (1+exp(-s));			// Ermittlung Aktivation: Verrechnung aus Summe aller Inputs und Sigmoidfunktion
        s = 0;

//		printf("OPUT %d %d: %f\n",amounthiddenlayers,y,act[amounthiddenlayers][y]);

        //-- Output-Unit Differenz
        oe[y] = om[y][m] - act[amounthiddenlayers][y];			// Outputfehler pro Unit
        soe[m] += oe[y] * oe[y] * 0.5;			// gegebene Funktion zur Fehlerberechnung Muster: NN selbst programmieren S.79
    }
    //-- Gesamtfehler Epoche*/
    serr[e] += soe[m];
}


void query_outputlayerq (int m, int e){

    float s = 0; 	// Summe aller a(i) * w(ij)
    int y, i; 	// Laufvariablen

    //-- Ermittlung des Aktivation der Hidden-Units Layer 1 (Abhängigkeit von Hidden-Unit-Nr. und Wort(x = mustz))
    soe[m] = 0;
    for (y = 0; y <output_nodes; y++){
        for (i = 0; i<hidden_nodes[amounthiddenlayers-1]; i++){
            s += act[amounthiddenlayers-1][i] * w[amounthiddenlayers][i][y] * (1-doprop[1]);	// Gesamtenergie im Query an Energie im Training anpassen; Kehrwert, da do... Wahrscheinlichkeit für 0 angibt
        }

        //-- Verrechnung der Aktivation mit Sigmoidfunktion und Ermittlung der Unit-Ausgabe
        act[amounthiddenlayers][y] = 1 / (1+exp(-s));			// Ermittlung Aktivation: Verrechnung aus Summe aller Inputs und Sigmoidfunktion
        s = 0;

        //-- Output-Unit Differenz
        oe[y] = om[y][m] - act[amounthiddenlayers][y];			// Outputfehler pro Unit
        soe[m] += oe[y]*oe[y] * 0.5;			// gegebene Funktion zur Fehlerberechnung Muster: NN selbst programmieren S.79
    }
    //-- Gesamtfehler Epoche*/
    serr[e] += soe[m];
}




