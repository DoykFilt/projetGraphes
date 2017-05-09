#include "Csommet.h"
#include <iostream>
#include "Cexception.h"

/******************************************************************************
Constructeur par d�faut
*******************************************************************************
	Entr�e : Rien
	Necessit� : N�ant
	Sortie : Rien
	Entraine : L'objet en cours est initialis�.
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
Constructeur � un argument
*******************************************************************************
	Entr�e : Num�ro de sommet de l'objet � initialiser
	Necessit� : N�ant
	Sortie : Rien
	Entraine : L'objet en cours est initialis�.
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
	Entr�e : Un objet de la classe
	Necessit� : N�ant
	Sortie : Rien
	Entraine : L'objet en cours est initialis�.
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
	Entr�e : Rien
	Necessit� : N�ant
	Sortie : Rien
	Entraine : L'objet en cours est initialis�.
******************************************************************************/
		Csommet::~Csommet()
		{
			free(ppARCSOMArcEntrant);
			free(ppARCSOMArcSortant);
		}

/******************************************************************************
M�thode de lecture du num�ro du sommet
*******************************************************************************
	Entr�e : Rien
	Necessit� : N�ant
	Sortie : Retourne le numero du sommet
	Entraine : N�ant.
******************************************************************************/
		unsigned int Csommet::SOMLireNumSommet()
		{
			return uiSOMNumSommet;
		}

/******************************************************************************
M�thode de modification du num�ro du sommet
*******************************************************************************
	Entr�e : Le nouveau num�ro de sommet
	Necessit� : le nouveau numero de sommet n'est pas existant
	Sortie : Rien
	Entraine : Le numero du sommet de l'objet est modifie.
******************************************************************************/
		void Csommet::SOMModifierSommet(unsigned int uiNouveauNumSommet)
		{
			uiSOMNumSommet=uiNouveauNumSommet;
		}

/******************************************************************************
M�thode de lecture du nombre d'arcs entrants
*******************************************************************************
	Entr�e : Rien
	Necessit� : N�ant
	Sortie : Retourne le nombre d'arcs entrant du sommet
	Entraine : N�ant.
******************************************************************************/
		unsigned int Csommet::SOMLireNbArcEntrant()
		{
			return uiSOMNbArcEntrant;
		}

/******************************************************************************
M�thode de lecture du nombre d'arcs sortants
*******************************************************************************
	Entr�e : Rien
	Necessit� : N�ant
	Sortie : Retourne le nombre d'arcs sortant du sommet
	Entraine : N�ant.
******************************************************************************/
		unsigned int Csommet::SOMLireNbArcSortant()
		{
			return uiSOMNbArcSortant;
		}

/******************************************************************************
M�thode pour ajouter un arc au sommet
*******************************************************************************
	Entr�e : la valeur du sommet de destination et si arc entrant ou sortant
	Necessit� : La destination pass�e en parametre est un sommet existant
	Sortie : Rien
	Entraine : Un arc est ajout� au sommet.
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
M�thode de modification d'un arc 
*******************************************************************************
	Entr�e : la valeur du sommet de destination initiale, si arc entrant ou sortant
			et le nouveau sommet destination de l'arc
	Necessit� : Les sommets pass�s en parametre doivent etre existant
	Sortie : Rien
	Entraine : l'arc est modifi�.
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
M�thode de suppression d'un arc 
*******************************************************************************
	Entr�e : la valeur du sommet de destination et si arc entrant ou sortant
	Necessit� : N�ant.
	Sortie : Rien
	Entraine : l'arc est supprim� si existant.
******************************************************************************/
		void Csommet::SOMSupprimerArc(unsigned int uiDestination, bool bEntrant) //pr�condition : arc existant
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