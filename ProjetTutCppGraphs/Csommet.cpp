#include "Csommet.h"
#include <iostream>
int Csommet::idernierSommet = 0;

/**
 * @brief Constructeur par défaut
 */
Csommet::Csommet()
{
	iNumero = idernierSommet + 1;
	idernierSommet += 1;

	iNbrArcArrivant = 0;
	iNbrArcSortant = 0;

	pARCtabArrivant = nullptr;
	pARCtabArrivant = nullptr;
}

/**
* @brief Constructeur de confort
* @param Le numero a attribuer au sommet
*/
Csommet::Csommet(int iNum)
{
	iNumero = iNum;
	idernierSommet = iNum;

	iNbrArcArrivant = 0;
	iNbrArcSortant = 0;

	pARCtabArrivant = nullptr;
	pARCtabSortant = nullptr;
}

/**
 * @brief Destructeur par défaut
 */
Csommet::~Csommet()
{
	int iBoucle = 0;
	for (iBoucle; iBoucle <iNbrArcArrivant; iBoucle++)
	{
		delete pARCtabArrivant[iBoucle];
	}

	iBoucle = 0;
	
	for (iBoucle; iBoucle < iNbrArcSortant; iBoucle++)
	{
		delete pARCtabSortant[iBoucle];
	}
	delete pARCtabArrivant;
	delete pARCtabSortant;
}

/**
 * @brief Ajoute un arc arrivant
 * @param Pointeur vers l'arc a ajouter
 */
void Csommet::SOMAddArcArrivant(int iDest)
{
	int iBoucle = 0;

	Carc** pArctabTemp = new Carc*[iNbrArcArrivant+1];
	for (iBoucle; iBoucle < (iNbrArcArrivant); iBoucle++) // On recopie dans case à case dans un tableau temporaire de taille +1
	{
		pArctabTemp[iBoucle] = pARCtabArrivant[iBoucle];
	}

	pArctabTemp[iNbrArcArrivant] = new Carc(iDest);
	delete[] pARCtabArrivant;
	pARCtabArrivant = pArctabTemp;

	iNbrArcArrivant += 1;

}

/**
 * @brief Ajoute un arc sortant
 * @param Pointeur vers l'arc a ajouter
 */
void Csommet::SOMAddArcSortant(int iDest)
{
	int iBoucle = 0;

	Carc** pArctabTemp = new Carc*[iNbrArcSortant + 1];
	for (iBoucle; iBoucle < (iNbrArcSortant); iBoucle++) // On recopie dans case à case dans un tableau temporaire de taille +1
	{
		pArctabTemp[iBoucle] = pARCtabSortant[iBoucle];
	}

	pArctabTemp[iNbrArcSortant] = new Carc(iDest);
	delete[] pARCtabSortant;
	pARCtabSortant = pArctabTemp;

	iNbrArcSortant += 1;
}

/**
 * @brief Supprime un arc arrivant
 * @param Pointeur vers l'arc à supprimer
 */
void Csommet::SOMDeleteArcArrivant(int iDest)
{
	int iBoucle = 0;
	int iDecalage = 0;

	while(pARCtabArrivant[iBoucle]->ARCgetDest() != iDest)	//On parcourt la liste des arcs jusqu'à tomber sur celui à supprimer
	{
		iBoucle++;
	}
	delete pARCtabArrivant[iBoucle];
	pARCtabArrivant[iBoucle] = nullptr;
	iNbrArcArrivant -= 1;

	if (iNbrArcArrivant != 0)
	{
		Carc** pArctabTemp = new Carc*[iNbrArcArrivant];
		iBoucle = 0;
		for (iBoucle; iBoucle <= iNbrArcArrivant; iBoucle++)	//On recopie la liste en supprimant la case vide
		{
			if (pARCtabArrivant[iBoucle] == nullptr)
			{
				iDecalage++;
			}
			pArctabTemp[iBoucle] = pARCtabArrivant[iBoucle + iDecalage];
		}

		delete[] pARCtabArrivant;
		pARCtabArrivant = pArctabTemp;
	}
	else
	{
		delete[] pARCtabArrivant;
		pARCtabArrivant = nullptr;
	}
}

