#include "Csommet.h"
int Csommet::idernierSommet = 0;

/**
 * @brief Constructeur par défaut
 */
Csommet::Csommet()
{
	iNumero = idernierSommet + 1;
	idernierSommet += 1;

	pARCtabArrivant = nullptr;
	pARCtabArrivant = nullptr;
}

/**
* @brief Constructeur de confort
* @param Le numero a attribuer au sommet
*/
Csommet::Csommet(int iNum)
{
	iNumero = iNum;
	idernierSommet = iNum;

	pARCtabArrivant = nullptr;
	pARCtabSortant = nullptr;
}

/**
 * @brief Destructeur par défaut
 */
Csommet::~Csommet()
{

}

/**
 * @brief Ajoute un arc arrivant
 * @param Pointeur vers un arc
 */
void Csommet::SOMAddArcArrivant(Carc * pARCelem)
{
}

/**
 * @brief Ajoute un arc sortant
 * @param Pointeur vers un arc
 */
void Csommet::SOMAddArcSortant(Carc * pARCelem)
{
}

/**
 * @brief Supprime un arc arrivant
 * @param Pointeur vers un arc
 */
void Csommet::SOMDeleteArcArrivant(Carc * pARCelem)
{
}

/**
 * @brief Ajoute un arc sortant
 * @param Pointeur vers un arc
 */
void Csommet::SOMDeleteArcSortant(Carc * pARCelem)
{
}

/**
 * @brief Affiche le numero du sommet
 * @return Le numéro du sommet
 */
int Csommet::SOMGetSomNum()
{
	return iNumero;
}

/**
 * @brief Affiche le numero du dernier sommet cree
 * @return Le numero du dernier sommet cree
 */
int Csommet::SOMGetdernierSommet()
{
	return idernierSommet;
}

/**
 * @brief Affiche toutes les informations du sommet
 * @return Numero du sommet, liste des arcs entrants et liste des arcs sortants
 */
void Csommet::SOMAfficherSommet()
{
}
