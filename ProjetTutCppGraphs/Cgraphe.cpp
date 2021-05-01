#include "Cgraphe.h"


/**
* @brief Permet de connaitre la position dans le tableau d'un sommet du graph
* @param iNumSom le numero a tester
* @return la poisition dans le tableau, et -1 s'il n'a pas trouve le sommet
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
* @brief Constructeur par defaut
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

	//si un sommet existe, il faut recreer le tableau, sinon on laisse le tableau a nullptr
	if (iNbSommets > 0) {
		pSOMtab = new Csommet*[iNbSommets];
		if (pSOMtab == nullptr) {
			throw Cexception(ErrNewMallocFailed);
		}

		for (iBoucle = 0; iBoucle < iNbSommets; iBoucle++) {

			pSOMtab[iBoucle] = new Csommet(*GRAelem.pSOMtab[iBoucle]);
			if (pSOMtab[iBoucle] == nullptr) {
				throw Cexception(ErrNewMallocFailed);
			}

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

	//pas besoin de verifier s'il y a un sommet qui existe, car on sortira directement de la boucle si iNbSommet == 0
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

	//pas besoin de verifier s'il y a un sommet qui existe, car on sortira directement de la boucle si iNbSommet == 0
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
	if (pSOMtabTemp == nullptr) {
		throw Cexception(ErrNewMallocFailed);
	}

	int iBoucle;
	for (iBoucle = 0; iBoucle < (iNbSommets - 1); iBoucle++) {
		pSOMtabTemp[iBoucle] = pSOMtab[iBoucle];
	}

	pSOMtabTemp[iBoucle] = new Csommet(iNum);
	if (pSOMtabTemp[iBoucle] == nullptr) {
		throw Cexception(ErrNewMallocFailed);
	}

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

	int iBoucle = 0, jBoucle, iArrivant, iSortant, iArcToDelete, iDecalage = 0;
	Csommet **pSOMtabTemp;

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
		iArcToDelete = GRAPlaceOfSomInTab(iArcToDelete);
		pSOMtab[iArcToDelete]->SOMDeleteArcSortant(iNumSom);
	}

	for (jBoucle = 0; jBoucle < iSortant; jBoucle++) {
		//get arc jBoucle du sommet iBoucle, recuperer la destination
		iArcToDelete = pSOMtab[iBoucle]->SOMgetDestSortant(jBoucle);

		//aller delete d'arc de dest iBoucle dans le sommet dont le numero a ete recup avant
		iArcToDelete = GRAPlaceOfSomInTab(iArcToDelete);
		pSOMtab[iArcToDelete]->SOMDeleteArcArrivant(iNumSom);
	}




	delete pSOMtab[iBoucle];
	pSOMtab[iBoucle] = nullptr;
	iNbSommets--;


	if (iNbSommets == 0) {
		delete[] pSOMtab;
		pSOMtab = nullptr;
	}
	else {
		pSOMtabTemp = new Csommet*[iNbSommets];
		if (pSOMtabTemp == nullptr) {
			throw Cexception(ErrNewMallocFailed);
		}
		
		//on pourrait penser que cette boucle va oublier 1 case, mais en realite pas de probleme, car le if permet de sauter une case pour bien atteindre toutes les cases
		//et si la case vide est a la fin, elle ne sera juste pas testee
		for (iBoucle = 0; iBoucle < iNbSommets; iBoucle++) {
			if (pSOMtab[iBoucle] == nullptr) {
				iDecalage++;
			}
			pSOMtabTemp[iBoucle] = pSOMtab[iBoucle+ iDecalage];
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

	if (iPosSomDepart == -1 || iPosSomArrivee == -1) {
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

	if (iPosSomDepart == -1 || iPosSomArrivee == -1 ) {
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

Csommet** Cgraphe::GRAgetTabSomCopy(void)
{
	Csommet** pSOMtabCopy;
	int iBoucle;
	
	if (iNbSommets > 0) {
		pSOMtabCopy = new Csommet*[iNbSommets];
		if (pSOMtabCopy == nullptr) {
			throw Cexception(ErrNewMallocFailed);
		}

		for (iBoucle = 0; iBoucle < iNbSommets; iBoucle++) {
			pSOMtabCopy[iBoucle] = new Csommet(*pSOMtab[iBoucle]);
			if (pSOMtabCopy[iBoucle] == nullptr) {
				throw Cexception(ErrNewMallocFailed);
			}
		}


		return pSOMtabCopy;
	}
	else {
		return nullptr;
	}
	
}


/**
* @brief Surcharge du = => equivalent au constructeur de recopie
* @param GRAelem le graph a copier
* @return le graph copie
*/
Cgraphe & Cgraphe::operator=(Cgraphe & GRAelem)
{
	int iBoucle;


	if (pSOMtab) {
		for (iBoucle = 0; iBoucle < iNbSommets; iBoucle++) {
			delete pSOMtab[iBoucle];
		}

		delete[] pSOMtab;
	}


	iNbSommets = GRAelem.iNbSommets;

	if (iNbSommets > 0) {

		pSOMtab = new Csommet*[iNbSommets];
		if (pSOMtab == nullptr) {
			throw Cexception(ErrNewMallocFailed);
		}

		for (iBoucle = 0; iBoucle < iNbSommets; iBoucle++) {
			pSOMtab[iBoucle] = new Csommet(*GRAelem.pSOMtab[iBoucle]);
			if (pSOMtab[iBoucle] == nullptr) {
				throw Cexception(ErrNewMallocFailed);
			}
		}
	}
	else {
		pSOMtab = nullptr;
	}
	

	return *this;
}



std::ostream & operator<<(std::ostream & out, Cgraphe & GRAelem)
{
	// TODO: insérer une instruction return ici
	int iBoucle;
	Csommet** pSOMtabTemp = GRAelem.GRAgetTabSomCopy();

	if (pSOMtabTemp == nullptr) {
		out << "Graphe Vide";
	}
	for (iBoucle = 0; iBoucle < GRAelem.GRAGetNbSommets(); iBoucle++) {
		out << *pSOMtabTemp[iBoucle] << std::endl;
	}

	return out;
}
