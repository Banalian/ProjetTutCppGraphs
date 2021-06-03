#include "Cgraphe.h"

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
	

	for (iBoucle = 0; iBoucle < iNbSomTotal; iBoucle++) {
		//on ajoute tt les sommets au graphe
		pGRAresult->GRAAddSommet(pSOMtabSommetsGraphe[iBoucle]->SOMGetSomNum());

		//l'ensemnble Qk contient Sk
	}

	//trier tab arc ordre croissant du poids

	for (iBoucle = 0; iBoucle < iNbArcsTotal; iBoucle++) {
		//soit (u,v) l'arrete pARCtabArcsTotalGraphe[iBoucle]
		//trouver les 2 ensmbles qui ont le sommet u et le sommet v
		//Si Gu != Gv
			pGRAresult->GRAAddArc(0, 0);//add arc u,v
			//fusionner Qv et Qu
		//fin si
	}

	return pGRAresult;
}
