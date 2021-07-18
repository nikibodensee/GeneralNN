/*----------------------------------------------------------------------
*  File: 4.0. teach.c
*  Project: GeneralNN_GUI_1.0
*  Version: V1.0
*  Created on: 08.11.2020, 20:19:59
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

#include "main.h"

extern float learnr;	// Lernrate im main-Programm definiert
extern int amounthiddenlayers;
extern int input_nodes;
extern int output_nodes;
extern int mustz;
extern int hidden_nodes[layermax];
extern float dopz[input_nodesmax][mustzmax];
extern float w[layermax][input_nodesmax][hidden_nodesmax];
extern float dopact[layermax][hidden_nodesmax];
extern float act[layermax][hidden_nodesmax];
extern float oe[output_nodesmax];
extern float her[layermax][hidden_nodesmax];
extern float er[layermax][hidden_nodesmax][hidden_nodesmax];

void teach(int m){

    int  h0, i, j;
    float mid; 		// temporärer Wertspeicher
    float sv; 		// temporärer Wertspeicher um Einzelfehler zu addieren
    float d; 		// temporärer Wertspeicher Fehler * mid
    float de; 		// Gewichtsänderung

    //-- Berechnung Einzelfehler letzte Hidden-Schicht, Gewichtsanpassung
    for (i = 0; i < output_nodes; i++) {
        mid = act[amounthiddenlayers][i]
              * (1 - act[amounthiddenlayers][i]);// Maßnahme, um Rechenschritte aus der Schleife
        d = -oe[i] * mid;				// zu nehmen und dadurch Zeit zu sparen
        for (j = 0; j < hidden_nodes[amounthiddenlayers - 1]; j++) {
            er[amounthiddenlayers - 1][j][i] = d * w[amounthiddenlayers][j][i];
            de = d * dopact[amounthiddenlayers - 1][j];
            w[amounthiddenlayers][j][i] = w[amounthiddenlayers][j][i] - learnr * de;
        }
    }

    //-- Berechnung Gesamtfehler letzter her Hidden-Schicht
    sv = 0;
    for (i = 0; i < hidden_nodes[amounthiddenlayers - 1]; i++) {
        for (j = 0; j < output_nodes; j++) {
            sv += er[amounthiddenlayers - 1][i][j];
        }
        her[amounthiddenlayers - 1][i] = sv;// Zwischenschritt führt zu schnellerer Gesamtfehlerabnahme???
        sv = 0;
    }




    for (h0 = amounthiddenlayers - 1; h0 > 0; h0--) {
        //-- Berechnung Einzelfehler Hidden-Schicht, Gewichtsanpassung
        for (i = 0; i < hidden_nodes[h0]; i++) {
            mid = dopact[h0][i] * (1 - dopact[h0][i]);
            d = her[h0][i] * mid;
            for (j = 0; j < hidden_nodes[h0 - 1]; j++) {
                er[h0 - 1][j][i] = d * w[h0][j][i];
                de = d * dopact[h0 - 1][j];
                w[h0][j][i] = w[h0][j][i] - learnr * de;
            }
        }

        //-- Berechnung Gesamtfehler her Hidden-Schicht
        sv = 0;
        for (i = 0; i < hidden_nodes[h0 - 1]; i++) {
            for (j = 0; j < hidden_nodes[h0]; j++) {
                sv += er[h0 - 1][i][j];
            }
            her[h0 - 1][i] = sv;
            sv = 0;
        }
    }



    //-- Gewichtsanpassung
    for (i = 0; i < hidden_nodes[0]; i++) {
        mid = dopact[0][i] * (1 - dopact[0][i]);
        for (j = 0; j < input_nodes; j++) {
            de = her[0][i] * mid * dopz[j][m];
            w[0][j][i] = w[0][j][i] - learnr * de;
        }
    }
}





