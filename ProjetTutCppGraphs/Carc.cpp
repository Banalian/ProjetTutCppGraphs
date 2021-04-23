#include "Carc.h"

/**
* @brief Constructeur de Carc, contenant le numero du sommet de destination
* @param iDest le sommet de destination
*/
Carc::Carc(int iDest)
{
	iDestination = iDest;
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
