#pragma once

#include <iostream>
#include "Csommet.h"
#include "Cexception.h"

#define ERRSumAlreadyExist 301
#define ERRSumDoesntExist 302


class Cgraphe
{
private:
	/*Tableau de tout les sommets du graphe.*/
	Csommet **pSOMtab;

	/*Nombre de sommets contenu dans le graph */
	int iGRANbSommets;

	/**
	* @brief Permet de connaitre la position dans le tableau d'un sommet du graph
	* @param iNumSom le numero a tester
	* @return la poisition dans le tableau, et -1 s'il n'a pas trouve le sommet
	*/
	int GRAPlaceOfSomInTab(int iNumSom);

public:

	/**
	* @brief Constructeur par defaut
	*/
	Cgraphe();

	/**
	* @brief Constructeur de recopie
	* @param GRAelem le graphe a recopier
	*/
	Cgraphe(Cgraphe& GRAelem);
	
	/**
	* @brief Destructeur de Cgraphe
	*/
	~Cgraphe();


	/**
	* @brief Recuperer le nombre de sommets dans le tableau
	* @return le Nombre total de sommets
	*/
	int GRAGetNbSommets();

	/**
	* @brief Permet de savoir si un numero est un sommet du graphe
	* @param iNumSom le numero a tester
	* @return vrai si le numero fait bien parti du graphe, faux sinon
	*/
	bool GRAIsSomInTab(int iNumSom);

	/**
	* @brief Permet d'ajouter un Sommet dans le graphe, sans aucun Arc
	* @param iNum Le numero du sommet a ajouter
	*/
	void GRAAddSommet(int iNum);

	/**
	* @brief Permet de supprimer un Sommet dans le graphe, ainsi que tous ses arcs (et les arcs dans les sommets relies a celui-ci)
	* @param iNumSom Le numero du sommet a supprimer;
	*/
	void GRADeleteSommet(int iNumSom);


	/**
	* @brief Permet d'ajouter un arc entre deux sommets
	* @param iNumSommetDepart Le numero du sommet de depart
	* @param iNumSommetArrive Le numero du sommet d'arrivee
	*/
	void GRAAddArc(int iNumSommetDepart, int iNumSommetArrivee);
	
	/**
	* @brief Permet de supprimer un arc entre deux sommets
	* @param iNumSommetDepart Le numero du sommet de depart
	* @param iNumSommetArrive Le numero du sommet d'arrivee
	*/
	void GRADeleteArc(int iNumSommetDepart, int iNumSommetArrivee);


	/**
	* @brief Affichage du graph oriente, en affichant tous les sommets existants, ainsi que les arcs entrants et sortants de ce sommet
	*/
	void GRAAfficherGraph();

	/**
	* @brief Fonction afin d'inverser tout les arcs du graphs, entre tous les sommets
	*/
	void GRAInverserGraph();

	/**
	* @brief Permet de r?cuperer une Copie du tableau des sommets
	* @return une copie du tableau des sommets
	*/
	Csommet** GRAgetTabSomCopy(void);


	/**
	* @brief Surcharge du = => equivalent au constructeur de recopie
	* @param GRAelem le graph a copier
	* @return le graph copie
	*/
	Cgraphe& operator=(Cgraphe& GRAelem);


};


/**
* @brief surcharge du flux de sortie pour un affichage simplifie de la structure
* @param out le flux
* @param GRAelem le sommet a afficher
* @return le flux de sortie contenant le sommet
*/
std::ostream& operator<<(std::ostream& out, Cgraphe& GRAelem);
