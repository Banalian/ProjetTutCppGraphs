#include "Cgraphe.h"

/**
* @brief Constructeur par défaut
*/
Cgraphe::Cgraphe()
{
}

/**
* @brief Destructeur de Cgraphe
*/
Cgraphe::~Cgraphe()
{
}

/**
* @brief Permet d'ajouter un Sommet dans le graphe, sans aucun Arc
* @param iNum Le numero du sommet a ajouter
*/
void Cgraphe::GRAAddSommet(int iNum)
{
}

/**
* @brief Permet de supprimer un Sommet dans le graphe, ainsi que tout ses arcs (et les arcs dans les sommets relies a celui-ci)
* @param iNumSom Le numero du sommet a supprimer;
*/
void Cgraphe::GRADeleteSommet(int iNumSom)
{
}

/**
* @brief Permet d'ajouter un arc entre deux sommets
* @param iNumSommetDepart Le numero du sommet de depart
* @param iNumSommetArrive Le numero du sommet d'arrivee
*/
void Cgraphe::GRAAddArc(int iNumSommetDepart, int iNumSommetArrivee)
{
}

/**
* @brief Permet de supprimer un arc entre deux sommets
* @param iNumSommetDepart Le numero du sommet de depart
* @param iNumSommetArrive Le numero du sommet d'arrivee
*/
void Cgraphe::GRADeleteArc(int iNumSommetDepart, int iNumSommetArrivee)
{
}

/**
* @brief Affichage du graph oriente, en affichant tout les sommets existants, ainsi que les arcs sortant de ce sommet
* afin d'eviter une redondance en affichant les arcs entrant egalement
*/
void Cgraphe::GRAAfficherGraph()
{
}
