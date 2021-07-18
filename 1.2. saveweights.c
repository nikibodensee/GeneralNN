/*----------------------------------------------------------------------
*  File: 1.2. saveweights.c
*  Project: GeneralNN_GUI_1.0
*  Version: V1.0
*  Created on: 07.11.2020, 17:32:12
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

extern float dop_i;
extern float dop_h;

extern int amounthiddenlayers;
extern int input_nodes;
extern int output_nodes;
extern int hidden_nodes[layermax];
extern float w[layermax][input_nodesmax][hidden_nodesmax];
extern float learnr;
extern char *filenameweight;


void saveweights(){

    FILE * datei;
    char *filename;
    int x, y;

    //-- neue Datei öffnen
    filename = filenameweight; 	//Gewünschten Filename, Endung: .csv, .txt, ...
    printf("\nfilename= %s", filename);
    fflush(stdout);
    //	getchar();

    //-- neuen File öffnen
    printf("Opening file...\n");
    datei = fopen(filename, "wb");// File wird geöffnet, Modus je nach Bedarf: wb, etc.
    if (datei == NULL) {// Wenn Datei nicht erstellt werden kann: Rückgabe NULL
        printf("Error opening file\n");
        fflush(stdout);
    }
    printf("schreibt in Datei...\n");
    fflush(stdout);

    //-- Netzdaten einspeichern:
    fprintf(datei, "%d", input_nodes);
    fprintf(datei,",");
    fprintf(datei, "%d", amounthiddenlayers);
    fprintf(datei,",");
    for (int a = 0; a < amounthiddenlayers; a++) {
        fprintf(datei, "%d", hidden_nodes[a]);        // Anzahl der Hidden-Units
        fprintf(datei,",");
    }
    fprintf(datei, "%d", output_nodes);
    fprintf(datei,",");
    fprintf(datei, "%f", learnr);
    fprintf(datei,",");
    fprintf(datei, "%f", dop_i); // Passende Input-Dropoutrate zu Gewichten wird eingelesen
    fprintf(datei,",");
    fprintf(datei, "%f", dop_h); // Passende Dropoutrate zu Gewichten wird eingelesen
    fprintf(datei,",");

    for (x = 0; x < input_nodes; x++) {
        for (y = 0; y < hidden_nodes[0]; y++) {
            fprintf(datei, "%f", w[0][x][y]);
            fprintf(datei,",");
        }
    }
    for (int z = 1; z < amounthiddenlayers; z++) {
        for (x = 0; x < hidden_nodes[z - 1]; x++) {
            for (y = 0; y < hidden_nodes[z]; y++) {
                fprintf(datei, "%f", w[z][x][y]);
                fprintf(datei,",");
            }
        }
    }
    for (x = 0; x < hidden_nodes[amounthiddenlayers-1]; x++) {
        for (y = 0; y < output_nodes; y++) {
            fprintf(datei, "%f", w[amounthiddenlayers][x][y]);
            fprintf(datei,",");
        }
    }
    fclose(datei);
    printf("Speichervorgang abgeschlossen\n");

}



