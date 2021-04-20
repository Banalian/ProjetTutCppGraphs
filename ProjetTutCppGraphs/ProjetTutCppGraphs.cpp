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
    std::cout << "Hello World!\n";//test push

	Cgraphe *testGraph;

	try {
		testGraph = GraphTextFileParser(argv[1]);
	}
	catch (Cexception e) {
		int iCodeErr = e.EXCLire_Code();
		switch (iCodeErr)
		{
		case ERRBadFormatFileGraph:
			std::cout << "Erreur : Le fichier n'avait pas un format correct" << std::endl;
			break;
		default:
			std::cout << "Erreur non repertoriee" << std::endl;
			break;
		}

	}
	

}
