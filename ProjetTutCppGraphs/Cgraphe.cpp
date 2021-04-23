#include "Cgraphe.h"


/**
* @brief Permet de connaitre la position dans le tableau d'un sommet du graph
* @param iNumSom le numero a tester
* @return la poisition dans le tableau, et -1 s'il n'a pas trouve
*/
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

Cgraphe::Cgraphe(Cgraphe & GRAelem)
{
	int iBoucle;

	iNbSommets = GRAelem.GRAGetNbSommets();

	if (iNbSommets > 0) {
		pSOMtab = new Csommet*[iNbSommets];

		for (iBoucle = 0; iBoucle < iNbSommets; iBoucle++) {

			pSOMtab[iBoucle] = new Csommet(*GRAelem.pSOMtab[iBoucle]);

		}
	}
	else {
		pSOMtab = nullptr;
	}
	
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


/**
* @brief Recuperer le nombre de sommets dans le tableau
* @return le Nombre total de sommets
*/
int Cgraphe::GRAGetNbSommets()
{
	return iNbSommets;
}


/**
* @brief Permet de savoir si un numero est un sommet du graph
* @param iNumSom le numero a tester
* @return Vrai si le numero fait bien parti du graph, faux sinon
*/
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
		pSOMtabTemp[iBoucle] = pSOMtab[iBoucle];
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


/**
* @brief Fonction afin d'inverser tout les arcs du graphs, entre tout les sommets
*/
void Cgraphe::GRAInverserGraph()
{
	int iBoucle;

	for (iBoucle = 0; iBoucle < GRAGetNbSommets(); iBoucle++) {
		pSOMtab[iBoucle]->SOMInverserArcSom();
	}
}
