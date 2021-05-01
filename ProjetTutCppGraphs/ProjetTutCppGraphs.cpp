// ProjetTutCppGraphs.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

///template Doxygen
/**
 * @brief
 * @param
 * @return.
 */

#include <iostream>
#include "Cgraphe.h"
#include "GraphTextFileParser.h"

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

	Cgraphe *pGRAGraphFile, *pGRAGraphFileInverse;

	try {
		pGRAGraphFile = GraphTextFileParser(argv[1]);

		std::cout << *pGRAGraphFile << std::endl;

		pGRAGraphFileInverse = new Cgraphe(*pGRAGraphFile);
		if (pGRAGraphFile == nullptr) {
			throw Cexception(ErrNewMallocFailed);
		}
		std::cout << "Inversion du graph" << std::endl;
		
		pGRAGraphFileInverse->GRAInverserGraph();

		std::cout << *pGRAGraphFileInverse << std::endl;
;

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
		default:
			std::cout << "Erreur non repertoriee" << std::endl;
			break;
		}

	}

	

}
