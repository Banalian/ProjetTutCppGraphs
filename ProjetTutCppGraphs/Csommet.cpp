#include "Csommet.h"
#include <iostream>

int Csommet::iSOMDernierSommet = 0;

/**
 * @brief Constructeur par defaut
 */
Csommet::Csommet()
{
	iNumero = iSOMDernierSommet + 1;
	iSOMDernierSommet += 1;

	iSOMNbrArcArrivant = 0;
	iSOMNbrArcSortant = 0;

	pARCtabArrivant = nullptr;
	pARCtabArrivant = nullptr;
}

/**
* @brief Constructeur de confort
* @param iNum Le numero a attribuer au sommet
*/
Csommet::Csommet(int iNum)
{
	iNumero = iNum;
	//if (iNum == iSOMDernierSommet) {
	//	throw Cexception(ERRSomAsSameNumAsLastSum);
	//}
	iSOMDernierSommet = iNum;

	iSOMNbrArcArrivant = 0;
	iSOMNbrArcSortant = 0;

	pARCtabArrivant = nullptr;
	pARCtabSortant = nullptr;
}

/**
* @brief Constructeur de recopie
* @param SOMsommet Le sommet a recopier
*/
Csommet::Csommet(Csommet & SOMsommet)
{
	int iBoucle;
	
	iNumero = SOMsommet.iNumero;
	iSOMNbrArcArrivant = SOMsommet.iSOMNbrArcArrivant;
	iSOMNbrArcSortant = SOMsommet.iSOMNbrArcSortant;

	pARCtabArrivant = new Carc*[iSOMNbrArcArrivant];
	if (pARCtabArrivant == nullptr) {
		throw Cexception(ErrNewMallocFailed);
	}
	pARCtabSortant = new Carc*[iSOMNbrArcSortant];
	if (pARCtabSortant == nullptr) {
		throw Cexception(ErrNewMallocFailed);
	}



	for (iBoucle = 0; iBoucle < iSOMNbrArcArrivant; iBoucle++)
	{
		pARCtabArrivant[iBoucle] = new Carc (*SOMsommet.pARCtabArrivant[iBoucle]);
	}
	for (iBoucle = 0; iBoucle < iSOMNbrArcSortant; iBoucle++)
	{
		pARCtabSortant[iBoucle] = new Carc(*SOMsommet.pARCtabSortant[iBoucle]);
	}	
	iSOMDernierSommet = SOMsommet.iSOMDernierSommet;

}

/**
 * @brief Destructeur par defaut
 */
Csommet::~Csommet()
{
	int iBoucle = 0;
	for (iBoucle; iBoucle <iSOMNbrArcArrivant; iBoucle++)
	{
		delete pARCtabArrivant[iBoucle];
	}

	iBoucle = 0;
	
	for (iBoucle; iBoucle < iSOMNbrArcSortant; iBoucle++)
	{
		delete pARCtabSortant[iBoucle];
	}
	delete pARCtabArrivant;
	delete pARCtabSortant;
}

/**
 * @brief Ajoute un arc arrivant
 * @param iDest Numero du sommet a relier
 */
void Csommet::SOMAddArcArrivant(int iDest)
{
	if (iDest == iNumero)
	{
		throw Cexception(ERRCantAddArc);
	}

	int iBoucle = 0;

	for (iBoucle; iBoucle < iSOMNbrArcArrivant; iBoucle++)
	{
		if (pARCtabArrivant[iBoucle]->ARCgetDest() == iDest)
		{
			throw Cexception(ERRArcAlreadyExists);
		}
	}

	iBoucle = 0;

	Carc** pArctabTemp = new Carc*[iSOMNbrArcArrivant+1];

	if (pArctabTemp == nullptr) {
		throw Cexception(ErrNewMallocFailed);
	}

	for (iBoucle; iBoucle < (iSOMNbrArcArrivant); iBoucle++) // On recopie dans case a case dans un tableau temporaire de taille +1
	{
		pArctabTemp[iBoucle] = pARCtabArrivant[iBoucle];
	}

	pArctabTemp[iSOMNbrArcArrivant] = new Carc(iDest);
	if (pArctabTemp[iSOMNbrArcArrivant] == nullptr) {
		throw Cexception(ErrNewMallocFailed);
	}

	delete[] pARCtabArrivant;
	pARCtabArrivant = pArctabTemp;

	iSOMNbrArcArrivant += 1;

}

