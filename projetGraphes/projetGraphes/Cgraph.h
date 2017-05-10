#ifndef CGRAPH_H
#define CGRAPH_H

#include "Csommet.h"

/******************************************************************************
class Cgraph
*******************************************************************************

	Cette classe permet de simuler un graphe en contenant des noeuds qui eux même
	contiennent les informations qui les relient

	Attributs
		ppSOMGRAListSommets : La liste des sommets
		uiGRAnbrSommets : le nombre de sommets dans la liste

******************************************************************************/
class Cgraph
{
private :
	//########## Attributs ##########//
	Csommet ** ppSOMGRAListSommets;
	unsigned int uiGRAnbrSommets;

public :
	//########## Constructeurs - Destructeur ##########//
	/******************************************************************************
	Constructeur
	*******************************************************************************
	Entrée : Rien
	Necessité : Néant
	Sortie : Rien
	Entraine : L'objet a été initialisé
	******************************************************************************/
	Cgraph();
	/******************************************************************************
	Constructeur de recopie
	*******************************************************************************
	Entrée : Référence sur un objet de type Cgraph
	Necessité : Néant
	Sortie : Rien
	Entraine : L'objet a été initialisé par recopie de l'objet en paramètre
	******************************************************************************/
	Cgraph(const Cgraph & GRAObjet);
	/******************************************************************************
	Constructeur avec deux arguments
	*******************************************************************************
	Entrée : un pointeur sur une liste de pointeur sur des sommets et le nombre de sommet
	Necessité : Le nombre de sommets contenus dans la liste correspond à uiNbrSommets
	Sortie : Rien
	Entraine : L'objet a été initialisé
	******************************************************************************/
	Cgraph(Csommet *** pppSOMListSommets, unsigned int uiNbrSommets);
	/******************************************************************************
	Destructeur
	*******************************************************************************
	Entrée : Rien
	Necessité : L'arbre a été désalloué
	Sortie : Rien
	Entraine : L'espace alloué pour les attributs de l'objet a été libéré
	******************************************************************************/
	~Cgraph();

	//########## Methodes ##########/
	/******************************************************************************
	GRAajouterSommet
	*******************************************************************************
	Entrée : pSOMSommet un pointeur sur un sommet
	Necessité : Le sommet n'est pas déjà contenu dans le graph
	Sortie : Rien
	Entraine : le sommet a été ajouté au graph ou exception si déjà présent
	******************************************************************************/
	void GRAajouterSommet(Csommet * pSOMSommet);
	/******************************************************************************
	GRAsupprimerSommet
	*******************************************************************************
	Entrée : le numéro du sommet à supprimer
	Necessité : le numéro correspond à un sommet
	Sortie : Rien
	Entraine : le sommet a été supprimé du graph ou rien si sommet inexistant
	******************************************************************************/
	void GRAsupprimerSommet(unsigned int uiNumSommet);
	/******************************************************************************
	GRAmodifierSommet
	*******************************************************************************
	Entrée : le numéro du sommet à modifier et le nouveau numéro à lui appliquer
	Necessité : le sommet est existant et le nouveau n'est pas déjà pris
	Sortie : Rien
	Entraine : le sommet a été modifié
	******************************************************************************/
	void GRAmodifierSommet(unsigned int uiAncienNum, unsigned int uiNouveauNum);
	/******************************************************************************
	GRAajouterArc
	*******************************************************************************
	Entrée : les deux numéro des sommets à relier, le destinataire et le destinateur
	Necessité : les sommets existent
	Sortie : Rien
	Entraine : l'arc a été créé
	******************************************************************************/
	void GRAajouterArc(unsigned int uiNumSommetDebut, unsigned int uiNumSommetFin);
	/******************************************************************************
	GRASupprimerArc
	*******************************************************************************
	Entrée : les deux numéro des sommets à relier, le destinataire et le destinateur
	Necessité : les sommets et l'arc existent
	Sortie : Rien
	Entraine : l'arc a été supprimer
	******************************************************************************/
	void GRAsupprimerArc(unsigned int uiNumSommetDebut, unsigned int uiNumSommetFin);
	/******************************************************************************
	GRAafficherGraph
	*******************************************************************************
	Entrée : Rien
	Necessité : Néant
	Sortie : Rien
	Entraine : L'arc a été afficher sur la console
	******************************************************************************/
	void GRAafficherGraph();
	/******************************************************************************
	GRAvider
	*******************************************************************************
	Entrée : Rien
	Necessité : Néant
	Sortie : Rien
	Entraine : L'espace alloué pour les sommets et les arcs a été libéré
	******************************************************************************/
	void GRAvider();
	/******************************************************************************
	GRAinverser
	*******************************************************************************
	Entrée : Rien
	Necessité : Néant
	Sortie : Rien
	Entraine : Les arcs entrants ont été remplacés par les arcs sortant et vice-versa
	******************************************************************************/
	void GRAinverser();

	//########## Surcharge d'operateur ##########//
	/******************************************************************************
	surcharge de l'opérateur d'affectation
	*******************************************************************************
	Entrée : un objet du même type
	Necessité : Néant
	Sortie : Une référence sur l'objet en cours qui a été modifié
	Entraine : L'objet en cours est une copie de l'objet en paramètre
	******************************************************************************/
	Cgraph & operator=(Cgraph const & GRAObjet);
};

#endif