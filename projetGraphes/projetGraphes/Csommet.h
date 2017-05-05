#ifndef CSOMMET_H
#define CSOMMET_H

#include "Carc.h"

class Csommet
{
	//Attributs
	private :
		unsigned int uiSOMNumSommet;
		Carc ** pARCSOMArcEntrant;
		Carc ** pARCSOMArcSortant;

	public : 
		//constructeurs et destructeurs
		Csommet();
		Csommet(unsigned int uiNumSommet);
		Csommet(const Csommet & SOMObjet);
		~Csommet();

		//Méthodes
		unsigned int SOMLireNumSommet();
		void SOMAjouterArc(unsigned int uiDestination, bool bEntrant);
		void SOMModifierArc(unsigned int uiDestinationInit, bool bEntrant, unsigned int uiNouvelleDestination);
		void SOMSupprimerArc(unsigned int uiDestination, bool bEntrant);
		
};

#endif