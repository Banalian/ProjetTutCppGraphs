#include "Csommet.h"
#include <iostream>

int Csommet::idernierSommet = 0;

/**
 * @brief Constructeur par defaut
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
* @brief Constructeur de recopie
* @param Le sommet a recopier
*/
Csommet::Csommet(Csommet & SOMsommet)
{
	int iBoucle;
	
	iNumero = SOMsommet.iNumero;
	iNbrArcArrivant = SOMsommet.iNbrArcArrivant;
	iNbrArcSortant = SOMsommet.iNbrArcSortant;

	pARCtabArrivant = new Carc*[iNbrArcArrivant];
	if (pARCtabArrivant == nullptr) {
		throw Cexception(ErrNewMallocFailed);
	}
	pARCtabSortant = new Carc*[iNbrArcSortant];
	if (pARCtabSortant == nullptr) {
		throw Cexception(ErrNewMallocFailed);
	}



	for (iBoucle = 0; iBoucle < iNbrArcArrivant; iBoucle++)
	{
		pARCtabArrivant[iBoucle] = SOMsommet.pARCtabArrivant[iBoucle];
	}
	for (iBoucle = 0; iBoucle < iNbrArcSortant; iBoucle++)
	{
		pARCtabSortant[iBoucle] = SOMsommet.pARCtabSortant[iBoucle];
	}	
	idernierSommet = SOMsommet.idernierSommet;

}

/**
 * @brief Destructeur par defaut
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
 * @param Numero du sommet a relier
 */
