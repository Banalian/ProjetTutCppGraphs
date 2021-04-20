#pragma once

#include "GraphTextFileParser.h"

/**
* @brief Cree un graph oriente a partir d'un nom de fichier/chemin vers un fichier
* @param cPath le chemin menant a ce fichier (exemple :  Graph/G1.txt)
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
Cgraphe* GraphTextFileParser(char* pcPath){
	std::fstream myFile(pcPath);



	if (myFile.is_open()) {


		try {
			char *line = new char[BUFFSIZE];



		}
		catch (Cexception e) {

			int iCodeErr = e.EXCLire_Code();
			switch (iCodeErr)
			{
			case 0:
				break;
			default:
				std::cout << "Erreur non repertoriee" << std::endl;
				break;
			}

			throw Cexception(ERRBadFormatFileGraph);
		}
	}
	else {
		throw Cexception(ERRFileNotOpen);
	}


	return nullptr;
}
