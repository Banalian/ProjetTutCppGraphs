#pragma once
#include "Carc.h"

class Csommet
{
private:

	int iNumero;
	static int idernierSommet; //Garde en mémoire le numero du dernier sommet cree

	Carc** pARCtabArrivant;
	Carc** pARCtabSortant;


public:

	Csommet();
	Csommet(int iNum);
	~Csommet();

	void SOMAddArcArrivant(Carc* pARCelem);
	void SOMAddArcSortant(Carc* pARCelem);

	void SOMDeleteArcArrivant(Carc* pARCelem);
	void SOMDeleteArcSortant(Carc* pARCelem);

	int SOMGetSomNum();
	int SOMGetdernierSommet();
	void SOMAfficherSommet();


};

