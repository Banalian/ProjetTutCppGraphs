#pragma once
class Carc
{
private:
	/** variable contenant la destination de l'arc (qui n'indique pas forcement le sens de l'arc) */
	int iDestination;
	int iPoids;
public:

	/**
	* @brief Constructeur de Carc, contenant le numero du sommet de destination
	* @param iDest le sommet de destination
	* par defaut la taille sera consideree comme infinie (-1)
	*/
	Carc(int iDest);
	
	/**
	* @brief Constructeur de Carc, contenant le numero du sommet de destination
	* @param iDest le sommet de destination
	* @param iPoids le poids de l'arete
	*/
	Carc(int iDest, int iPoids);

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

