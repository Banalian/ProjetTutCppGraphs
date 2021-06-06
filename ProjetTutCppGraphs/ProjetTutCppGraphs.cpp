#pragma once
// ProjetTutCppGraphs.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

///template Doxygen
/**
 * @brief test push in the new branch
 * @param
 * @return.
 */

#include <iostream>
#include "Cgraphe.h"
#include "GraphTextFileParser.h"
#include "Kruskal.h"

int main(int argc, char*argv[])
{

	if (argc < 2) {
		std::cout << "Erreur :  pas de fichier transmis en parametre de la fonction" << std::endl;
		return -1;
	}

	if (argc > 2) {
		std::cout << "Erreur :  Trop de fichiers transmis en parametre de la fonction" << std::endl;
		return -1;
	}

	Cgraphe *pGRAGraphFile, *pGRAGraphFileInverse, *pGRAGraphArbreCovenant;

	try {
		pGRAGraphFile = GraphTextFileParser(argv[1]);


		std::cout << "--------------Affichage d'un graphe--------------" << std::endl << *pGRAGraphFile << std::endl;

		pGRAGraphFileInverse = new Cgraphe(*pGRAGraphFile);
		if (pGRAGraphFile == nullptr) {
			throw Cexception(ErrNewMallocFailed);
		}
		std::cout << "------------Inversion du graph-------------------" << std::endl;
		
		pGRAGraphFileInverse->GRAInverserGraph();

		std::cout << "--------------Affichage d'un graphe Inverse--------------" << std::endl << *pGRAGraphFileInverse << std::endl;

		Carc** testTab = pGRAGraphFile->GRAgetTabAllArcsCopy();
		int nbArcsTot = pGRAGraphFile->GRAgetNbAllArcs();

		std::cout << "--------------Affichage des arcs du graphe de base--------------" << std::endl << *pGRAGraphFileInverse << std::endl;
		for (int i = 0; i < nbArcsTot; i++) {
			std::cout	<< "ARC d'origine " << testTab[i]->ARCgetDepart() 
						<< " et de dest " << testTab[i]->ARCgetDest()
						<< " avec un poids de " << testTab[i]->ARCgetPoids() << std::endl;
		}


		pGRAGraphArbreCovenant = kruskal(pGRAGraphFile);


		std::cout << "--------------Affichage de l'arbre covenant de poids minimal--------------" << std::endl << *pGRAGraphArbreCovenant << std::endl;


	}
	catch (Cexception e) {
		int iCodeErr = e.EXCLire_Code();
		switch (iCodeErr)
		{
		case ERRFileNotOpen:
			std::cout << "Erreur : Le fichier n'a pas pu etre ouvert " << std::endl;
			break;
		case ERRBadFormatFileGraph:
			std::cout << "Erreur : Le fichier n'avait pas un format correct" << std::endl;
			break;
		case ErrNewMallocFailed:
			std::cout << "Erreur : Une operation malloc ou new a echouee, arret du programme" << std::endl;
			break;
		case ERRSumAlreadyExist:
			std::cout << "Erreur : Le sommet qui devait etre ajoute existe deja " << std::endl;
			break;
		case ERRSumDoesntExist:
			std::cout << "Erreur : Un sommet non existant a essaye d'etre supprime " << std::endl;
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
		default:
			std::cout << "Erreur non repertoriee" << std::endl;
			break;
		}

	}

	

}
