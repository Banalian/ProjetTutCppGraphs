#pragma once

#include "Csommet.h"
#include "Carc.h"
#include "Cexception.h"

class Cgraphe
{
private:
	/*Tableau de Sommet de tout le graphe.*/
	Csommet **pSOMtab;

public:

	/**
	* @brief Constructeur par défaut
	*/
	Cgraphe();
	
	/**
	* @brief Destructeur de Cgraphe
	*/
	~Cgraphe();

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
	void GRAAddArc(int iNumSommetDepart, int iNumSommetArrive);
	
	/**
	* @brief Permet de supprimer un arc entre deux sommets
	* @param iNumSommetDepart Le numero du sommet de depart
	* @param iNumSommetArrive Le numero du sommet d'arrivee
	*/
	void GRADeleteArc(int iNumSommetDepart, int iNumSommetArrive);


	/**
	* @brief Affichage du graph oriente, en affichant tout les sommets existants, ainsi que les arcs sortant de ce sommet
	* afin d'eviter une redondance en affichant les arcs entrant egalement
	*/
	void GRAAfficherGraph();
};

