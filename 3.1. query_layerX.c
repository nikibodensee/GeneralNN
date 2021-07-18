/*----------------------------------------------------------------------
*  File: 3.2. query_layerX.c
*  Project: GeneralNN_GUI_1.0
*  Version: V1.0
*  Created on: 08.11.2020, 18:39:55
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
extern float act[layermax][hidden_nodesmax];
extern int hidden_nodes[layermax];
extern float dopact[layermax][hidden_nodesmax];
extern float w[layermax][input_nodesmax][hidden_nodesmax];
extern float doprop[2];


void query_layerX (int h){

    srand (time(NULL));		//Randomized Timer: Zufallszahlen nach jedem Start neu
    float zp; 				// Zufallszahl Dropout
    float s = 0; 				// Summe aller a(i) * w(ij)
    int y, i;

    for(y = 0; y < hidden_nodes[h]; y++){
        dopact[h-1][y] = act[h-1][y];
        zp = (float) rand() / (RAND_MAX);
        if(zp < dop_h){
            dopact[h][y] = 0;
        }
    }

    //-- Ermittlung des Aktivation der Hidden-Units Layer 1 (Abhängigkeit von Hidden-Unit-Nr. und Wort(x = mustz))
    for (y = 0; y <hidden_nodes[h]; y++){
        for (i = 0; i<hidden_nodes[h-1]; i++){
            s += dopact[h-1][i] * w[h][i][y];			// Multiplikation Input-Wert und Gewicht
        }

        //-- Verrechnung der Aktivation mit Sigmoidfunktion und Ermittlung der Unit-Ausgabe
        act[h][y] = 1 / (1+exp(-s));				// Ermittlung Aktivation: Verrechnung aus Summe aller Inputs und Sigmoidfunktion
        s = 0;
    }
}

void query_layerXq (int h){

    float s = 0; 	// Summe aller a(i) * w(ij)
    int y, i;

    //-- Ermittlung des Aktivation der Hidden-Units Layer 1 (Abhängigkeit von Hidden-Unit-Nr. und Wort(x = mustz))
    for (y = 0; y < hidden_nodes[h]; y++){
        for (i = 0; i<hidden_nodes[h-1]; i++){
            s += act[h-1][i] * w[h][i][y] * (1-doprop[1]);	// Gesamtenergie im Query an Energie im Training anpassen; Kehrwert, da do... Wahrscheinlichkeit für 0 amgibt
        }

        //-- Verrechnung der Aktivation mit Sigmoidfunktion und Ermittlung der Unit-Ausgabe
        act[h][y] = 1 / (1+exp(-s));				// Ermittlung Aktivation: Verrechnung aus Summe aller Inputs und Sigmoidfunktion
        s = 0;
    }
}


