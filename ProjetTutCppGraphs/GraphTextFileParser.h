#pragma once

//cette ligne sert a desactive les erreurs pour les commandes comme strtok()
//car elles sont depreciees car non thread safe par exemple, mais ici etant donne que l'on est en mono-thread pas de soucis
#pragma warning(disable : 4996)

#include <fstream>
#include <iostream>
#include <cstring>
#include "Cexception.h"
#include "Cgraphe.h"
#define BUFFSIZE 2048


#define ERRFileNotOpen 200
#define ERRBadFormatLineGraph 201
#define ERRBadFormatFileGraph 202
#define ERREmptyFile 203
#define ERRBadSumNumber 204
#define ERRBadArcNumber 205

/**
* @brief Cree un graph oriente a partir d'un nom de fichier/chemin vers un fichier
* @param cPath le chemin menant a ce fichier (exemple :  Graph/G1.txt)
* @param bHasPoids boolean pour choisir si le fichier a des poids ou non
* @return un graphe respectant les specification du fichier
*
* Precondition :  Le fichier doit respecter un format tres specifique, comme dit dans le sujet de ce projet.
* Si le fichier est sous un format different, le programme est susceptible de planter ou d'avoir un comportement non defini.
*
*
* Format du fichier attendu :
* NBSommets=<Nombre_de_Sommets_du_graphe>
* NBArcs=< Nombre_d_arcs_du_graphe >
* Sommets=[
* Numero=<Numero_sommet >
* Numero=<Numero_sommet>
* …
* Numero=<Numero_sommet>
* ]
* Arcs=[
* Debut=<Sommet_depart_arc>, Fin=<Sommet_arrivee_arc>
* Debut=<Sommet_depart_arc>, Fin=<Sommet_arrivee_arc>
* …
* Debut=<Sommet_depart_arc>, Fin=<Sommet_arrivee_arc>
* ]
* ----------------------------------------------------------------------
* Exemple concret :
* NBSommets=3
* NBArcs=3
* Sommets=[
* Numero=1
* Numero=2
* Numero=3
* ]
* Arcs=[
* Debut=1, Fin=2
* Debut=2, Fin=3
* Debut=3, Fin=1
* ]
*/
Cgraphe* GraphTextFileParser(char* pcPath, bool bHasPoids = false);

/**
* @brief Fonction pour passer a la prochaine ligne non vide du fichier. Si une fin de document est trouvee, lance une exception
* @param myFile pointeur vers un objet pour lire un fichier
* @param line la variable dans laquelle sera stockee la ligne
*/
inline void getNextLine(std::fstream* myFile, char* line);
