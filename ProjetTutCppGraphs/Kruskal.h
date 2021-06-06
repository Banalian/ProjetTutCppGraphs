#pragma once
#include "Cgraphe.h"
#include <algorithm>

struct SensembleSommets
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
Cgraphe* kruskal(Cgraphe* pGRAbase);



/**
 * @brief permet de trouver l'ensemble contenant un sommet dans un tableau d'ensemble
 *
 * @param tabEns le tableau ou l'on cherche
 * @param iSizeTabEns la taille de ce tableau
 * @param iSomNum le numero du sommet recherche
 * @return un pointeur vers l'ensemble en question
 */
SensembleSommets* findEnsembleFromSommet(SensembleSommets** &tabEns, int iSizeTabEns, int iSomNum);


/**
 * @brief permet de fusionner 2 ensembles, en MODIFIANT le tableau pour le reduire et mettre tout les sommets de l'ensemble B dans l'ensemble A
 *
 * @param pENSTab le tableau des ensembles
 * @param pENSa le premier ensemble a fusioner
 * @param pENSb le second ensemble a fusioner
 */
void fusionEnsembles(SensembleSommets** &pENSTab, int &iSizeTabENS, SensembleSommets* &pENSa, SensembleSommets* &pENSb);

/**
 * @brief fonction de tri pour la fonction sort
 *
 * @param firstArc Premier arc a trier
 * @param otherArc Seconde arc a trier
 * @return 1 si otherarc a un poids plus important, 0 sinon
 */
bool triArc(Carc* firstArc, Carc* otherArc);
