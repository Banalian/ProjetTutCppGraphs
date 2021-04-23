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

		pGRAGraphFile->GRAAfficherGraph();

		pGRAGraphFileInverse = new Cgraphe(*pGRAGraphFile);
		std::cout << "Inversion du graph" << std::endl;
		
		pGRAGraphFileInverse->GRAInverserGraph();

		pGRAGraphFileInverse->GRAAfficherGraph();

	}
	catch (Cexception e) {
		int iCodeErr = e.EXCLire_Code();
		switch (iCodeErr)
		{
		case ERRBadFormatFileGraph:
			std::cout << "Erreur : Le fichier n'avait pas un format correct ou " << std::endl;
			break;
		default:
			std::cout << "Erreur non repertoriee" << std::endl;
			break;
		}

	}
	

}
