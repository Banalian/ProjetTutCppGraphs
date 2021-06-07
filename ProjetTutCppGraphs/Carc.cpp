#include "Carc.h"


/**
* @brief Constructeur de Carc, contenant le numero du sommet de destination
* @param iDest le sommet de destination
*/
Carc::Carc(int iDest)
{
	iDestination = iDest;
	iPoids = -1;
}

Carc::Carc(int iDest, int iStart, int iPoids)
{
	if (iPoids < 0) {
		throw Cexception(ErrPoidsNegatif);
	}
	this->iDestination = iDest;
	this->iDepart = iStart;
	this->iPoids = iPoids;
}

/**
* @brief Destructeur de Carc
*/
Carc::~Carc()
{
}

/**
* @brief Permet de modifier la destination de l'arc, si necessaire
* @param iNewDest la nouvelle destination de l'arc
*/
void Carc::ARCModifDest(int iNewDest)
{
	iDestination = iNewDest;
}

/**
* @brief Permet de recuperer le sommet de destination de l'arc
* @return le sommet de destination
*/
int Carc::ARCgetDest()
{
	return iDestination;
}

/**
* @brief Permet de recuperer le sommet de depart de l'arc
* @return le sommet de depart
*/
int Carc::ARCgetDepart()
{
	return iDepart;
}

/**
* @brief Permet de recuperer le poids de l'arc
* @return le poids
*/
int Carc::ARCgetPoids()
{
	return iPoids;
}
