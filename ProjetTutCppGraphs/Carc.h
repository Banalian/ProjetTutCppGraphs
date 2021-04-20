#pragma once
class Carc
{
private:
	int iDestination;
public:

	/**
	* @brief Constructeur de Carc, contenant le numero du sommet de destination
	* @param iDest le sommet de destination
	*/
	Carc(int iDest);
	
	/**
	* @brief Destructeur de Carc
	*/
	~Carc();

	/**
	* @brief Permet de modifier la destination de l'arc, si necessaire
	* @param iNewDest la nouvelle destination de l'arc
	*/
	void ARCModifDest(int iNewDest);

	/**
	* @brief Permet de recuperer le sommet de destination de l'arc
	* @return le sommet de destination
	*/
	int ARCgetDest();
};

