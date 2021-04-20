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
	* @param iNum le numéro du graphe à ajouter
	*/
	void GRAAddSommet(int iNum);

	/**
	* @brief Constructeur par défaut
	*/
	void GRADeleteSommet(int iNumSom);


	/**
	* @brief Constructeur par défaut
	*/
	void GRAAddArc(int iNumSommetDepart, int iNumSommetArrive);
	
	/**
	* @brief Constructeur par défaut
	*/
	void GRADeleteArc(int iNumSommetDepart, int iNumSommetArrive);


	/**
	* @brief Constructeur par défaut
	*/
	void GRAAfficherGraph();
};

