#include "Kruskal.h"



/**
 * @brief Permet de chercher un arbre couvrant de poids minimal a aprtir d'un graphe
 * 
 * @param pGRAbase le graphe de depart
 * @return un graphe étant l'arbre couvrant
 */
Cgraphe* kruskal(Cgraphe* pGRAbase) {

	int iBoucle;
	int iNbSomTotal = pGRAbase->GRAGetNbSommets();
	int iNbArcsTotal = pGRAbase->GRAgetNbAllArcs();
	
	Csommet** pSOMtabSommetsGraphe = pGRAbase->GRAgetTabSomCopy();
	Carc** pARCtabArcsTotalGraphe = pGRAbase->GRAgetTabAllArcsCopy();
	
	Cgraphe* pGRAresult = new Cgraphe();
	if (pGRAresult == nullptr) {
		throw Cexception(ErrNewMallocFailed);
	}
	SensembleSommets** pENSTabEnsemble = new SensembleSommets*[iNbSomTotal];
	if (pENSTabEnsemble == nullptr) {
		throw Cexception(ErrNewMallocFailed);
	}
	int iENSTaille = iNbSomTotal;

	SensembleSommets* pENSsomU;
	int iSomU;
	SensembleSommets* pENSsomV;
	int iSomV;

	for (iBoucle = 0; iBoucle < iNbSomTotal; iBoucle++) {
		//on ajoute tt les sommets au graphe
		pGRAresult->GRAAddSommet(pSOMtabSommetsGraphe[iBoucle]->SOMGetSomNum());

		//l'ensemnble Qk contient Sk
		pENSTabEnsemble[iBoucle] = new SensembleSommets();
		if (pENSTabEnsemble[iBoucle] == nullptr) {
			throw Cexception(ErrNewMallocFailed);
		}

		pENSTabEnsemble[iBoucle]->iTailleTab = 1;

		pENSTabEnsemble[iBoucle]->pSOMtab = new Csommet*[1];
		if (pENSTabEnsemble[iBoucle]->pSOMtab == nullptr) {
			throw Cexception(ErrNewMallocFailed);
		}

		pENSTabEnsemble[iBoucle]->pSOMtab[0] = new Csommet(pSOMtabSommetsGraphe[iBoucle]->SOMGetSomNum());
		if (pENSTabEnsemble[iBoucle]->pSOMtab[0] == nullptr) {
			throw Cexception(ErrNewMallocFailed);
		}
	}

	//trier tab arc ordre croissant du poids
	std::sort( pARCtabArcsTotalGraphe, pARCtabArcsTotalGraphe + iNbArcsTotal, triArc);

	for (iBoucle = 0; iBoucle < iNbArcsTotal; iBoucle++) {
		//soit (u,v) l'arrete pARCtabArcsTotalGraphe[iBoucle]
		//trouver les 2 ensmbles qui ont le sommet u et le sommet v

		iSomU = pARCtabArcsTotalGraphe[iBoucle]->ARCgetDepart();
		pENSsomU = findEnsembleFromSommet(pENSTabEnsemble, iENSTaille, iSomU);

		iSomV = pARCtabArcsTotalGraphe[iBoucle]->ARCgetDest();
		pENSsomV = findEnsembleFromSommet(pENSTabEnsemble, iENSTaille, iSomV);
		//Si Gu != Gv
		if (pENSsomU != pENSsomV) {
			pGRAresult->GRAAddArc(iSomU, iSomV);//add arc u,v
			//fusionner Qv et Qu
			fusionEnsembles(pENSTabEnsemble, iENSTaille, pENSsomU, pENSsomV);
		}
	}

	return pGRAresult;
}

/**
 * @brief permet de trouver l'ensemble contenant un sommet dans un tableau d'ensemble
 * 
 * @param tabEns le tableau ou l'on cherche
 * @param iSizeTabEns la taille de ce tableau
 * @param iSomNum le numero du sommet recherche
 * @return un pointeur vers l'ensemble en question
 */
SensembleSommets* findEnsembleFromSommet(SensembleSommets** &tabEns, int iSizeTabEns, int iSomNum) {
	int iBoucleEns, iBoucleSom;
	//for each ensembles
	for (iBoucleEns = 0; iBoucleEns < iSizeTabEns; iBoucleEns++) {
		//for each som of the ensemble
		for (iBoucleSom = 0; iBoucleSom < tabEns[iBoucleEns]->iTailleTab; iBoucleSom++) {
			//if som nim == iSomNum
			if (tabEns[iBoucleEns]->pSOMtab[iBoucleSom]->SOMGetSomNum() == iSomNum) {
				//return ensemble
				return tabEns[iBoucleEns];
			}						
		}		
	}
		
	//throw new Cexception(-1);
	//return null which mean no ensemble found
	return nullptr;
}

