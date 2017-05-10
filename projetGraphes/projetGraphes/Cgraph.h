#ifndef CGRAPH_H
#define CGRAPH_H

#include "Csommet.h"

/******************************************************************************
class Cgraph
*******************************************************************************

	Cette classe permet de simuler un graphe en contenant des noeuds qui eux m�me
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
	Entr�e : Rien
	Necessit� : N�ant
	Sortie : Rien
	Entraine : L'objet a �t� initialis�
	******************************************************************************/
	Cgraph();
	/******************************************************************************
	Constructeur de recopie
	*******************************************************************************
	Entr�e : R�f�rence sur un objet de type Cgraph
	Necessit� : N�ant
	Sortie : Rien
	Entraine : L'objet a �t� initialis� par recopie de l'objet en param�tre
	******************************************************************************/
	Cgraph(const Cgraph & GRAObjet);
	/******************************************************************************
	Constructeur avec deux arguments
	*******************************************************************************
	Entr�e : un pointeur sur une liste de pointeur sur des sommets et le nombre de sommet
	Necessit� : Le nombre de sommets contenus dans la liste correspond � uiNbrSommets
	Sortie : Rien
	Entraine : L'objet a �t� initialis�
	******************************************************************************/
	Cgraph(Csommet *** pppSOMListSommets, unsigned int uiNbrSommets);
	/******************************************************************************
	Destructeur
	*******************************************************************************
	Entr�e : Rien
	Necessit� : L'arbre a �t� d�sallou�
	Sortie : Rien
	Entraine : L'espace allou� pour les attributs de l'objet a �t� lib�r�
	******************************************************************************/
	~Cgraph();

	//########## Methodes ##########/
	/******************************************************************************
	GRAajouterSommet
	*******************************************************************************
	Entr�e : pSOMSommet un pointeur sur un sommet
	Necessit� : Le sommet n'est pas d�j� contenu dans le graph
	Sortie : Rien
	Entraine : le sommet a �t� ajout� au graph ou exception si d�j� pr�sent
	******************************************************************************/
	void GRAajouterSommet(Csommet * pSOMSommet);
	/******************************************************************************
	GRAsupprimerSommet
	*******************************************************************************
	Entr�e : le num�ro du sommet � supprimer
	Necessit� : le num�ro correspond � un sommet
	Sortie : Rien
	Entraine : le sommet a �t� supprim� du graph ou rien si sommet inexistant
	******************************************************************************/
	void GRAsupprimerSommet(unsigned int uiNumSommet);
	/******************************************************************************
	GRAmodifierSommet
	*******************************************************************************
	Entr�e : le num�ro du sommet � modifier et le nouveau num�ro � lui appliquer
	Necessit� : le sommet est existant et le nouveau n'est pas d�j� pris
	Sortie : Rien
	Entraine : le sommet a �t� modifi�
	******************************************************************************/
	void GRAmodifierSommet(unsigned int uiAncienNum, unsigned int uiNouveauNum);
	/******************************************************************************
	GRAajouterArc
	*******************************************************************************
	Entr�e : les deux num�ro des sommets � relier, le destinataire et le destinateur
	Necessit� : les sommets existent
	Sortie : Rien
	Entraine : l'arc a �t� cr��
	******************************************************************************/
	void GRAajouterArc(unsigned int uiNumSommetDebut, unsigned int uiNumSommetFin);
	/******************************************************************************
	GRASupprimerArc
	*******************************************************************************
	Entr�e : les deux num�ro des sommets � relier, le destinataire et le destinateur
	Necessit� : les sommets et l'arc existent
	Sortie : Rien
	Entraine : l'arc a �t� supprimer
	******************************************************************************/
	void GRAsupprimerArc(unsigned int uiNumSommetDebut, unsigned int uiNumSommetFin);
	/******************************************************************************
	GRAafficherGraph
	*******************************************************************************
	Entr�e : Rien
	Necessit� : N�ant
	Sortie : Rien
	Entraine : L'arc a �t� afficher sur la console
	******************************************************************************/
	void GRAafficherGraph();
	/******************************************************************************
	GRAvider
	*******************************************************************************
	Entr�e : Rien
	Necessit� : N�ant
	Sortie : Rien
	Entraine : L'espace allou� pour les sommets et les arcs a �t� lib�r�
	******************************************************************************/
	void GRAvider();
	/******************************************************************************
	GRAinverser
	*******************************************************************************
	Entr�e : Rien
	Necessit� : N�ant
	Sortie : Rien
	Entraine : Les arcs entrants ont �t� remplac�s par les arcs sortant et vice-versa
	******************************************************************************/
	void GRAinverser();

	//########## Surcharge d'operateur ##########//
	/******************************************************************************
	surcharge de l'op�rateur d'affectation
	*******************************************************************************
	Entr�e : un objet du m�me type
	Necessit� : N�ant
	Sortie : Une r�f�rence sur l'objet en cours qui a �t� modifi�
	Entraine : L'objet en cours est une copie de l'objet en param�tre
	******************************************************************************/
	Cgraph & operator=(Cgraph const & GRAObjet);
};

#endif