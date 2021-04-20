#pragma once
#include "Carc.h"

class Csommet
{
private:

	int iNumero;

	Carc** pARCtabArrivant;
	Carc** pARCtabSortant;


public:

	Csommet(int iNum);
	~Csommet();

	void SOMAddArcArrivant(Carc* pARCelem);
	void SOMAddArcSortant(Carc* pARCelem);

	void SOMDeleteArcArrivant(Carc* pARCelem);
	void SOMDeleteArcSortant(Carc* pARCelem);

	int SOMGetSomNum();
	void SOMAfficherSommet();


};

