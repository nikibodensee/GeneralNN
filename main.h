/*----------------------------------------------------------------------
*  File: main.h
*  Project: GeneralNN_v1.0
*  Version: V1.0
*  Created on: 09.11.2020, 22:35:46
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

//#ifndef GENERALNN_V1_0_MAIN_H
//#define GENERALNN_V1_0_MAIN_H
//
//#endif //GENERALNN_V1_0_MAIN_H




#ifndef MAIN_H_
#define MAIN_H_

//-- Hyperparameter:
#define mustzmax 60000								// Anzahl der abgespeicherten Muster
#define epochemax 500								// Anzahl der Lerndurchläufe

//-- Netzcharakteristiken:
#define layermax 10                                 // Anzahl an maximalen Layers
#define input_nodesmax 3000						// Länge jedes Musters, Anzahl Input-Units
#define hidden_nodesmax 1000						// Anzahl der maximalen Hidden-Units pro Schicht
#define output_nodesmax 1000						// Anzahl der Output-Units im Netz, folglich Anzahl an verschiedenen Wörtern


#endif /* MAIN_H_ */

