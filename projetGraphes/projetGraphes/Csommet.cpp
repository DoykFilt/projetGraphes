#include "Csommet.h"
#include <iostream>
#include "Cexception.h"

/******************************************************************************
Constructeur par défaut
*******************************************************************************
	Entrée : Rien
	Necessité : Néant
	Sortie : Rien
	Entraine : L'objet en cours est initialisé.
******************************************************************************/
        Csommet::Csommet()
		{
			uiSOMNbArcEntrant=0;
			uiSOMNbArcSortant=0;
			ppARCSOMArcEntrant=(Carc**)malloc(uiSOMNbArcEntrant*sizeof(Carc*));
			if(ppARCSOMArcEntrant==nullptr)
				throw Cexception(MESSAGE_ALLOCATION);
			ppARCSOMArcSortant=(Carc**)malloc(uiSOMNbArcSortant*sizeof(Carc*));
			if(ppARCSOMArcSortant==nullptr)
				throw Cexception(MESSAGE_ALLOCATION);

		}

/******************************************************************************
Constructeur à un argument
*******************************************************************************
	Entrée : Numéro de sommet de l'objet à initialiser
	Necessité : Néant
	Sortie : Rien
	Entraine : L'objet en cours est initialisé.
******************************************************************************/
		Csommet::Csommet(unsigned int uiNumSommet)
		{
			uiSOMNumSommet=uiNumSommet;
			uiSOMNbArcEntrant=0;
			uiSOMNbArcSortant=0;
			ppARCSOMArcEntrant=(Carc**)malloc(uiSOMNbArcEntrant*sizeof(Carc*));
			if(ppARCSOMArcEntrant==nullptr)
				throw Cexception(MESSAGE_ALLOCATION);
			ppARCSOMArcSortant=(Carc**)malloc(uiSOMNbArcSortant*sizeof(Carc*));
			if(ppARCSOMArcSortant==nullptr)
				throw Cexception(MESSAGE_ALLOCATION);

		}
		
/******************************************************************************
Constructeur de recopie
*******************************************************************************
	Entrée : Un objet de la classe
	Necessité : Néant
	Sortie : Rien
	Entraine : L'objet en cours est initialisé.
******************************************************************************/
		Csommet::Csommet(const Csommet & SOMObjet)
		{
			uiSOMNumSommet=SOMObjet.uiSOMNumSommet;
			uiSOMNbArcEntrant=SOMObjet.uiSOMNbArcEntrant;
			uiSOMNbArcSortant=SOMObjet.uiSOMNbArcSortant;
			ppARCSOMArcEntrant=(Carc**)malloc(uiSOMNbArcEntrant*sizeof(Carc*));
			if(ppARCSOMArcSortant==nullptr)
				throw Cexception(MESSAGE_ALLOCATION);
			ppARCSOMArcSortant=(Carc**)malloc(uiSOMNbArcSortant*sizeof(Carc*));
			if(ppARCSOMArcSortant==nullptr)
				throw Cexception(MESSAGE_ALLOCATION);
			unsigned int uiCompteurArc;
			unsigned int uiCompteurArc;

			for(uiCompteurArc=0; uiCompteurArc < uiSOMNbArcEntrant; uiCompteurArc++)
			{
				ppARCSOMArcEntrant[uiCompteurArc] =  SOMObjet.ppARCSOMArcEntrant[uiCompteurArc];
			}

			for(uiCompteurArc=0; uiCompteurArc < uiSOMNbArcSortant; uiCompteurArc++)
			{
				ppARCSOMArcSortant[uiCompteurArc] =  SOMObjet.ppARCSOMArcSortant[uiCompteurArc];
			}
		
		}

/******************************************************************************
Destructeur par defaut
*******************************************************************************
	Entrée : Rien
	Necessité : Néant
	Sortie : Rien
	Entraine : L'objet en cours est initialisé.
******************************************************************************/
		Csommet::~Csommet()
		{
			free(ppARCSOMArcEntrant);
			free(ppARCSOMArcSortant);
		}

