#include "Cgraphe.h"

bool Cgraphe::GRAIsSomInTab(int iNumSom)
{
	int iBoucle;

	for (iBoucle = 0; iBoucle < iNbSommets; iBoucle++) {
		if (pSOMtab[iBoucle]->SOMGetSomNum() == iNumSom) {
			return true;
		}
	}

	return false;
}

/**
* @brief Constructeur par défaut
*/
Cgraphe::Cgraphe()
{
	pSOMtab = nullptr;
	iNbSommets = 0;
}

/**
* @brief Destructeur de Cgraphe
*/
Cgraphe::~Cgraphe()
{
	int iBoucle;

	for (iBoucle = 0; iBoucle < iNbSommets; iBoucle++) {
		delete pSOMtab[iBoucle];
	}

	delete[] pSOMtab;

}


int Cgraphe::GRAGetNbSommets()
{
	return iNbSommets;
}

/**
* @brief Permet d'ajouter un Sommet dans le graphe, sans aucun Arc
* @param iNum Le numero du sommet a ajouter
*/
void Cgraphe::GRAAddSommet(int iNum)
{
	if (GRAIsSomInTab(iNum)) {
		throw Cexception(ERRSumAlreadyExist);
	}

	iNbSommets++;

	Csommet **pSOMtabTemp = new Csommet*[iNbSommets];
	int iBoucle;
	for (iBoucle = 0; iBoucle < (iNbSommets - 1); iBoucle++) {
		pSOMtabTemp[iBoucle] = pSOMtabTemp[iBoucle];
	}

	pSOMtabTemp[iBoucle] = new Csommet(iNum);

	delete[] pSOMtab;
	pSOMtab = pSOMtabTemp;


}

/**
* @brief Permet de supprimer un Sommet dans le graphe, ainsi que tout ses arcs (et les arcs dans les sommets relies a celui-ci)
* @param iNumSom Le numero du sommet a supprimer;
*/
void Cgraphe::GRADeleteSommet(int iNumSom)
{

	//-------------------------------------------------NON FINI : il faut egalement supprimer les arc dans les sommets relie au sommet a supprimer-----------
	if (!GRAIsSomInTab(iNumSom)) {
		throw Cexception(ERRSumDoesntExist);
	}
	int iBoucle = 0;

	while(pSOMtab[iBoucle]->SOMGetSomNum() != iNumSom) {
		iBoucle++;
	}
	
	delete pSOMtab[iBoucle];
	
	Csommet **pSOMtabTemp;
	iNbSommets--;


	if (iNbSommets == 0) {
		delete[] pSOMtab;
		pSOMtab = nullptr;
	}
	else {
		pSOMtabTemp = new Csommet*[iNbSommets];
		
		for (iBoucle = 0; iBoucle < iNbSommets; iBoucle++) {
			if (pSOMtab[iBoucle] == nullptr) {
				iBoucle++;
			}
			pSOMtabTemp[iBoucle] = pSOMtabTemp[iBoucle];
		}
		delete[] pSOMtab;
		pSOMtab = pSOMtabTemp;
	}
	
	
}

/**
* @brief Permet d'ajouter un arc entre deux sommets
* @param iNumSommetDepart Le numero du sommet de depart
* @param iNumSommetArrive Le numero du sommet d'arrivee
*/
void Cgraphe::GRAAddArc(int iNumSommetDepart, int iNumSommetArrivee)
{
}

/**
* @brief Permet de supprimer un arc entre deux sommets
* @param iNumSommetDepart Le numero du sommet de depart
* @param iNumSommetArrive Le numero du sommet d'arrivee
*/
void Cgraphe::GRADeleteArc(int iNumSommetDepart, int iNumSommetArrivee)
{
}

/**
* @brief Affichage du graph oriente, en affichant tout les sommets existants, ainsi que les arcs sortant de ce sommet
* afin d'eviter une redondance en affichant les arcs entrant egalement
*/
void Cgraphe::GRAAfficherGraph()
{
	int iBoucle;

	for (iBoucle = 0; iBoucle < iNbSommets; iBoucle++) {
		pSOMtab[iBoucle]->SOMAfficherSommet();
	}

}
