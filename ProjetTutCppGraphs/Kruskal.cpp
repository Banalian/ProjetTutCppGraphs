#include "Cgraphe.h"

typedef struct SensembleSommets
	{
		Csommet** pSOMtab;
		int iTailleTab;
	};

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
	SensembleSommets** pENSTabEnsemble = new SensembleSommets*[iNbSomTotal];

	for (iBoucle = 0; iBoucle < iNbSomTotal; iBoucle++) {
		//on ajoute tt les sommets au graphe
		pGRAresult->GRAAddSommet(pSOMtabSommetsGraphe[iBoucle]->SOMGetSomNum());

		//l'ensemnble Qk contient Sk
		pENSTabEnsemble[iBoucle] = new SensembleSommets();
		pENSTabEnsemble[iBoucle]->iTailleTab = 1;
		pENSTabEnsemble[iBoucle]->pSOMtab = new Csommet*[1];
		pENSTabEnsemble[iBoucle]->pSOMtab[0] = new Csommet(pSOMtabSommetsGraphe[iBoucle]->SOMGetSomNum());
	}

	//trier tab arc ordre croissant du poids

	for (iBoucle = 0; iBoucle < iNbArcsTotal; iBoucle++) {
		//soit (u,v) l'arrete pARCtabArcsTotalGraphe[iBoucle]
		//trouver les 2 ensmbles qui ont le sommet u et le sommet v
		do {
			//rechercher dans les ensembles chaque som
		} while (pARCtabArcsTotalGraphe[iBoucle]->ARCgetDepart() != pENSTabEnsemble[0]->pSOMtab[0]->SOMGetSomNum());
		//Si Gu != Gv
		if (pENSTabEnsemble[iBoucle] != pENSTabEnsemble[iBoucle]) {
			pGRAresult->GRAAddArc(0, 0);//add arc u,v
			//fusionner Qv et Qu
		}
	}

	return pGRAresult;
}

bool TriArc(Carc &firstArc, Carc &otherArc) {
	return (firstArc.ARCgetPoids() < otherArc.ARCgetPoids());
}

