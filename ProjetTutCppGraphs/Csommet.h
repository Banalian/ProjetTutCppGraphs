#pragma once

#include <iostream>
#include "Carc.h"
#include "Cexception.h"
#define ERRCantAddArc 401
#define ERRNoMoreArc 402
#define ERRPosOutOfRange 403

class Csommet
{
private:

	int iNumero;
	Carc** pARCtabArrivant;
	Carc** pARCtabSortant;

	//Attributs de confort : ne servent qu'au confort de codage
	int iNbrArcArrivant;
	int iNbrArcSortant;
	static int idernierSommet; //Garde en memoire le numero du dernier sommet cree

public:

	/**
	 * @brief Constructeur par defaut
	 */
	Csommet();
	/**
	* @brief Constructeur de confort
	* @param Le numero a attribuer au sommet
	*/
	Csommet(int iNum);
	/**
	* @brief Constructeur de recopie
	* @param Le sommet a recopier
	*/
	Csommet(Csommet & SOMsommet);
	/**
	 * @brief Destructeur par defaut
	 */
	~Csommet();

	/**
	 * @brief Ajoute un arc arrivant
	 * @param Numero du sommet a relier
	 */
	void SOMAddArcArrivant(int iDest);
	/**
	 * @brief Ajoute un arc sortant
	 * @param Numero du sommet a relier
	 */
	void SOMAddArcSortant(int iDest);

	/**
	 * @brief Supprime un arc arrivant
	 * @param Numero du sommet a delier
	 */
	void SOMDeleteArcArrivant(int iDest);
	/**
	 * @brief Supprime un arc sortant
	 * @param Numero du sommet a delier
	 */
	void SOMDeleteArcSortant(int iDest);

	/**
	 * @brief Affiche le numero du sommet
	 * @return Le numero du sommet
	 */
	int SOMGetSomNum();
	/**
	* @brief Donne le nombre d'arcs arrivants
	*/
	int SOMGetNbArcArrivant();
	/**
	* @brief Donne le nombre d'arcs sortants
	*/
	int SOMGetNbArcSortant();
	/**
	 * @brief Affiche le numero du dernier sommet cree
	 * @return Le numero du dernier sommet cree
	 */
	int SOMGetdernierSommet();
	/**
	 * @brief Affiche toutes les informations du sommet
	 * @return Numero du sommet, liste des arcs entrants et liste des arcs sortants
	 */
	void SOMAfficherSommet();
	/**
	 * @brief Renvoie la destination de l'arc arrivant a la position iPos
	 * @param position iPos
	 * @return destination iDest
	 */
	int SOMgetDestArrivant(int iPos);
	/**
	 * @brief Renvoie la destination de l'arc sortant a la position iPos
	 * @param position iPos
	 * @return destination iDest
	 */
	int SOMgetDestSortant(int iPos);

	/**
	* @brief Permet d'inverser tout les arcs du sommet.
	* Une simple inversion entre A et B permet d'atteindre cela.
	*/
	void SOMInverserArcSom();

	Csommet& operator=(Csommet &sommet);

	
};

std::ostream& operator<<(std::ostream& out, Csommet& SOMelem);
