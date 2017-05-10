#ifndef CGRAPH_H
#define CGRAPH_H

#include "Csommet.h"

//*GERER LES EXCEPTIONS LORS DE LA GESTION D'ARCS SUR DES SOMMETS QUI N'EXISTENT PAS*//

class Cgraph
{
private :
	//Attributs
	Csommet ** ppSOMGRAListSommets;
	unsigned int uiGRAnbrSommets;

public :
	//Constructeurs - Destructeur
	Cgraph();
	Cgraph(const Cgraph & GRAObjet);
	Cgraph(Csommet *** pppSOMListSommets, unsigned int uiNbrSommets);
	~Cgraph();

	//Methodes
	void GRAajouterSommet(Csommet * pSOMSommet);
	void GRAsupprimerSommet(unsigned int uiNumSommet);
	void GRAmodifierSommet(unsigned int uiAncienNum, unsigned int uiNouveauNum);
	void GRAajouterArc(unsigned int uiNumSommetDebut, unsigned int uiNumSommetFin);
	void GRAsupprimerArc(unsigned int uiNumSommetDebut, unsigned int uiNumSommetFin);
	void GRAafficherGraph();
	void GRAdeleteAll();

	//Surcharge d'operateur
	Cgraph & operator=(Cgraph const & GRAObjet);
};

#endif