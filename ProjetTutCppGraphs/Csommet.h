#pragma once

#include <iostream>
#include "Carc.h"
#include "Cexception.h"
#define ERRCantAddArc 401
#define ERRNoMoreArc 402
#define ERRPosOutOfRange 403
#define ERRArcAlreadyExists 404
#define ERRSomAsSameNumAsLastSum 405

class Csommet
{
private:

	int iNumero;
	Carc** pARCtabArrivant;
	Carc** pARCtabSortant;

	/** Attributs de confort : ne servent qu'au confort de codage*/
	int iSOMNbrArcArrivant;
	int iSOMNbrArcSortant;

	/**  Garde en memoire le numero du dernier sommet cree*/
	static int iSOMDernierSommet; 

public:

	/**
	 * @brief Constructeur par defaut
	 */
	Csommet();
	/**
	* @brief Constructeur de confort
	* @param iNum Le numero a attribuer au sommet
	*/
	Csommet(int iNum);
	/**
	* @brief Constructeur de recopie
	* @param SOMsommet Le sommet a recopier
	*/
	Csommet(Csommet & SOMsommet);
	/**
	 * @brief Destructeur par defaut
	 */
	~Csommet();

	/**
	 * @brief Ajoute un arc arrivant
	 * @param iDest Numero du sommet a relier
	 */
	void SOMAddArcArrivant(int iDest);
	/**
	 * @brief Ajoute un arc sortant
	 * @param iDest Numero du sommet a relier
	 */
	void SOMAddArcSortant(int iDest);

	/**
	 * @brief Supprime un arc arrivant
	 * @param iDest Numero du sommet a delier
	 */
	void SOMDeleteArcArrivant(int iDest);
	/**
	 * @brief Supprime un arc sortant
	 * @param iDest Numero du sommet a delier
	 */
	void SOMDeleteArcSortant(int iDest);

	/**
	 * @brief Affiche le numero du sommet
	 * @return Le numero du sommet
	 */
	int SOMGetSomNum();
	/**
	* @brief Donne le nombre d'arcs arrivants
	* @return le nombre d'arcs arrivant du sommet
	*/
	int SOMGetNbArcArrivant();
	/**
	* @brief Donne le nombre d'arcs sortants
	* @return le nombre d'arcs sortant du sommet
	*/
	int SOMGetNbArcSortant();
	/**
	 * @brief Affiche le numero du dernier sommet cree
	 * @return Le numero du dernier sommet cree
	 */
	int SOMGetDernierSommet();
	/**
	 * @brief Affiche toutes les informations du sommet
	 * renvoie le numero du sommet, liste des arcs entrants et liste des arcs sortants
	 */
	void SOMAfficherSommet();
	/**
	 * @brief Renvoie la destination de l'arc arrivant a la position iPos
	 * @param iPos position iPos dans le tableau
	 * @return destination iDest
	 */
	int SOMgetDestArrivant(int iPos);
	/**
	 * @brief Renvoie la destination de l'arc sortant a la position iPos
	 * @param iPos position iPos dans le tableau
	 * @return destination iDest
	 */
	int SOMgetDestSortant(int iPos);

	/**
	* @brief Permet d'inverser tous les arcs du sommet.
	* Une simple inversion entre A et B permet d'atteindre cela.
	*/
	void SOMInverserArcSom();

	/**
	* @brief Surcharge de l'opérateur egal
	* @param sommet le sommet a utiliser pour l'operation
	*/
	Csommet& operator=(Csommet &sommet);

	
};

/**
* @brief surcharge du flux de sortie pour un affichage simplifie de la structure
* @param out le flux
* @param SOMelem le sommet a afficher
* @return le flux de sortie contenant le sommet
*/
std::ostream& operator<<(std::ostream& out, Csommet& SOMelem);
