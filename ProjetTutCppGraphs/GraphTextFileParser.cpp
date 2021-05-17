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
	int iBoucle, nbSommets, nbArcs, numSom, numArcDepart, numArcArrivee;
	char *buf, *line;
	Cgraphe *pGRAtemp = nullptr;

	line = new char[BUFFSIZE];
	if (line == nullptr) {
		throw Cexception(ErrNewMallocFailed);
	}

	if (myFile.is_open()) {

		

		try {
			
			std::cout << "--------------Creation d'un graphe a partir d'un fichier--------------" << std::endl;

			//Recuperation du nombre de sommets puis d'arcs
			getNextLine(&myFile, line);


			strtok(line, "=");
			buf = strtok(NULL, "=");
			nbSommets = atoi(buf);
			std::cout << "VAR nbSommets = "<< nbSommets << std::endl;

			getNextLine(&myFile, line);

			strtok(line, "=");
			buf = strtok(NULL, "=");
			nbArcs = atoi(buf);
			std::cout << "VAR nbArcs = "<< nbArcs << std::endl;

			getNextLine(&myFile, line);


			//Recuperation des numeros de sommet et ajout dans le graph
			if (strcmp(line, "Sommets=[")) {
				throw Cexception(ERRBadFormatLineGraph);
			}

			pGRAtemp = new Cgraphe();
			if (pGRAtemp == nullptr) {
				throw Cexception(ErrNewMallocFailed);
			}
				
			for (iBoucle = 0; iBoucle < nbSommets; iBoucle++) {
				getNextLine(&myFile, line);
				if (!strcmp(line, "]")) {
					throw Cexception(ERRBadSumNumber);
				}
				
				strtok(line, "=");
				buf = strtok(NULL, "=");
				numSom = atoi(buf);
				pGRAtemp->GRAAddSommet(numSom);

				std::cout << "Sommet "<< iBoucle << "VAR nbSom = "<< numSom <<std::endl;
				
				
			}
			
			getNextLine(&myFile, line);
			if (strcmp(line, "]")) {
				throw Cexception(ERRBadSumNumber);
			}


			//Recuperation des arcs et ajout dans le graph
			getNextLine(&myFile, line);
			if (strcmp(line, "Arcs=[")) {
				throw Cexception(ERRBadFormatLineGraph);
			}


			for (iBoucle = 0; iBoucle < nbArcs; iBoucle++) {
				getNextLine(&myFile, line);
				if (!strcmp(line, "]")) {
					throw Cexception(ERRBadArcNumber);
				}

				strtok(line, "=");
				buf = strtok(NULL, "=");
				numArcDepart = atoi(buf);
				buf = strtok(NULL, "=");
				numArcArrivee = atoi(buf);
				pGRAtemp->GRAAddArc(numArcDepart, numArcArrivee);

				std::cout << "Arc " << iBoucle << "VAR numArcDepart = "<< numArcDepart << " AND numArcArrivee = " << numArcArrivee <<std::endl;



			}

			getNextLine(&myFile, line);
			if (strcmp(line, "]")) {
				throw Cexception(ERRBadArcNumber);
			}



		}
		catch (Cexception e) {

			int iCodeErr = e.EXCLire_Code();
			switch (iCodeErr)
			{
			case ERREmptyFile:
				std::cout << "Erreur : Fichier Vide ou fin de fichier atteint trop tot" << std::endl;
				break;
			case ERRBadFormatLineGraph:
				std::cout << "Erreur : Format du fichier nom respecte (verifiez la convention d'ecriture du fichier" << std::endl;
				break;
			case ERRBadSumNumber:
				std::cout << "Erreur : Le Nombre de sommets donnee est different de ce que trouve le parser" << std::endl;
				break;
			case ERRBadArcNumber:
				std::cout << "Erreur : Le Nombre d'arcs donnee est different de ce que trouve le parser" << std::endl;
				break;
			case ERRSumAlreadyExist:
				std::cout << "Erreur : un des sommets a ete nomme deux fois dans le fichier" << std::endl;
				break;
			case ERRSumDoesntExist:
				std::cout << "Erreur : un des sommets nomme dans un arc n'existe pas et n'a pas ete nomme dans le fichier" << std::endl;
				break;
			case ERRCantAddArc:
				std::cout << "Erreur : un arc pointant sur lui meme ne peut pas etre ajoute " << std::endl;
				break;
			case ERRArcAlreadyExists:
				std::cout << "Erreur : un arc deja existant a essaye d'etre ajoute " << std::endl;
				break;
			case ERRSomAsSameNumAsLastSum:
				std::cout << "Erreur : un sommet ne peut etre ajoute s'il a deja ete cree avant " << std::endl;
				break;
			case ErrNewMallocFailed:
				std::cout << "Erreur : echec de l'operateur new" << std::endl;
				break;
			default:
				std::cout << "Erreur non repertoriee" << std::endl;
				break;
			}

			if (line) {
				delete line;
			}
			myFile.close();
			if (pGRAtemp) {
				delete pGRAtemp;
			}

			throw Cexception(ERRBadFormatFileGraph);
		}
	}
	else {
		throw Cexception(ERRFileNotOpen);
	}

	std::cout << "--------Fin de la Creation d'un graphe a partir d'un fichier----------" << std::endl;
	return pGRAtemp;
}


/**
* @brief Fonction pour passer a la prochaine ligne non vide du fichier. Si une fin de document est trouvee, lance une exception
* @param myFile pointeur vers un objet pour lire un fichier
* @param line la variable dans laquelle sera stockee la ligne
*/
inline void getNextLine(std::fstream* myFile, char *line)
{
	do {
		myFile->getline(line, BUFFSIZE);
		if (line == nullptr) {
			throw Cexception(ERREmptyFile);
		}
	} while (!strcmp(line, ""));
}
