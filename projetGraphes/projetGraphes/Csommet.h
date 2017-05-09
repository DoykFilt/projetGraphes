#ifndef CSOMMET_H
#define CSOMMET_H

#include "Carc.h"

class Csommet
{
	//Attributs
	private :
		unsigned int uiSOMNumSommet;
		unsigned int uiSOMNbArcEntrant;
		unsigned int uiSOMNbArcSortant;
		Carc ** ppARCSOMArcEntrant;
		Carc ** ppARCSOMArcSortant;

	public : 
		//constructeurs et destructeurs
		Csommet();
		Csommet(unsigned int uiNumSommet);
		Csommet(const Csommet & SOMObjet);
		~Csommet();

		//Méthodes
		unsigned int SOMLireNumSommet();
		unsigned int SOMLireNbArcEntrant();
		unsigned int SOMLireNbArcSortant();
		void SOMAjouterArc(unsigned int uiDestination, bool bEntrant);
		void SOMModifierArc(unsigned int uiAncienneDestination, bool bEntrant, unsigned int uiNouvelleDestination);
		void SOMSupprimerArc(unsigned int uiDestination, bool bEntrant);
		void SOMModifierSommet(unsigned int uiNouveauNumSommet);
};

#endif