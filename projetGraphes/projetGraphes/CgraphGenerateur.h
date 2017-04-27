#ifndef CGRAPHGENERATEUR
#define CGRAPHGENERATEUR

#include "Cparseur.h"

class CgraphGenerateur
{
private :
	Cparseur * pPARGRGparseur;

public :
	CgraphGenerateur();
	CgraphGenerateur(Cparseur * pPARparseur);
	CgraphGenerateur(const CgraphGenerateur & GRGObjet);
	~CgraphGenerateur();

	Cgraph GRGgenererGraph();
	void GRGsetParseur(Cparseur * PARparseur);
	Cparseur * GRGgetParseur();
	unsigned int PARreconnaitreEntier(char * pcElm);
};

#endif