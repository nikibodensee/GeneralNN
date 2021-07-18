/*----------------------------------------------------------------------
 *  File: 2.0. readinp.c
 *  Project: GeneralNN_GUI_1.0
 *  Version: V1.0
 *  Created on: 07.11.2020, 16:22:29
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

#include "main.h"

int	  ov;
extern int input_nodes;
extern int output_nodes;
extern int mustz;
extern float zint;
extern float z[input_nodesmax][mustzmax];
extern float om[output_nodesmax][mustzmax];
extern char *filenameinput;

void readinp() {

    FILE *datei; 	// Pointer um mit File umzugehen
    char *filename;	// Variable, um filename zu ändern
    int x, y, m;

    //-- Öffnen der richtigen Datei (Lerndaten oder Testdaten)
    filename = filenameinput;
    datei = fopen(filename, "r");

    //-- Auslesen beginnt:
    if (datei != NULL) {

//		for (m = 0; m < mustz; m++) {
//
//			//-- Reines Auslesen der Werte:
//			for (y = 0; y < input_nodes; y++) {
//				fscanf(datei, "%f", &zint);			// Wert Variable zuordnen
//				z[y][m] = zint;	// Werte bis 255 umwandeln in Werte zwischen 0.01 & 1
//				fgetc(datei);								// Übersprung Komma
////				printf("%f\n",zint);
//			}
//
//
//			//-- Umwandlung von ow zu ou:
//			for (x = 0; x < output_nodes; x++) {
//				float buf;
//				fscanf(datei, "%f", &buf);// jeweils 1. Wert nach sizew.: Output-Wert
//					om[x][m] = buf;				// Aktivierung für Output-Unit 1
//					fgetc(datei);								// Übersprung Komma
////								printf("%d om[%d][%d]: %f\n", output_nodes, x, m, om[x][m]);
//			}
//
//		}
//		printf("readinp abgeschlossen\n\n");

        for (m = 0; m < mustz; m++) {

            fscanf(datei, "%d", &ov);// jeweils 1. Wert nach sizew.: Output-Werte

            //-- Umwandlung von ow zu ou:
            for (x = 0; x < output_nodes; x++) {
                if ((x) == ov) {	// Sobald Muster-Nr. = Output-Unit-Nr. -- Aktivierung mit 1
                    om[x][m] = 1;				// Aktivierung für Output-Unit 1
                } else {// Falls Muster-Nr. != Output-Unit-Nr. -- Aktivierung mit 0
                    om[x][m] = 0;				// Aktivierung für Output-Unit 0
                }
                //				printf("%d om[%d][%d]: %f\n", output_nodes, x, m, om[x][m]);
            }

            fgetc(datei);									// Übersprung Komma

            //-- Reines Auslesen der Werte:
            for (y = 0; y < input_nodes; y++) {
                fscanf(datei, "%f", &zint);			// Wert Variable zuordnen
                z[y][m] = (zint / 255);	// Werte bis 255 umwandeln in Werte zwischen 0.01 & 1
                fgetc(datei);								// Übersprung Komma
            }
        }
        printf("readinp abgeschlossen\n\n");


    } else {
        printf("Datei konnte nicht geöffnet werden");
    }

}




