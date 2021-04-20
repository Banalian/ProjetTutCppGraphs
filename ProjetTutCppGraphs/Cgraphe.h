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
	* @brief Constructeur par d�faut
	*/
	Cgraphe();
	
	/**
	* @brief Destructeur de Cgraphe
	*/
	~Cgraphe();

	/**
	* @brief Permet d'ajouter un Sommet dans le graphe, sans aucun Arc
	* @param iNum le num�ro du graphe � ajouter
	*/
	void GRAAddSommet(int iNum);

	/**
	* @brief Constructeur par d�faut
	*/
	void GRADeleteSommet(int iNumSom);


	/**
	* @brief Constructeur par d�faut
	*/
	void GRAAddArc(int iNumSommetDepart, int iNumSommetArrive);
	
	/**
	* @brief Constructeur par d�faut
	*/
	void GRADeleteArc(int iNumSommetDepart, int iNumSommetArrive);


	/**
	* @brief Constructeur par d�faut
	*/
	void GRAAfficherGraph();
};

