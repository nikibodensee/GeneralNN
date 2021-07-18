/*----------------------------------------------------------------------
*  File: 1.1. readweights.c
*  Project: GeneralNN_GUI_1.0
*  Version: V1.0
*  Created on: 07.11.2020, 16:21:39
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

#include "main.h"

extern int amounthiddenlayers;
extern int input_nodes;
extern int output_nodes;
extern int hidden_nodes[layermax+1];
extern float w[layermax][input_nodesmax][hidden_nodesmax];
extern float doprop[2];

extern float learnr;
extern char *filenameweight;

void readweights(){

    FILE *datei; 			// Pointer um mit File umzugehen
    char *filename;			// Variable, um filename zu ändern
    int y, x;

    filename = filenameweight;
    datei = fopen(filename, "r");

    //-- Reines Auslesen der Werte:
    if (datei != NULL) {
        fscanf(datei, "%d", &input_nodes);
        fgetc(datei);
        fscanf(datei, "%d", &amounthiddenlayers);
        fgetc(datei);
        for (int a = 0; a < amounthiddenlayers; a++) {
            fscanf(datei, "%d", &hidden_nodes[a]);          // Anzahl der Hidden-Units
            fgetc(datei);
        }
        fscanf(datei, "%d", &output_nodes);
        fgetc(datei);
        fscanf(datei, "%f", &learnr);
        fgetc(datei);
        fscanf(datei, "%f", &doprop[0]);// Passende Input-Dropoutrate zu Gewichten wird eingelesen
        fgetc(datei);
        fscanf(datei, "%f", &doprop[1]);// Passende Dropoutrate zu Gewichten wird eingelesen
        fgetc(datei);
        for (x = 0; x < input_nodes; x++) {
            for (y = 0; y < hidden_nodes[0]; y++) {
                fscanf(datei, "%f", &w[0][x][y]);
                fgetc(datei);
            }
        }
        for (int z = 1; z < amounthiddenlayers; z++) {
            for (x = 0; x < hidden_nodes[z - 1]; x++) {
                for (y = 0; y < hidden_nodes[z]; y++) {
                    fscanf(datei, "%f", &w[z][x][y]);
                    fgetc(datei);
                }
            }
        }
        for (x = 0; x < hidden_nodes[amounthiddenlayers - 1]; x++) {
            for (y = 0; y < output_nodes; y++) {
                fscanf(datei, "%f", &w[amounthiddenlayers][x][y]);
                fgetc(datei);
            }
        }
        printf("\nreadweights abgeschlossen\n\n");
    } else {
        printf("Datei konnte nicht geöffnet werden\n\n");
    }
}






