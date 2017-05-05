#include "Csommet.h"

        Csommet::Csommet()
		{
			pARCSOMArcEntrant=nullptr;
			pARCSOMArcSortant=nullptr;

		}

		Csommet::Csommet(unsigned int uiNumSommet)
		{
			uiSOMNumSommet=uiNumSommet;
			pARCSOMArcEntrant=nullptr;
			pARCSOMArcSortant=nullptr;
		}
		
		Csommet::Csommet(const Csommet & SOMObjet)
		{
			uiSOMNumSommet=SOMObjet.uiSOMNumSommet;

		
		
		}
		
		Csommet::~Csommet()
		{
			delete pARCSOMArcEntrant;
			delete pARCSOMArcSortant;
		}

		unsigned int Csommet::SOMLireNumSommet()
		{
			return uiSOMNumSommet;
		}

		void Csommet::SOMAjouterArc(unsigned int uiDestination, bool bEntrant)
		{
			if(bEntrant==true)
			{
				
			}
			else

		}
		
		void Csommet::SOMModifierArc(unsigned int uiDestinationInit, bool bEntrant, unsigned int uiNouvelleDestination)
		{
		
		}
		
		void Csommet::SOMSupprimerArc(unsigned int uiDestination, bool bEntrant)
		{
		
		}
