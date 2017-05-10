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
		Constructeur par défaut
		*******************************************************************************
			Entrée : Rien
			Necessité : Néant
			Sortie : Rien
			Entraine : L'objet en cours est initialisé.
		******************************************************************************/
		Csommet();

		/******************************************************************************
		Constructeur à un argument
		*******************************************************************************
			Entrée : Numéro de sommet de l'objet à initialiser
			Necessité : Néant
			Sortie : Rien
			Entraine : L'objet en cours est initialisé.
		******************************************************************************/
		Csommet(unsigned int uiNumSommet);

		/******************************************************************************
		Constructeur de recopie
		*******************************************************************************
			Entrée : Un objet de la classe
			Necessité : Néant
			Sortie : Rien
			Entraine : L'objet en cours est initialisé.
		******************************************************************************/
		Csommet(const Csommet & SOMObjet);

		/******************************************************************************
		Destructeur par defaut
		*******************************************************************************
			Entrée : Rien
			Necessité : Néant
			Sortie : Rien
			Entraine : L'objet en cours est initialisé.
		******************************************************************************/
		~Csommet();

		/******************************************************************************
		Méthode de lecture du numéro du sommet
		*******************************************************************************
			Entrée : Rien
			Necessité : Néant
			Sortie : Retourne le numero du sommet
			Entraine : Néant.
		******************************************************************************/
		unsigned int SOMLireNumSommet();

		/******************************************************************************
		Méthode de modification du numéro du sommet
		*******************************************************************************
			Entrée : Le nouveau numéro de sommet
			Necessité : le nouveau numero de sommet n'est pas existant
			Sortie : Rien
			Entraine : Le numero du sommet de l'objet est modifie.
		******************************************************************************/
		void SOMModifierSommet(unsigned int uiNouveauNumSommet);

		/******************************************************************************
		Méthode de lecture du nombre d'arcs entrants
		*******************************************************************************
			Entrée : Rien
			Necessité : Néant
			Sortie : Retourne le nombre d'arcs entrant du sommet
			Entraine : Néant.
		******************************************************************************/
		unsigned int SOMLireNbArcEntrant();

		/******************************************************************************
		Méthode de lecture du nombre d'arcs sortants
		*******************************************************************************
			Entrée : Rien
			Necessité : Néant
			Sortie : Retourne le nombre d'arcs sortant du sommet
			Entraine : Néant.
		******************************************************************************/
		unsigned int SOMLireNbArcSortant();

		/******************************************************************************
		Méthode pour ajouter un arc au sommet
		*******************************************************************************
			Entrée : la valeur du sommet de destination et si arc entrant ou sortant
			Necessité : La destination passée en parametre est un sommet existant
			Sortie : Rien
			Entraine : Un arc est ajouté au sommet.
		******************************************************************************/
		void SOMAjouterArc(unsigned int uiDestination, bool bEntrant);

		/******************************************************************************
		Méthode de modification d'un arc 
		*******************************************************************************
			Entrée : la valeur du sommet de destination initiale, si arc entrant ou sortant
					et le nouveau sommet destination de l'arc
			Necessité : Les sommets passés en parametre doivent etre existant
			Sortie : Rien
			Entraine : l'arc est modifié.
		******************************************************************************/
		void SOMModifierArc(unsigned int uiAncienneDestination, bool bEntrant, unsigned int uiNouvelleDestination);

		/******************************************************************************
		Méthode de suppression d'un arc 
		*******************************************************************************
			Entrée : la valeur du sommet de destination et si arc entrant ou sortant
			Necessité : Néant.
			Sortie : Rien
			Entraine : l'arc est supprimé si existant.
		******************************************************************************/
		void SOMSupprimerArc(unsigned int uiDestination, bool bEntrant);
		
		/******************************************************************************
		Méthode de lecture de la liste des arcs
		*******************************************************************************
			Entrée : vrai pour obtenir la liste des arcs entrant, faux sinon
			Necessité : Néant.
			Sortie : Un pointeur sur la liste des arcs
			Entraine : La bonne liste d'arcs est renvoyée
		******************************************************************************/
		Carc ** SOMLireArcs(bool bEntrant);
};

#endif