#pragma once
#include "Carc.h"

class Csommet
{
private:

	int iNumero;
	Carc** pARCtabArrivant;
	Carc** pARCtabSortant;

	//Attributs de confort : ne servent qu'au confort de codage
	int iNbrArcArrivant;
	int iNbrArcSortant;
	static int idernierSommet; //Garde en mémoire le numero du dernier sommet cree

public:

	Csommet();
	Csommet(int iNum);
	Csommet(Csommet & SOMsommet);
	~Csommet();

	void SOMAddArcArrivant(int iDest);
	void SOMAddArcSortant(int iDest);

	void SOMDeleteArcArrivant(int iDest);
	void SOMDeleteArcSortant(int iDest);

	int SOMGetSomNum();
	int SOMGetNbArcArrivant();
	int SOMGetNbArcSortant();
	int SOMGetdernierSommet();
	void SOMAfficherSommet();
	int SOMgetDestArrivant(int iPos);
	int SOMgetDestSortant(int iPos);

	/**
	* @brief Permet d'inverser tout les arcs du sommet.
	* Une simple inversion entre A et B permet d'atteindre cela.
	*/
	void SOMInverserArcSom();

};

