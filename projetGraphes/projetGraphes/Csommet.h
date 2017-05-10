#ifndef CSOMMET_H
#define CSOMMET_H

#include "Carc.h"

class Csommet
{

	private :
		/******************************************************************************
		Attribut numero du sommet de l'objet
		******************************************************************************/
		unsigned int uiSOMNumSommet;

		/******************************************************************************
		Attribut nombre d'arcs entrants de l'objet
		******************************************************************************/
		unsigned int uiSOMNbArcEntrant;

		/******************************************************************************
		Attribut nombre d'arcs sortants de l'objet
		******************************************************************************/
		unsigned int uiSOMNbArcSortant;

		/******************************************************************************
		Attribut contenant les arcs entrants
		******************************************************************************/
		Carc ** ppARCSOMArcEntrant;

		/******************************************************************************
		Attributs contenant les arcs sortants
		******************************************************************************/
		Carc ** ppARCSOMArcSortant;

	public : 
		/******************************************************************************
		Constructeur par d�faut
		*******************************************************************************
			Entr�e : Rien
			Necessit� : N�ant
			Sortie : Rien
			Entraine : L'objet en cours est initialis�.
		******************************************************************************/
		Csommet();

		/******************************************************************************
		Constructeur � un argument
		*******************************************************************************
			Entr�e : Num�ro de sommet de l'objet � initialiser
			Necessit� : N�ant
			Sortie : Rien
			Entraine : L'objet en cours est initialis�.
		******************************************************************************/
		Csommet(unsigned int uiNumSommet);

		/******************************************************************************
		Constructeur de recopie
		*******************************************************************************
			Entr�e : Un objet de la classe
			Necessit� : N�ant
			Sortie : Rien
			Entraine : L'objet en cours est initialis�.
		******************************************************************************/
		Csommet(const Csommet & SOMObjet);

		/******************************************************************************
		Destructeur par defaut
		*******************************************************************************
			Entr�e : Rien
			Necessit� : N�ant
			Sortie : Rien
			Entraine : L'objet en cours est initialis�.
		******************************************************************************/
		~Csommet();

		/******************************************************************************
		M�thode de lecture du num�ro du sommet
		*******************************************************************************
			Entr�e : Rien
			Necessit� : N�ant
			Sortie : Retourne le numero du sommet
			Entraine : N�ant.
		******************************************************************************/
		unsigned int SOMLireNumSommet();

		/******************************************************************************
		M�thode de modification du num�ro du sommet
		*******************************************************************************
			Entr�e : Le nouveau num�ro de sommet
			Necessit� : le nouveau numero de sommet n'est pas existant
			Sortie : Rien
			Entraine : Le numero du sommet de l'objet est modifie.
		******************************************************************************/
		void SOMModifierSommet(unsigned int uiNouveauNumSommet);

		/******************************************************************************
		M�thode de lecture du nombre d'arcs entrants
		*******************************************************************************
			Entr�e : Rien
			Necessit� : N�ant
			Sortie : Retourne le nombre d'arcs entrant du sommet
			Entraine : N�ant.
		******************************************************************************/
		unsigned int SOMLireNbArcEntrant();

		/******************************************************************************
		M�thode de lecture du nombre d'arcs sortants
		*******************************************************************************
			Entr�e : Rien
			Necessit� : N�ant
			Sortie : Retourne le nombre d'arcs sortant du sommet
			Entraine : N�ant.
		******************************************************************************/
		unsigned int SOMLireNbArcSortant();

		/******************************************************************************
		M�thode pour ajouter un arc au sommet
		*******************************************************************************
			Entr�e : la valeur du sommet de destination et si arc entrant ou sortant
			Necessit� : La destination pass�e en parametre est un sommet existant
			Sortie : Rien
			Entraine : Un arc est ajout� au sommet.
		******************************************************************************/
		void SOMAjouterArc(unsigned int uiDestination, bool bEntrant);

		/******************************************************************************
		M�thode de modification d'un arc 
		*******************************************************************************
			Entr�e : la valeur du sommet de destination initiale, si arc entrant ou sortant
					et le nouveau sommet destination de l'arc
			Necessit� : Les sommets pass�s en parametre doivent etre existant
			Sortie : Rien
			Entraine : l'arc est modifi�.
		******************************************************************************/
		void SOMModifierArc(unsigned int uiAncienneDestination, bool bEntrant, unsigned int uiNouvelleDestination);

		/******************************************************************************
		M�thode de suppression d'un arc 
		*******************************************************************************
			Entr�e : la valeur du sommet de destination et si arc entrant ou sortant
			Necessit� : N�ant.
			Sortie : Rien
			Entraine : l'arc est supprim� si existant.
		******************************************************************************/
		void SOMSupprimerArc(unsigned int uiDestination, bool bEntrant);
		
		/******************************************************************************
		M�thode de lecture de la liste des arcs
		*******************************************************************************
			Entr�e : vrai pour obtenir la liste des arcs entrant, faux sinon
			Necessit� : N�ant.
			Sortie : Un pointeur sur la liste des arcs
			Entraine : La bonne liste d'arcs est renvoy�e
		******************************************************************************/
		Carc ** SOMLireArcs(bool bEntrant);
};

#endif