/******************************************************************************
Méthode de lecture du numéro du sommet
*******************************************************************************
	Entrée : Rien
	Necessité : Néant
	Sortie : Retourne le numero du sommet
	Entraine : Néant.
******************************************************************************/
		unsigned int Csommet::SOMLireNumSommet()
		{
			return uiSOMNumSommet;
		}

/******************************************************************************
Méthode de modification du numéro du sommet
*******************************************************************************
	Entrée : Le nouveau numéro de sommet
	Necessité : le nouveau numero de sommet n'est pas existant
	Sortie : Rien
	Entraine : Le numero du sommet de l'objet est modifie.
******************************************************************************/
		void Csommet::SOMModifierSommet(unsigned int uiNouveauNumSommet)
		{
			uiSOMNumSommet=uiNouveauNumSommet;
		}

/******************************************************************************
Méthode de lecture du nombre d'arcs entrants
*******************************************************************************
	Entrée : Rien
	Necessité : Néant
	Sortie : Retourne le nombre d'arcs entrant du sommet
	Entraine : Néant.
******************************************************************************/
		unsigned int Csommet::SOMLireNbArcEntrant()
		{
			return uiSOMNbArcEntrant;
		}

/******************************************************************************
Méthode de lecture du nombre d'arcs sortants
*******************************************************************************
	Entrée : Rien
	Necessité : Néant
	Sortie : Retourne le nombre d'arcs sortant du sommet
	Entraine : Néant.
******************************************************************************/
		unsigned int Csommet::SOMLireNbArcSortant()
		{
			return uiSOMNbArcSortant;
		}

/******************************************************************************
Méthode pour ajouter un arc au sommet
*******************************************************************************
	Entrée : la valeur du sommet de destination et si arc entrant ou sortant
	Necessité : La destination passée en parametre est un sommet existant
	Sortie : Rien
	Entraine : Un arc est ajouté au sommet.
******************************************************************************/
		void Csommet::SOMAjouterArc(unsigned int uiDestination, bool bEntrant)
		{
			unsigned int uiCompteurArc;
			if(bEntrant==true)
			{
				for(uiCompteurArc=0; uiCompteurArc < uiSOMNbArcEntrant; uiCompteurArc++)
				{
					if(ppARCSOMArcEntrant[uiCompteurArc]->ARCLireDestination() == uiDestination)
						throw Cexception(ERREUR_PARAM, "Arc Existant");
				}

				uiSOMNbArcEntrant++;
				ppARCSOMArcEntrant=(Carc**)realloc(ppARCSOMArcEntrant, uiSOMNbArcEntrant*sizeof(Carc*));
				if(ppARCSOMArcEntrant==nullptr)
					throw Cexception(MESSAGE_REALLOCATION);
				Carc * nouveauArc = new Carc(uiDestination);
				ppARCSOMArcEntrant[uiSOMNbArcEntrant-1] = nouveauArc;
			}
			else
			{
				for(uiCompteurArc=0; uiCompteurArc < uiSOMNbArcSortant; uiCompteurArc++)
				{
					if(ppARCSOMArcSortant[uiCompteurArc]->ARCLireDestination() == uiDestination)
						throw Cexception(ERREUR_PARAM, "Arc Existant");
				}

				uiSOMNbArcSortant++;
				ppARCSOMArcSortant=(Carc**)realloc(ppARCSOMArcSortant, uiSOMNbArcSortant*sizeof(Carc*));
				if(ppARCSOMArcSortant==nullptr)
					throw Cexception(MESSAGE_REALLOCATION);
				Carc * nouveauArc = new Carc(uiDestination);
				ppARCSOMArcSortant[uiSOMNbArcSortant-1] = nouveauArc;
			}
		}
			