/**
* @brief Ajoute un arc arrivant avec un certain poids
* @param iDest Numero du sommet a relier
* @param iPoidsArc Le poids de l'arc ajoute
*/
 void Csommet::SOMAddArcArrivant(int iDest, int iPoidsArc)
 {
	 if (iDest == iNumero)
	 {
		 throw Cexception(ERRCantAddArc);
	 }

	 int iBoucle = 0;

	 for (iBoucle; iBoucle < iSOMNbrArcArrivant; iBoucle++)
	 {
		 if (pARCtabArrivant[iBoucle]->ARCgetDest() == iDest)
		 {
			 throw Cexception(ERRArcAlreadyExists);
		 }
	 }

	 iBoucle = 0;

	 Carc** pArctabTemp = new Carc*[iSOMNbrArcArrivant + 1];

	 if (pArctabTemp == nullptr) {
		 throw Cexception(ErrNewMallocFailed);
	 }

	 for (iBoucle; iBoucle < (iSOMNbrArcArrivant); iBoucle++) // On recopie dans case a case dans un tableau temporaire de taille +1
	 {
		 pArctabTemp[iBoucle] = pARCtabArrivant[iBoucle];
	 }

	 pArctabTemp[iSOMNbrArcArrivant] = new Carc(iDest, this->iNumero, iPoidsArc);
	 if (pArctabTemp[iSOMNbrArcArrivant] == nullptr) {
		 throw Cexception(ErrNewMallocFailed);
	 }

	 delete[] pARCtabArrivant;
	 pARCtabArrivant = pArctabTemp;

	 iSOMNbrArcArrivant += 1;
 }


 /**
 * @brief Ajoute un arc sortant
 * @param iDest Numero du sommet a relier
 */
 void Csommet::SOMAddArcSortant(int iDest)
{
	if (iDest == iNumero)
	{
		throw Cexception(ERRCantAddArc);
	}

	int iBoucle = 0;

	for (iBoucle; iBoucle < iSOMNbrArcSortant; iBoucle++)
	{
		if (pARCtabSortant[iBoucle]->ARCgetDest() == iDest)
		{
			throw Cexception(ERRArcAlreadyExists);
		}
	}

	iBoucle = 0;

	Carc** pArctabTemp = new Carc*[iSOMNbrArcSortant + 1];
	if (pArctabTemp == nullptr) {
		throw Cexception(ErrNewMallocFailed);
	}


	for (iBoucle; iBoucle < (iSOMNbrArcSortant); iBoucle++) // On recopie dans case a case dans un tableau temporaire de taille +1
	{
		pArctabTemp[iBoucle] = pARCtabSortant[iBoucle];
	}

	pArctabTemp[iSOMNbrArcSortant] = new Carc(iDest);
	if (pArctabTemp[iSOMNbrArcSortant] == nullptr) {
		throw Cexception(ErrNewMallocFailed);
	}
	delete[] pARCtabSortant;
	pARCtabSortant = pArctabTemp;

	iSOMNbrArcSortant += 1;
}

/**
* @brief Ajoute un arc sortant avec un certain poids
* @param iDest Numero du sommet a relier
* @param iPoidsArc Le poids de l'arc ajoute
*/
void Csommet::SOMAddArcSortant(int iDest, int iPoidsArc)
{
	if (iDest == iNumero)
	{
		throw Cexception(ERRCantAddArc);
	}

	int iBoucle = 0;

	for (iBoucle; iBoucle < iSOMNbrArcSortant; iBoucle++)
	{
		if (pARCtabSortant[iBoucle]->ARCgetDest() == iDest)
		{
			throw Cexception(ERRArcAlreadyExists);
		}
	}

	iBoucle = 0;

	Carc** pArctabTemp = new Carc*[iSOMNbrArcSortant + 1];
	if (pArctabTemp == nullptr) {
		throw Cexception(ErrNewMallocFailed);
	}


	for (iBoucle; iBoucle < (iSOMNbrArcSortant); iBoucle++) // On recopie dans case a case dans un tableau temporaire de taille +1
	{
		pArctabTemp[iBoucle] = pARCtabSortant[iBoucle];
	}

	pArctabTemp[iSOMNbrArcSortant] = new Carc(iDest, this->iNumero, iPoidsArc);
	if (pArctabTemp[iSOMNbrArcSortant] == nullptr) {
		throw Cexception(ErrNewMallocFailed);
	}
	delete[] pARCtabSortant;
	pARCtabSortant = pArctabTemp;

	iSOMNbrArcSortant += 1;
}

