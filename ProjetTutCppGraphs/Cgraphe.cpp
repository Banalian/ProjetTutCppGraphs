#include "Cgraphe.h"


/**
* @brief Permet de connaitre la position dans le tableau d'un sommet du graph
* @param iNumSom le numero a tester
* @return la poisition dans le tableau, et -1 s'il n'a pas trouve le sommet
*/
int Cgraphe::GRAPlaceOfSomInTab(int iNumSom)
{
	int iBoucle;

	for (iBoucle = 0; iBoucle < iGRANbSommets; iBoucle++) {
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
	iGRANbSommets = 0;
}


/**
* @brief Constructeur de recopie
* @param GRAelem le graphe a recopier
*/
Cgraphe::Cgraphe(Cgraphe & GRAelem)
{
	int iBoucle;

	iGRANbSommets = GRAelem.GRAGetNbSommets();

	//si un sommet existe, il faut recreer le tableau, sinon on laisse le tableau a nullptr
	if (iGRANbSommets > 0) {
		pSOMtab = new Csommet*[iGRANbSommets];
		if (pSOMtab == nullptr) {
			throw Cexception(ErrNewMallocFailed);
		}

		for (iBoucle = 0; iBoucle < iGRANbSommets; iBoucle++) {

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
	for (iBoucle = 0; iBoucle < iGRANbSommets; iBoucle++) {
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
	return iGRANbSommets;
}


/**
* @brief Permet de savoir si un numero est un sommet du graphe
* @param iNumSom le numero a tester
* @return Vrai si le numero fait bien parti du graphe, faux sinon
*/
bool Cgraphe::GRAIsSomInTab(int iNumSom)
{
	int iBoucle;

	//pas besoin de verifier s'il y a un sommet qui existe, car on sortira directement de la boucle si iNbSommet == 0
	for (iBoucle = 0; iBoucle < iGRANbSommets; iBoucle++) {
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

	iGRANbSommets++;

	Csommet **pSOMtabTemp = new Csommet*[iGRANbSommets];
	if (pSOMtabTemp == nullptr) {
		throw Cexception(ErrNewMallocFailed);
	}

	int iBoucle;
	for (iBoucle = 0; iBoucle < (iGRANbSommets - 1); iBoucle++) {
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
	iGRANbSommets--;


	if (iGRANbSommets == 0) {
		delete[] pSOMtab;
		pSOMtab = nullptr;
	}
	else {
		pSOMtabTemp = new Csommet*[iGRANbSommets];
		if (pSOMtabTemp == nullptr) {
			throw Cexception(ErrNewMallocFailed);
		}
		
		//on pourrait penser que cette boucle va oublier 1 case, mais en realite pas de probleme, car le if permet de sauter une case pour bien atteindre toutes les cases
		//et si la case vide est a la fin, elle ne sera juste pas testee
		for (iBoucle = 0; iBoucle < iGRANbSommets; iBoucle++) {
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

void Cgraphe::GRAAddArc(int iNumSommetDepart, int iNumSommetArrivee, int iPoidsArc)
{
	int iPosSomDepart = GRAPlaceOfSomInTab(iNumSommetDepart);
	int iPosSomArrivee = GRAPlaceOfSomInTab(iNumSommetArrivee);

	if (iPosSomDepart == -1 || iPosSomArrivee == -1) {
		throw Cexception(ERRSumDoesntExist);
	}

	pSOMtab[iPosSomDepart]->SOMAddArcSortant(iNumSommetArrivee, iPoidsArc);
	pSOMtab[iPosSomArrivee]->SOMAddArcArrivant(iNumSommetDepart, iPoidsArc);
}

/**
* @brief Permet de supprimer un arc entre deux sommets
* @param iNumSommetDepart Le numero du sommet de depart
* @param iNumSommetArrive Le numero du sommet d'arrivee
*/
void Cgraphe::GRADeleteArc(int iNumSommetDepart, int iNumSommetArrivee)
{
	//On verifie d'abord que les 2 sommets existent
	int iPosSomDepart = GRAPlaceOfSomInTab(iNumSommetDepart);
	int iPosSomArrivee = GRAPlaceOfSomInTab(iNumSommetArrivee);

	if (iPosSomDepart == -1 || iPosSomArrivee == -1 ) {
		throw Cexception(ERRSumDoesntExist);
	}

	//puis on supprime l'arc des deux cotes
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

	for (iBoucle = 0; iBoucle < iGRANbSommets; iBoucle++) {
		pSOMtab[iBoucle]->SOMAfficherSommet();
	}

}


/**
* @brief Permet de récuperer une Copie du tableau des sommets
* @return une copie du tableau des sommets
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
	
	if (iGRANbSommets > 0) {
		pSOMtabCopy = new Csommet*[iGRANbSommets];
		if (pSOMtabCopy == nullptr) {
			throw Cexception(ErrNewMallocFailed);
		}

		for (iBoucle = 0; iBoucle < iGRANbSommets; iBoucle++) {
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

Carc ** Cgraphe::GRAgetTabAllArcsCopy(void)
{
	int iBoucleSom, iBoucleArcSom, iNbArcCurrent, iNbArcTotalAdded;
	int iNbArcTotal = 0;

	//on recupere le nombre total d'arcs du graphe
	for (iBoucleSom = 0; iBoucleSom < iGRANbSommets; iBoucleSom++) {
		iNbArcTotal += pSOMtab[iBoucleSom]->SOMGetNbArcSortant();
	}

	Carc** pARCtotal = new Carc*[iNbArcTotal];

	//on ajoute tout les arcs dans un grand tableau unique
	for (iBoucleSom = 0; iBoucleSom < iGRANbSommets; iBoucleSom++) {
		
		iNbArcCurrent = pSOMtab[iBoucleSom]->SOMGetNbArcSortant();

		Carc** pARCtemp = pSOMtab[iBoucleSom]->SOMgetTabArcCopy();



		for (iBoucleArcSom = 0; iBoucleArcSom < iNbArcCurrent; iBoucleArcSom++, iNbArcTotalAdded++) {
			//pARCtotal[iNbArcTotalAdded] = new Carc(*pARCtemp[iBoucleArcSom]); //safe method
			//delete pARCtemp[iBoucleArcSom];

			pARCtotal[iNbArcTotalAdded] = pARCtemp[iBoucleArcSom]; //not so safe method
		}

		if(pARCtemp != nullptr)
			delete pARCtemp;


	}

	return pARCtotal;
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
		for (iBoucle = 0; iBoucle < iGRANbSommets; iBoucle++) {
			delete pSOMtab[iBoucle];
		}

		delete[] pSOMtab;
	}


	iGRANbSommets = GRAelem.iGRANbSommets;

	if (iGRANbSommets > 0) {

		pSOMtab = new Csommet*[iGRANbSommets];
		if (pSOMtab == nullptr) {
			throw Cexception(ErrNewMallocFailed);
		}

		for (iBoucle = 0; iBoucle < iGRANbSommets; iBoucle++) {
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


/**
* @brief surcharge du flux de sortie pour un affichage simplifie de la structure
* @param out le flux
* @param GRAelem le sommet a afficher
* @return le flux de sortie contenant le sommet
*/
std::ostream & operator<<(std::ostream & out, Cgraphe & GRAelem)
{
	int iBoucle;
	//la fonction étant en dehors de la classe, il faut un moyen d'acceder au tableau, nous avons choisi de faire cette fonction
	Csommet** pSOMtabTemp = GRAelem.GRAgetTabSomCopy();

	if (pSOMtabTemp == nullptr) {
		out << "Graphe Vide";
	}
	for (iBoucle = 0; iBoucle < GRAelem.GRAGetNbSommets(); iBoucle++) {
		out << *pSOMtabTemp[iBoucle] << std::endl;
		delete pSOMtabTemp[iBoucle];
	}

	delete[] pSOMtabTemp;

	return out;
}