/******************************************************************************
Méthode de modification d'un arc 
*******************************************************************************
	Entrée : la valeur du sommet de destination initiale, si arc entrant ou sortant
			et le nouveau sommet destination de l'arc
	Necessité : Les sommets passés en parametre doivent etre existant
	Sortie : Rien
	Entraine : l'arc est modifié.
******************************************************************************/
		void Csommet::SOMModifierArc(unsigned int uiAncienneDestination, bool bEntrant, unsigned int uiNouvelleDestination) 
		{
			unsigned int uiCompteurArc;
			if(bEntrant==true)
			{
				for(uiCompteurArc=0; uiCompteurArc < uiSOMNbArcEntrant; uiCompteurArc++)
				{ 
					if(ppARCSOMArcEntrant[uiCompteurArc]->ARCLireDestination() == uiNouvelleDestination)
						throw Cexception(ERREUR_PARAM, "Arc Existant");
					if(ppARCSOMArcEntrant[uiCompteurArc]->ARCLireDestination() == uiAncienneDestination)
						ppARCSOMArcEntrant[uiCompteurArc]->ARCModifierDestination(uiNouvelleDestination);
				}
			}
			else
			{
				for(uiCompteurArc=0; uiCompteurArc < uiSOMNbArcSortant; uiCompteurArc++)
				{
					if(ppARCSOMArcSortant[uiCompteurArc]->ARCLireDestination() == uiNouvelleDestination)
						throw Cexception(ERREUR_PARAM, "Arc Existant");
					if(ppARCSOMArcSortant[uiCompteurArc]->ARCLireDestination() == uiAncienneDestination)
						ppARCSOMArcEntrant[uiCompteurArc]->ARCModifierDestination(uiNouvelleDestination);
				}
			}
		}
		
/******************************************************************************
Méthode de suppression d'un arc 
*******************************************************************************
	Entrée : la valeur du sommet de destination et si arc entrant ou sortant
	Necessité : Néant.
	Sortie : Rien
	Entraine : l'arc est supprimé si existant.
******************************************************************************/
		void Csommet::SOMSupprimerArc(unsigned int uiDestination, bool bEntrant) //précondition : arc existant
		{
			unsigned int uiCompteurArc;

			if(bEntrant==true)
			{
				while(ppARCSOMArcEntrant[uiCompteurArc]->ARCLireDestination() != uiDestination && uiCompteurArc < uiSOMNbArcEntrant )
				{
					uiCompteurArc++;
				}
				
				if(ppARCSOMArcEntrant[uiCompteurArc]->ARCLireDestination() == uiDestination && uiCompteurArc < uiSOMNbArcEntrant)
					free(ppARCSOMArcEntrant[uiCompteurArc]);

				while(uiCompteurArc< uiSOMNbArcEntrant-1)
				{
						ppARCSOMArcEntrant[uiCompteurArc]=ppARCSOMArcEntrant[uiCompteurArc+1];
						uiCompteurArc++;
				}

				uiSOMNbArcEntrant--;
				ppARCSOMArcEntrant=(Carc**)realloc(ppARCSOMArcEntrant, uiSOMNbArcEntrant*sizeof(Carc*));
				if(ppARCSOMArcEntrant==nullptr)
					throw Cexception(MESSAGE_REALLOCATION);

			}
			else
			{
				while(ppARCSOMArcSortant[uiCompteurArc]->ARCLireDestination() != uiDestination && uiCompteurArc < uiSOMNbArcSortant )
				{
					uiCompteurArc++;
				}
				
				if(ppARCSOMArcSortant[uiCompteurArc]->ARCLireDestination() == uiDestination && uiCompteurArc < uiSOMNbArcSortant)
					free(ppARCSOMArcSortant[uiCompteurArc]);

				while(uiCompteurArc< uiSOMNbArcSortant-1)
				{
						ppARCSOMArcSortant[uiCompteurArc]=ppARCSOMArcSortant[uiCompteurArc+1];
						uiCompteurArc++;
				}

				uiSOMNbArcSortant--;
				ppARCSOMArcSortant=(Carc**)realloc(ppARCSOMArcSortant, uiSOMNbArcSortant*sizeof(Carc*));
				if(ppARCSOMArcSortant==nullptr)
					throw Cexception(MESSAGE_REALLOCATION);
			}
		}