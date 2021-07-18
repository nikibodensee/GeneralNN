/*----------------------------------------------------------------------
*  File: 0.0. main.c
*  Project: GeneralNN_GUI_1.0
*  Version: V1.0
*  Created on: 07.11.2020, 15:23:20
*  Author: N. Kornel
*  Company: Nensys
*
*  Copyright © 2020 by Nensys GbR
*  Use of this file and all called functions requires a license.
*  Further distribution in any form is prohibited.
*
*  Description:
*  A General Neural Network for Data Analysis and Nensys Java Application
*  Interface
*
*---------------------------------------------------------------------*/
#include <stdio.h>
#include <time.h>

#include "main.h"

////-- Hyperparameter:
//#define mustzmax 60000							// Anzahl der abgespeicherten Muster
//#define epochemax 500								// Anzahl der Lerndurchläufe
//
////-- Netzcharakteristiken:
//#define layermax 10                                 // Anzahl an maximalen Layers
//#define input_nodesmax 3000						// Länge jedes Musters, Anzahl Input-Units
//#define hidden_nodesmax 1000						// Anzahl der maximalen Hidden-Units pro Schicht
//#define output_nodesmax 100						// Anzahl der Output-Units im Netz, folglich Anzahl an verschiedenen Wörtern

int choice;											// Auswahl Verfahren: 1 = neu lernen, 2 = weiter lernen, 3 = query

int amounthiddenlayers;
int input_nodes;									// Länge jedes Wortes, Anzahl Input-Units (39*39 bei lerndaten Andi)(39*37 bei selbst erstellten Lerndaten)
int hidden_nodes[layermax];						// Anzahl der Hidden-Units pro Einheit
int output_nodes;				      			    // Anzahl der Output-Units im Netz, folglich Anzahl an verschiedenen Wörtern

int epoche;											// Anzahl der Lerndurchläufe
int mustz;											// Anzahl der abgespeicherten Wortsequenzen
float learnr;          					            // Lernrate
float dop_i;										// Dropout probability Input-Layer (< dop_i = 0)
float dop_h;										// Dropout probability Hidden-Layer (< dop_h = 0)
char *filenameinput;
char *filenameweight;

//-- Dropoutverfahren:
float doprop[2];								    // Ausgelesene dropout probabilities zu Gewichten (0: dop_i, 1: dop_h)

//-- Input-Variablen:
int   zint; 										// Input-Werte
float z[input_nodesmax][mustzmax];				// Input-Werte zwischen 0 & 1: zint / 255
float dopz[input_nodesmax][mustzmax];			// Übertrag z[][], um bei Dropout Werte auf 0 zu setzen

//-- Gewichte:
float w[layermax][input_nodesmax][hidden_nodesmax];	// Gewichte zwischen der Input und ersten Hidden-Schicht

//-- Aktivierungswerte:
float act[layermax][hidden_nodesmax]; 					// Weitergabe der Units in der ersten an die zweite Hidden Schicht (s1 nach Sigmoidfkt.)
float dopact[layermax][hidden_nodesmax];				// Übertrag act1[], um bei Dropout Werte auf 0 zu setzen

//-- Output:
int	  ov;								// Array Output-Werte
int   oerg[mustzmax];								// Tatsächliches Ergebnis
int   oergsoll[mustzmax];								// Tatsächliches Ergebnis
float om[output_nodesmax][mustzmax];			// Aktivierung der Output-Units
float oe[output_nodesmax];						// Differenz zwischen tatsächlichem und ermitteltem Wert der Output-Units

//-- Fehlerwerte:
float er[layermax][hidden_nodesmax][hidden_nodesmax];		// Einzelerror der Gewichte an der Hidden-Schicht
float her[layermax][hidden_nodesmax];						// Summenerror eines Units an der Hidden-Schicht
float soe[mustzmax];								// Summenerror Ouputdifferenz oe pro Muster
int   ser[mustzmax];								// Gesamtfehler bis Durchgang m
float serr[epochemax+1];								// Netzerror aufsummiert (Output-Werte) pro Epoche

//-- Ergebnisbewertung:
int   erg[mustzmax];				// Gesamttreffer bis Durchgang m
float perg[mustzmax];				// Trefferquote
int vork[output_nodesmax];							// Vorkommen jedes Musters
int   mdt[output_nodesmax];						// fehlerhaft erkannt Muster

//-- Unterprogramme:
void weightinit ();
void readweights();
void readinp ();

void query_inputlayer ();
void query_inputlayerq ();
void query_layerX ();
void query_layerXq ();
void query_outputlayer ();
void query_outputlayerq ();

void pattern_missmatch();
void teach();
void teach_pattern_missmatch();
void saveweights();
//void query_pattern_missmatch();
//void einzelergebnis();


void weightinit();