/**
 * @brief Supprime un arc sortant
 * @param Pointeur vers l'arc a supprimer
 */
void Csommet::SOMDeleteArcSortant(int iDest)
{
	int iBoucle = 0;
	int iDecalage = 0;

	while (pARCtabSortant[iBoucle]->ARCgetDest() != iDest)	//On parcourt la liste des arcs jusqu'à tomber sur celui à supprimer
	{
		iBoucle++;
	}
	delete pARCtabSortant[iBoucle];
	pARCtabSortant[iBoucle] = nullptr;
	iNbrArcSortant -= 1;

	if (iNbrArcSortant != 0)
	{
		Carc** pArctabTemp = new Carc*[iNbrArcSortant];
		iBoucle = 0;
		for (iBoucle; iBoucle <= iNbrArcSortant; iBoucle++)	//On recopie la liste en supprimant la case vide
		{
			if (pARCtabSortant[iBoucle] == nullptr)
			{
				iDecalage++;
			}
			pArctabTemp[iBoucle] = pARCtabSortant[iBoucle + iDecalage];
		}

		delete[] pARCtabSortant;
		pARCtabSortant = pArctabTemp;
	}
	else
	{
		delete[] pARCtabSortant;
		pARCtabSortant = nullptr;
	}
}


/**
 * @brief Affiche le numero du sommet
 * @return Le numéro du sommet
 */
int Csommet::SOMGetSomNum()
{
	return iNumero;
}

int Csommet::SOMGetNbArcArrivant()
{
	return iNbrArcArrivant;
}

int Csommet::SOMGetNbArcSortant()
{
	return iNbrArcSortant;
}

/**
 * @brief Affiche le numero du dernier sommet cree
 * @return Le numero du dernier sommet cree
 */
int Csommet::SOMGetdernierSommet()
{
	return idernierSommet;
}

/**
 * @brief Affiche toutes les informations du sommet
 * @return Numero du sommet, liste des arcs entrants et liste des arcs sortants
 */
void Csommet::SOMAfficherSommet()
{
	int iBoucle = 0;
	std::cout << "Numero de sommet :" << iNumero << std::endl;
	std::cout << "/t Liste des arcs entrants : \n" ;
	for (iBoucle; iBoucle < iNbrArcArrivant; iBoucle++)
	{
		std::cout << "/t/t" << pARCtabArrivant[iBoucle]->ARCgetDest() << std::endl;
	}
	iBoucle = 0;
	std::cout << "/t Liste des arcs sortants : \n";
	for (iBoucle; iBoucle < iNbrArcSortant; iBoucle++)
	{
		std::cout << "/t/t" << pARCtabSortant[iBoucle]->ARCgetDest() << std::endl;
	}
}

/**
 * @brief Renvoie la destination de l'arc arrivant à la position iPos
 * @param position iPos
 * @return destination iDest
 */
int Csommet::SOMgetDestArrivant(int iPos)
{
	return pARCtabArrivant[iPos]->ARCgetDest();
}

/**
 * @brief Renvoie la destination de l'arc sortant à la position iPos
 * @param position iPos
 * @return destination iDest
 */
int Csommet::SOMgetDestSortant(int iPos)
{
	return pARCtabSortant[iPos]->ARCgetDest();
}

/**
* @brief Permet d'inverser tout les arcs du sommet.
* Une simple inversion entre A et B permet d'atteindre cela.
*/
void Csommet::SOMInverserArcSom()
{

	Carc** pARCTemp;

	pARCTemp = pARCtabArrivant;

	pARCtabArrivant = pARCtabSortant;

	pARCtabSortant = pARCTemp;

}
