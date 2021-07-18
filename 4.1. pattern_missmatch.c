/*----------------------------------------------------------------------
*  File: 4.1. pattern_missmatch.c
*  Project: GeneralNN_GUI_1.0
*  Version: V1.0
*  Created on: 09.11.2020, 17:16:38
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
extern int output_nodes;
extern int mustz;
extern float act[layermax][hidden_nodesmax];
extern int oerg[mustzmax];
extern int   oergsoll[mustzmax];
extern int	ov[mustzmax];
extern int erg[mustzmax];
extern float perg[mustzmax];
extern int ser[mustzmax];
extern int   mdt[output_nodesmax];
extern int vork[output_nodesmax];
extern float om[output_nodesmax][mustzmax];			// Aktivierung der Output-Units

void pattern_missmatch (int m){

    int x,y;		// Laufvariablen
    float mx1,mx2;	// Maximale Aktivität einer Output-Unit
    int k;		// Treffer / kein Treffer

    erg[m] = 0;

    //-- Ergebnis
    mx1 = 0;
    mx2 = 0;
    for (x = 0; x < 50; x++) {
        for (y = 0; y < 12; y++) {
            if (act[amounthiddenlayers][(y * 50) + x] > mx1) {
                mx1 = act[amounthiddenlayers][(y * 50) + x]; // Ermittlung der Aktivsten Output-Unit
                oerg[m] = (y * 50) + x;
//				printf("%d\n",(y*50) + y);
            }
            if (om[(y * 50) + x][m] > mx2) {
                mx2 = om[(y * 50) + x][m]; // Ermittlung der Aktivsten Output-Unit
                oergsoll[m] = (y * 50) + x;
                //				printf("%d\n",(y*50) + y);
            }
        }

        for (y = 0; y < 12; y++) {
            //-- Vergleich Sollwert, Istwert
            if (act[amounthiddenlayers][(y * 50) + x] == om[(y * 50) + x][m]) {
                k = 1;							// Treffer
                break;
            } else {
                k = 0;							// Kein Treffer
            }
        }
//		 printf("%d\n",k);
        erg[m] += k;
    }

    //-- Trefferquote
    float per = (float) erg[m] / (float) 50;
    if (m == 0)
        perg[m] = per;
    else {
        perg[m] = ((perg[m - 1] * (m - 1)) + per) / (float) m;
//		printf("perg[%d] = ((%f * %d) + %f)/%d = %f\n", m, perg[m - 1], m - 1,
//				per, m, perg[m]);
//		if (buf > 0)
//			perg[m] = buf / (m);
//		else
//			perg[m] = 0;
    }
//	printf("per = %f perg[m] = %f m = %d\n", per, perg[m], m);
}







