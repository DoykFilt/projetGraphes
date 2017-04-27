#include <iostream>
#include "CgraphGenerateur.h"
#include "Cexception.h"


CgraphGenerateur::CgraphGenerateur()
{
	pPARGRGparseur = nullptr;
}

CgraphGenerateur::CgraphGenerateur(Cparseur * pPARparseur)
{
	pPARGRGparseur = pPARparseur;
}

CgraphGenerateur::CgraphGenerateur(const CgraphGenerateur & GRGObjet)
{
	pPARGRGparseur = GRGObjet.pPARGRGparseur;
}

CgraphGenerateur::~CgraphGenerateur(){}

Cgraph CgraphGenerateur::GRGgenererGraph()
{

}

void CgraphGenerateur::GRGsetParseur(Cparseur * PARparseur)
{
	pPARGRGparseur = PARparseur;
}

Cparseur * CgraphGenerateur::GRGgetParseur()
{
	return pPARGRGparseur;
}

/******************************************************************************
PARreconnaitreEntier
*******************************************************************************
Entr�e : une cha�ne de caract�res
Necessit� : le param�tre est convertible en int
Sortie : L'entier d�tect�
Entraine : L'entier retourn� est une taille valide
******************************************************************************/
unsigned int CgraphGenerateur::PARreconnaitreEntier(char * pcElm)
{
	long int liTemp;
	//on utilise strtol au cas o� l'utilisateur aurait rentr� un long ou un double au lieu d'un int
	liTemp = strtol(pcElm, NULL, 0);
	if(liTemp == 0L || liTemp == liTemp * (-1))
		throw Cexception(6, "Impossible de reconnaitre l'entier");

	if(liTemp < 0)
		throw Cexception(6, "Les parametres doivent etre positifs");

	return (unsigned int)liTemp;
}