int main (
//		int argumenten_zaehler, char *argumenten_vektor[]
){

    // FOLLOWING ONLY UNCOMMENT IF PROGRAM IS CALLED BY ANOTHER PROGRAM

//	choice = atoi(argumenten_vektor[1]);							// Auswahl Verfahren: 1 = neu lernen, 2 = weiter lernen, 3 = query
//
//	input_nodes = atoi(argumenten_vektor[2]);						// Länge jedes Wortes, Anzahl Input-Units (39*39 bei lerndaten Andi)(39*37 bei selbst erstellten Lerndaten)
//	amounthiddenlayers = atoi(argumenten_vektor[3]);
//	int count1 = 0;
//	for(int a = 4; a < amounthiddenlayers + 4; a++) {
//	hidden_nodes[count1] = atoi(argumenten_vektor[a]);						// Anzahl der Hidden-Units in der ersten Schicht
//	count1++;}
//	output_nodes = atoi(argumenten_vektor[argumenten_zaehler-7]);				        // Anzahl der Output-Units im Netz, folglich Anzahl an verschiedenen Wörtern
//
//	epoche = atoi(argumenten_vektor[argumenten_zaehler-6]);							// Anzahl der Lerndurchläufe
//	mustz = atoi(argumenten_vektor[argumenten_zaehler-5]);								// Anzahl der abgespeicherten Wortsequenzen
//	learnr = atof(argumenten_vektor[argumenten_zaehler-4]);                            // Lernrate
//	dop_i = atof(argumenten_vektor[argumenten_zaehler-3]);						        // Dropout probability Input-Layer (< dop_i = 0)
//	dop_h = atof(argumenten_vektor[argumenten_zaehler-2]);					        // Dropout probability Hidden-Layer (< dop_h = 0)
//	filenameinput = argumenten_vektor[argumenten_zaehler-1];
//	filenameweight = argumenten_vektor[argumenten_zaehler];

    choice = 1;	// Auswahl Verfahren: 1 = neu lernen, 2 = weiter lernen, 3 = query

    input_nodes = 1521;        // NUR FÜR ISI-PROJEKT: Länge jedes Wortes, Anzahl Input-Units (39*39 bei lerndaten Andi)(39*37 bei selbst erstellten Lerndaten)
    amounthiddenlayers = 2;
    hidden_nodes[0] = 500;	 // Anzahl der Hidden-Units in der ersten Schicht
    hidden_nodes[1] = 100;
//	hidden_nodes[2] = 700;
//	hidden_nodes[3] = 650;
//	hidden_nodes[4] = 600;
    output_nodes = 36;        // Anzahl der Output-Units im Netz, folglich Anzahl an verschiedenen Wörtern

    epoche = 10;							// Anzahl der Lerndurchläufe
    mustz = 100;					// Anzahl der abgespeicherten Wortsequenzen
    learnr = 0.1;                            // Lernrate
    dop_i = 0;					// Dropout probability Input-Layer (< dop_i = 0)
    dop_h = 0;				// Dropout probability Hidden-Layer (< dop_h = 0)
    filenameinput =
            "isi_lerndaten_17k_mfcc_39x39.csv";
    filenameweight =
            "NensysWeights1.0.txt";


    int e; 		// Laufvariable Epochen
    int m;		// Laufvariable Wörter

    printf("Hallo, choice = %d\n", choice);

    //-- Initlialisierung der Gewichte
    if (choice == 1) {
        weightinit();
    }
        //-- Gewichte werden eingelesen:
    else if (choice != 1) {
        readweights();
    }

    //-- Daten einlesen, Input-Layer:
    readinp();

    if (choice == 1 || choice == 2) {
        //-- Anfangsfehler berechnen
        for (m = 0; m < mustz; m++) {
            e = 0;
            query_inputlayerq(m);
            for (int h = 1; h < amounthiddenlayers; h++) {
                query_layerXq(h);
            }
            query_outputlayerq(m, e);
//			printf("%d\n",m);
        }

        printf("Lernen beginnt\n");

        //-- Lernen des Netzes beginnt
        for (e = 1; e <= epoche; e++) {
//			//-- Werte werden zurückgesetzt:
//			for (int i = 0; i < output_nodes; i++) {
//				mdt[i] = 0;
//				vork[i] = 0;
//			}

            clock_t t;
            t = clock();
            //-- Muster werden einzeln gelernt:
            for (m = 0; m < mustz; m++) {
                query_inputlayer(m);
                for (int h = 1; h < amounthiddenlayers; h++) {
                    query_layerX(h);
                }
                query_outputlayer(m, e);
                pattern_missmatch(m);
                teach(m);
//				printf("erg[%d]: %d -> %f\n", m, erg[m], perg[m]);
            }
            t = clock() - t;
            double time_taken = ((double)t)/CLOCKS_PER_SEC;
            printf("Error %f  Time %f\n",serr[e],time_taken);

        }
        saveweights();
    }

    if (choice == 3) {

        //-- Werte werden zurückgesetzt:
        for (int i = 0; i < output_nodes; i++) {
            mdt[i] = 0;
            vork[i] = 0;
        }
        e = 1;

        for (m = 0; m < mustz; m++) {
            query_inputlayerq(m);
            for (int h = 1; h < amounthiddenlayers; h++) {
                query_layerXq(h);
            }
            query_outputlayerq(m, e);
        }
    }
    return 0;
}

