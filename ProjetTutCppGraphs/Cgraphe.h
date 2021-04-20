#pragma once

#include "Csommet.h"
#include "Carc.h"
#include "Cexception.h"

#define ERRSumAlreadyExist 301
#define ERRSumDoesntExist 302


class Cgraphe
{
private:
	/*Tableau de Sommet de tout le graphe.*/
	Csommet **pSOMtab;

	int iNbSommets;

	bool GRAIsSomInTab(int iNumSom);

public:

	/**
	* @brief Constructeur par d�faut
	*/
	Cgraphe();
	
	/**
	* @brief Destructeur de Cgraphe
	*/
	~Cgraphe();


	int GRAGetNbSommets();

	/**
	* @brief Permet d'ajouter un Sommet dans le graphe, sans aucun Arc
	* @param iNum Le numero du sommet a ajouter
	*/
	void GRAAddSommet(int iNum);

	/**
	* @brief Permet de supprimer un Sommet dans le graphe, ainsi que tout ses arcs (et les arcs dans les sommets relies a celui-ci)
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
	* @brief Affichage du graph oriente, en affichant tout les sommets existants, ainsi que les arcs sortant de ce sommet
	* afin d'eviter une redondance en affichant les arcs entrant egalement
	*/
	void GRAAfficherGraph();
};

