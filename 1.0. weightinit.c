/*----------------------------------------------------------------------
*  File: 1.0. weightinit.c
*  Project: GeneralNN_GUI_1.0
*  Version: V1.0
*  Created on: 07.11.2020, 16:17:44
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
#include <stdlib.h>
#include <time.h>

#include "main.h"


extern int amounthiddenlayers;
extern int input_nodes;
extern int output_nodes;
extern int hidden_nodes[layermax];
extern float w[layermax][input_nodesmax][hidden_nodesmax];

void weightinit (){

    srand (time(NULL));		//Randomized Timer: Zufallszahlen nach jedem Start neu
    int h, i, j;

    //-- Initialisierung Gewichte zwischen Inputschicht und 1. Hidden-Schicht
    for (i = 0; i < input_nodes; i++) {
        for (j = 0; j < hidden_nodes[0]; j++) {
            w[0][i][j] = 1 - 2 * ((float) rand() / (RAND_MAX));	//Initialisierung Gewichte zwischen -1 & 1
//			printf("w[0][%d][%d] = %f\n",i,j,w[0][i][j]);
        }
    }

    for (h = 1; h < amounthiddenlayers; h++) {
        //-- Initialisierung Gewichte zwischen Hidden-Schichten
        for (i = 0; i < hidden_nodes[h - 1]; i++) {
            for (j = 0; j < hidden_nodes[h]; j++) {
                w[h][i][j] = 1 - 2 * ((float) rand() / (RAND_MAX));
//				printf("w[%d][%d][%d] = %f\n",h,i,j,w[h][i][j]);
            }
        }
    }

    //-- Initialisierung Gewichte zwischen letzter Hidden-Schicht und Outputschicht
    for (i = 0; i < hidden_nodes[amounthiddenlayers - 1]; i++) {
        for (j = 0; j < output_nodes; j++) {
            w[amounthiddenlayers][i][j] = 1 - 2 * ((float) rand() / (RAND_MAX));
        }
    }
    printf("\nInitialisierung der neuen Gewichte abgeschlossen\n\n");
}