/**
 * @brief permet de fusionner 2 ensembles, en MODIFIANT le tableau pour le reduire et mettre tout les sommets de l'ensemble B dans l'ensemble A
 * 
 * @param pENSTab le tableau des ensembles
 * @param pENSa le premier ensemble a fusioner
 * @param pENSb le second ensemble a fusioner
 */
void fusionEnsembles(SensembleSommets** &pENSTab, int &iSizeTabENS, SensembleSommets* &pENSa, SensembleSommets* &pENSb) {
	int iTailleC, iBoucle, iDecalage;
	SensembleSommets* pENSc, *pENStemp;
	SensembleSommets** pENSNewTab;
	//recup taille
	iTailleC = pENSa->iTailleTab + pENSb->iTailleTab;

	//nouvel ensemble C de taille a+b
	pENSc = new SensembleSommets();
	if (pENSc == nullptr) {
		throw Cexception(ErrNewMallocFailed);
	}
	pENSc->iTailleTab = iTailleC;
	pENSc->pSOMtab = new Csommet*[iTailleC];
	if (pENSc->pSOMtab == nullptr) {
		throw Cexception(ErrNewMallocFailed);
	}

	//recopie de A dans C
	for (iBoucle = 0; iBoucle < pENSa->iTailleTab; iBoucle++) {
		pENSc->pSOMtab[iBoucle] = new Csommet(*pENSa->pSOMtab[iBoucle]);
		if (pENSc->pSOMtab[iBoucle] == nullptr) {
			throw Cexception(ErrNewMallocFailed);
		}
	}
	//recopie de B dans C
	for (iBoucle = pENSa->iTailleTab; iBoucle < iTailleC; iBoucle++) {
		pENSc->pSOMtab[iBoucle] = new Csommet(*pENSb->pSOMtab[iBoucle - pENSa->iTailleTab]);
		if (pENSc->pSOMtab[iBoucle] == nullptr) {
			throw Cexception(ErrNewMallocFailed);
		}
	}
	
	
	

	


	//recopie pC dans pA
	//pENSa = pENSc;


	//nouveau tab EnsB de taille -1
	pENSNewTab = new SensembleSommets*[iSizeTabENS - 1];
	if (pENSNewTab == nullptr) {
		throw Cexception(ErrNewMallocFailed);
	}

	//recopie tab EnsA dans ENSB
	for (iBoucle = 0, iDecalage = 0; iBoucle < iSizeTabENS; iBoucle++) {
		if (pENSTab[iBoucle] == pENSb) {
			iDecalage++;//n'arrivera qu'une fois
		}
		if (pENSTab[iBoucle + iDecalage] == pENSa) {
			pENSNewTab[iBoucle] = pENSc;
		}
		else {
			pENSNewTab[iBoucle] = pENSTab[iBoucle + iDecalage];
		}
		
	}
	

	//delete A et mettre a nullptr
	for (iBoucle = 0; iBoucle < pENSa->iTailleTab; iBoucle++) {
		delete pENSa->pSOMtab[iBoucle];
		pENSa->pSOMtab[iBoucle] = nullptr;
	}
	delete[] pENSa->pSOMtab;
	pENSa->pSOMtab = nullptr;
	//pENStemp = pENSa;
	delete pENSa;
	pENSa = nullptr;

	//delete de B 
	for (iBoucle = 0; iBoucle < pENSb->iTailleTab; iBoucle++) {
		delete pENSb->pSOMtab[iBoucle];
		pENSb->pSOMtab[iBoucle] = nullptr;
	}
	delete[] pENSb->pSOMtab;
	pENSb->pSOMtab = nullptr;
	//pENStemp = pENSb;
	delete pENSb;
	pENSb = nullptr;
	



	delete[] pENSTab;
	pENSTab = pENSNewTab;
	iSizeTabENS--;
}

/**
 * @brief fonction de tri pour la fonction sort
 * 
 * @param firstArc Premier arc a trier
 * @param otherArc Seconde arc a trier
 * @return 1 si otherarc a un poids plus important, 0 sinon
 */
bool triArc(Carc* firstArc, Carc* otherArc) {
	return (firstArc->ARCgetPoids() < otherArc->ARCgetPoids());
}
