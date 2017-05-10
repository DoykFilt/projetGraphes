#ifndef CGRAPHGENERATEUR_H
#define CGRAPHGENERATEUR_H

#include "Cparseur.h"
#include "Cgraph.h"

class CgraphGenerateur
{
private :
	//Attributs
	Cparseur * pPARGRGparseur;

public :
	//Constructeurs - Desctructeur
	CgraphGenerateur();
	CgraphGenerateur(Cparseur * pPARparseur);
	CgraphGenerateur(const CgraphGenerateur & GRGObjet);
	~CgraphGenerateur();

	//Methodes
	Cgraph GRGgenererGraph();
	void GRGsetParseur(Cparseur * pPARparseur);
	Cparseur * GRGgetParseur();
	unsigned int PARreconnaitreEntier(char * pcElm);
	
	//Surcharge d'operateur
	CgraphGenerateur & operator=(CgraphGenerateur const & GRGObjet);
};

#endif