void Csommet::SOMAddArcArrivant(int iDest)
{
	if (iDest == iNumero)
	{
		throw Cexception(ERRCantAddArc);
	}

	int iBoucle = 0;

	Carc** pArctabTemp = new Carc*[iNbrArcArrivant+1];

	if (pArctabTemp == nullptr) {
		throw Cexception(ErrNewMallocFailed);
	}

	for (iBoucle; iBoucle < (iNbrArcArrivant); iBoucle++) // On recopie dans case a case dans un tableau temporaire de taille +1
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
 * @param Numero du sommet a relier
 */
void Csommet::SOMAddArcSortant(int iDest)
{
	if (iDest == iNumero)
	{
		throw Cexception(ERRCantAddArc);
	}

	int iBoucle = 0;

	Carc** pArctabTemp = new Carc*[iNbrArcSortant + 1];
	if (pArctabTemp == nullptr) {
		throw Cexception(ErrNewMallocFailed);
	}


	for (iBoucle; iBoucle < (iNbrArcSortant); iBoucle++) // On recopie dans case a case dans un tableau temporaire de taille +1
	{
		pArctabTemp[iBoucle] = pARCtabSortant[iBoucle];
	}

	pArctabTemp[iNbrArcSortant] = new Carc(iDest);
	if (pArctabTemp[iNbrArcSortant] == nullptr) {
		throw Cexception(ErrNewMallocFailed);
	}
	delete[] pARCtabSortant;
	pARCtabSortant = pArctabTemp;

	iNbrArcSortant += 1;
}

/**
 * @brief Supprime un arc arrivant
 * @param Numero du sommet a delier
 */
void Csommet::SOMDeleteArcArrivant(int iDest)
{
	if (iNbrArcArrivant == 0)
	{
		throw Cexception(ERRNoMoreArc);
	}

	int iBoucle = 0;
	int iDecalage = 0;

	while(pARCtabArrivant[iBoucle]->ARCgetDest() != iDest)	//On parcourt la liste des arcs jusqu'a tomber sur celui a supprimer
	{
		iBoucle++;
	}
	delete pARCtabArrivant[iBoucle];
	pARCtabArrivant[iBoucle] = nullptr;
	iNbrArcArrivant -= 1;

	if (iNbrArcArrivant != 0)
	{
		Carc** pArctabTemp = new Carc*[iNbrArcArrivant];
		if (pArctabTemp == nullptr) {
			throw Cexception(ErrNewMallocFailed);
		}

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
 * @param Numero du sommet a delier
 */
void Csommet::SOMDeleteArcSortant(int iDest)
{
	if (iNbrArcSortant == 0)
	{
		throw Cexception(ERRNoMoreArc);
	}

	int iBoucle = 0;
	int iDecalage = 0;

	while (pARCtabSortant[iBoucle]->ARCgetDest() != iDest)	//On parcourt la liste des arcs jusqu'a tomber sur celui a supprimer
	{
		iBoucle++;
	}
	delete pARCtabSortant[iBoucle];
	pARCtabSortant[iBoucle] = nullptr;
	iNbrArcSortant -= 1;

	if (iNbrArcSortant != 0)
	{
		Carc** pArctabTemp = new Carc*[iNbrArcSortant];
		if (pArctabTemp == nullptr) {
			throw Cexception(ErrNewMallocFailed);
		}

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
 * @return Le numero du sommet
 */
int Csommet::SOMGetSomNum()
{
	return iNumero;
}

/**
* @brief Donne le nombre d'arcs arrivants
*/
int Csommet::SOMGetNbArcArrivant()
{
	return iNbrArcArrivant;
}

/**
* @brief Donne le nombre d'arcs sortants
*/
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
	std::cout << "\t Liste des arcs entrants : \n" ;
	for (iBoucle; iBoucle < iNbrArcArrivant; iBoucle++)
	{
		std::cout << "\t\t" << pARCtabArrivant[iBoucle]->ARCgetDest() << std::endl;
	}
	iBoucle = 0;
	std::cout << "\t Liste des arcs sortants : \n";
	for (iBoucle; iBoucle < iNbrArcSortant; iBoucle++)
	{
		std::cout << "\t\t" << pARCtabSortant[iBoucle]->ARCgetDest() << std::endl;
	}
}

/**
 * @brief Renvoie la destination de l'arc arrivant a la position iPos
 * @param position iPos
 * @return destination iDest
 */
int Csommet::SOMgetDestArrivant(int iPos)
{
	if (iPos >= iNbrArcArrivant)
	{
		throw Cexception(ERRPosOutOfRange);
	}
	return pARCtabArrivant[iPos]->ARCgetDest();
}

/**
 * @brief Renvoie la destination de l'arc sortant a la position iPos
 * @param position iPos
 * @return destination iDest
 */
int Csommet::SOMgetDestSortant(int iPos)
{
	if (iPos >= iNbrArcSortant)
	{
		throw Cexception(ERRPosOutOfRange);
	}
	return pARCtabSortant[iPos]->ARCgetDest();
}

/**
* @brief Permet d'inverser tout les arcs du sommet.
* Une simple inversion entre A et B permet d'atteindre cela.
*/
void Csommet::SOMInverserArcSom()
{

	Carc** pARCTemp;
	int iTemp;

	pARCTemp = pARCtabArrivant;
	iTemp = iNbrArcArrivant;

	pARCtabArrivant = pARCtabSortant;
	iNbrArcArrivant = iNbrArcSortant;

	pARCtabSortant = pARCTemp;
	iNbrArcSortant = iTemp;

	pARCTemp = nullptr;

}

Csommet& Csommet::operator=(Csommet& sommet)
{
	int iBoucle = 0;
	for (iBoucle; iBoucle < iNbrArcArrivant; iBoucle++)
	{
		delete pARCtabArrivant[iBoucle];
	}

	iBoucle = 0;

	for (iBoucle; iBoucle < iNbrArcSortant; iBoucle++)
	{
		delete pARCtabSortant[iBoucle];
	}

	iBoucle = 0;

	iNumero = sommet.iNumero;
	iNbrArcArrivant = sommet.iNbrArcArrivant;
	iNbrArcSortant = sommet.iNbrArcSortant;

	for (iBoucle = 0; iBoucle < iNbrArcArrivant; iBoucle++)
	{
		pARCtabArrivant[iBoucle] = sommet.pARCtabArrivant[iBoucle];
	}
	for (iBoucle = 0; iBoucle < iNbrArcSortant; iBoucle++)
	{
		pARCtabSortant[iBoucle] = sommet.pARCtabSortant[iBoucle];
	}
	idernierSommet = sommet.idernierSommet;
	return *this;
}



std::ostream & operator<<(std::ostream & out, Csommet & SOMelem)
{

	int iBoucle = 0;
	out << "Numero de sommet :" << SOMelem.SOMGetSomNum() << std::endl;
	out << "\t Liste des arcs entrants : \n";
	for (iBoucle; iBoucle < SOMelem.SOMGetNbArcArrivant(); iBoucle++)
	{
		out << "\t\t" << SOMelem.SOMgetDestArrivant(iBoucle) << std::endl;
	}
	iBoucle = 0;
	out << "\t Liste des arcs sortants : \n";
	for (iBoucle; iBoucle < SOMelem.SOMGetNbArcSortant(); iBoucle++)
	{
		out << "\t\t" << SOMelem.SOMgetDestSortant(iBoucle) << std::endl;
	}

	return out;
}
