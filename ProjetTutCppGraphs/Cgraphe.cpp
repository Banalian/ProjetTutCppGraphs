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

int Cgraphe::GRAPlaceOfSomInTab(int iNumSom)
{
	int iBoucle;

	for (iBoucle = 0; iBoucle < iNbSommets; iBoucle++) {
		if (pSOMtab[iBoucle]->SOMGetSomNum() == iNumSom) {
			return iBoucle;
		}
	}

	return -1;
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
	int iBoucle = 0, jBoucle, iArrivant, iSortant, iArcToDelete;

	while(pSOMtab[iBoucle]->SOMGetSomNum() != iNumSom) {
		iBoucle++;
	}
	//iBoucle a partir d'ici represente l'emplacement du sommet a supprimer.

	iArrivant = pSOMtab[iBoucle]->SOMGetNbArcArrivant();
	iSortant = pSOMtab[iBoucle]->SOMGetNbArcSortant();

	//pour chaque arc ARRIVANT, on supprime l'arc PARTANT dans le sommet correspondant
	for (jBoucle = 0; jBoucle < iArrivant; jBoucle++) {
		//get arc jBoucle du sommet iBoucle, recuperer la destination
		iArcToDelete = pSOMtab[iBoucle]->SOMgetDestArrivant(jBoucle);
		
		//aller delete d'arc de dest iBoucle dans le sommet dont le numero a ete recup avant
		pSOMtab[iArcToDelete]->SOMDeleteArcSortant(iBoucle);
	}

	for (jBoucle = 0; jBoucle < iSortant; jBoucle++) {
		//get arc jBoucle du sommet iBoucle, recuperer la destination
		iArcToDelete = pSOMtab[iBoucle]->SOMgetDestSortant(jBoucle);

		//aller delete d'arc de dest iBoucle dans le sommet dont le numero a ete recup avant
		pSOMtab[iArcToDelete]->SOMDeleteArcArrivant(iBoucle);
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
	int iPosSomDepart = GRAPlaceOfSomInTab(iNumSommetDepart);
	int iPosSomArrivee = GRAPlaceOfSomInTab(iNumSommetArrivee);

	if (iPosSomArrivee == -1 || iPosSomArrivee == -1) {
		throw Cexception(ERRSumDoesntExist);
	}

	pSOMtab[iPosSomDepart]->SOMAddArcSortant(iNumSommetArrivee);
	pSOMtab[iPosSomArrivee]->SOMAddArcArrivant(iNumSommetDepart);
}

/**
* @brief Permet de supprimer un arc entre deux sommets
* @param iNumSommetDepart Le numero du sommet de depart
* @param iNumSommetArrive Le numero du sommet d'arrivee
*/
void Cgraphe::GRADeleteArc(int iNumSommetDepart, int iNumSommetArrivee)
{
	int iPosSomDepart = GRAPlaceOfSomInTab(iNumSommetDepart);
	int iPosSomArrivee = GRAPlaceOfSomInTab(iNumSommetArrivee);

	if ( iPosSomArrivee == -1 || iPosSomArrivee == -1 ) {
		throw Cexception(ERRSumDoesntExist);
	}

	pSOMtab[iPosSomDepart]->SOMDeleteArcSortant(iNumSommetArrivee);
	pSOMtab[iPosSomArrivee]->SOMDeleteArcArrivant(iNumSommetDepart);

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
