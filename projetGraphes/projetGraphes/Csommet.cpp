#include "Csommet.h"
#include <iostream>
#include "Cexception.h"

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
		
		Csommet::~Csommet()
		{
			free(ppARCSOMArcEntrant);
			free(ppARCSOMArcSortant);
		}

		unsigned int Csommet::SOMLireNumSommet()
		{
			return uiSOMNumSommet;
		}

		unsigned int Csommet::SOMLireNbArcEntrant()
		{
			return uiSOMNbArcEntrant;
		}

		unsigned int Csommet::SOMLireNbArcSortant()
		{
			return uiSOMNbArcSortant;
		}

		void Csommet::SOMAjouterArc(unsigned int uiDestination, bool bEntrant) //précondition : uiDestination = sommet existant
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
		
		void Csommet::SOMModifierArc(unsigned int uiAncienneDestination, bool bEntrant, unsigned int uiNouvelleDestination) // précondition : sommet existant 
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

		void Csommet::SOMModifierSommet(unsigned int uiNouveauNumSommet)
		{
			uiSOMNumSommet=uiNouveauNumSommet;
		}
