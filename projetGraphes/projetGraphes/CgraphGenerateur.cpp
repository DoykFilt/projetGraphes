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
Entrée : une chaîne de caractères
Necessité : le paramètre est convertible en int
Sortie : L'entier détecté
Entraine : L'entier retourné est une taille valide
******************************************************************************/
unsigned int CgraphGenerateur::PARreconnaitreEntier(char * pcElm)
{
	long int liTemp;
	//on utilise strtol au cas où l'utilisateur aurait rentré un long ou un double au lieu d'un int
	liTemp = strtol(pcElm, NULL, 0);
	if(liTemp == 0L || liTemp == liTemp * (-1))
		throw Cexception(6, "Impossible de reconnaitre l'entier");

	if(liTemp < 0)
		throw Cexception(6, "Les parametres doivent etre positifs");

	return (unsigned int)liTemp;
}