/**
* @brief Supprime un arc arrivant
* @param iDest Numero du sommet a delier
*/
void Csommet::SOMDeleteArcArrivant(int iDest)
{
	if (iSOMNbrArcArrivant == 0)
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
	iSOMNbrArcArrivant -= 1;

	if (iSOMNbrArcArrivant != 0)
	{
		Carc** pArctabTemp = new Carc*[iSOMNbrArcArrivant];
		if (pArctabTemp == nullptr) {
			throw Cexception(ErrNewMallocFailed);
		}

		iBoucle = 0;
		for (iBoucle; iBoucle <= iSOMNbrArcArrivant; iBoucle++)	//On recopie la liste en supprimant la case vide
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
 * @param iDest Numero du sommet a delier
 */
void Csommet::SOMDeleteArcSortant(int iDest)
{
	if (iSOMNbrArcSortant == 0)
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
	iSOMNbrArcSortant -= 1;

	if (iSOMNbrArcSortant != 0)
	{
		Carc** pArctabTemp = new Carc*[iSOMNbrArcSortant];
		if (pArctabTemp == nullptr) {
			throw Cexception(ErrNewMallocFailed);
		}

		iBoucle = 0;
		for (iBoucle; iBoucle <= iSOMNbrArcSortant; iBoucle++)	//On recopie la liste en supprimant la case vide
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
	return iSOMNbrArcArrivant;
}

/**
* @brief Donne le nombre d'arcs sortants
*/
int Csommet::SOMGetNbArcSortant()
{
	return iSOMNbrArcSortant;
}

/**
 * @brief Affiche le numero du dernier sommet cree
 * @return Le numero du dernier sommet cree
 */
int Csommet::SOMGetDernierSommet()
{
	return iSOMDernierSommet;
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
	for (iBoucle; iBoucle < iSOMNbrArcArrivant; iBoucle++)
	{
		if (pARCtabArrivant[iBoucle]->ARCgetPoids() >= 0) {
			std::cout << "\t\t" << pARCtabArrivant[iBoucle]->ARCgetDest() << " Poids = "<< pARCtabArrivant[iBoucle]->ARCgetPoids() <<std::endl;
		}
		else {
			std::cout << "\t\t" << pARCtabArrivant[iBoucle]->ARCgetDest() << std::endl;
		}
		
	}
	iBoucle = 0;
	std::cout << "\t Liste des arcs sortants : \n";
	for (iBoucle; iBoucle < iSOMNbrArcSortant; iBoucle++)
	{
		if (pARCtabArrivant[iBoucle]->ARCgetPoids() >= 0) {
			std::cout << "\t\t" << pARCtabSortant[iBoucle]->ARCgetDest() << " Poids = " << pARCtabSortant[iBoucle]->ARCgetPoids() << std::endl;
		}
		else {
			std::cout << "\t\t" << pARCtabSortant[iBoucle]->ARCgetDest() << std::endl;
		}
		
	}
}

/**
 * @brief Renvoie la destination de l'arc arrivant a la position iPos
 * @param iPos position iPos dans le tableau
 * @return destination iDest
 */
int Csommet::SOMgetDestArrivant(int iPos)
{
	if (iPos >= iSOMNbrArcArrivant || iPos < 0)
	{
		throw Cexception(ERRPosOutOfRange);
	}
	return pARCtabArrivant[iPos]->ARCgetDest();
}

/**
 * @brief Renvoie la destination de l'arc sortant a la position iPos
 * @param iPose position iPos dans le tableau
 * @return destination iDest
 */
int Csommet::SOMgetDestSortant(int iPos)
{
	if (iPos >= iSOMNbrArcSortant || iPos < 0)
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
	iTemp = iSOMNbrArcArrivant;

	pARCtabArrivant = pARCtabSortant;
	iSOMNbrArcArrivant = iSOMNbrArcSortant;

	pARCtabSortant = pARCTemp;
	iSOMNbrArcSortant = iTemp;

	pARCTemp = nullptr;

}


/**
* @brief Permet de recuperer une copie des arcs du tableau sortant du sommet
* @return la copie du tableau
*/
Carc ** Csommet::SOMgetTabArcCopy(void)
{
	Carc** pARCtabCopy;
	int iBoucle;

	if (iSOMNbrArcSortant > 0) {

		pARCtabCopy = new Carc*[iSOMNbrArcSortant];
		for (iBoucle = 0; iBoucle < iSOMNbrArcSortant; iBoucle++) {
			pARCtabCopy[iBoucle] = new Carc(*pARCtabSortant[iBoucle]);
		}

		return pARCtabCopy;
	}
	else {
		return nullptr;
	}

}

/**
* @brief Surcharge de l'opérateur egal
* @param sommet le sommet a utiliser pour l'operation
*/
Csommet& Csommet::operator=(Csommet& sommet)
{
	int iBoucle = 0;
	for (iBoucle; iBoucle < iSOMNbrArcArrivant; iBoucle++)
	{
		delete pARCtabArrivant[iBoucle];
	}

	iBoucle = 0;

	for (iBoucle; iBoucle < iSOMNbrArcSortant; iBoucle++)
	{
		delete pARCtabSortant[iBoucle];
	}
	delete[] pARCtabArrivant;
	delete[] pARCtabSortant;

	iBoucle = 0;

	iNumero = sommet.iNumero;
	iSOMNbrArcArrivant = sommet.iSOMNbrArcArrivant;
	iSOMNbrArcSortant = sommet.iSOMNbrArcSortant;

	pARCtabArrivant = new Carc*[iSOMNbrArcArrivant];
	pARCtabSortant = new Carc*[iSOMNbrArcSortant];

	for (iBoucle = 0; iBoucle < iSOMNbrArcArrivant; iBoucle++)
	{
		pARCtabArrivant[iBoucle] = new Carc(*sommet.pARCtabArrivant[iBoucle]);
	}
	for (iBoucle = 0; iBoucle < iSOMNbrArcSortant; iBoucle++)
	{
		pARCtabSortant[iBoucle] = new Carc(*sommet.pARCtabSortant[iBoucle]);
	}
	iSOMDernierSommet = sommet.iSOMDernierSommet;

	return *this;
}

/**
* @brief surcharge du flux de sortie pour un affichage simplifie de la structure
* @param out le flux
* @param SOMelem le sommet a afficher
* @return le flux de sortie contenant le sommet
*/
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
