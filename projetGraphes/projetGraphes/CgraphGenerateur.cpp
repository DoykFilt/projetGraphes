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
	Cgraph * GRAgraph;
	Csommet * SOMsommet;
	unsigned int uiNbrSommets, uiNbrArcs;
	unsigned int uiCompteurPrincipal, uiCompteurSecondaire;
	char *** brut;

	if(pPARGRGparseur == nullptr)
		throw Cexception(ERREUR_PRECONDITIONS, "Parseur vide");
	brut = pPARGRGparseur->PARbrut();
	if(brut == nullptr)
		throw Cexception(ERREUR_PRECONDITIONS, "Parser le fichier avant");

	GRAgraph = new Cgraph();

	//On récupère le nombre de sommets et d'arcs
	for(uiCompteurPrincipal = 0; uiCompteurPrincipal < pPARGRGparseur->PARLireNbrBalise(); uiCompteurPrincipal++)
		if(strcmp("NBRSOMMETS", pPARGRGparseur->PARbrut[uiCompteurPrincipal][0]) == 0)
			uiNbrSommets = pPARGRGparseur->PARbrut[uiCompteurPrincipal][0];
		else if(strcmp("NBRARCS", pPARGRGparseur->PARbrut[uiCompteurPrincipal][0]) == 0)
			uiNbrArcs = pPARGRGparseur->PARbrut[uiCompteurPrincipal][0];
	
	//Puis les sommets
	for(uiCompteurPrincipal = 0; uiCompteurPrincipal < pPARGRGparseur->PARLireNbrBalise(); uiCompteurPrincipal++)
		if(strcmp("SOMMETS", pPARGRGparseur->PARbrut[uiCompteurPrincipal][0]) == 0)
			for(uiCompteurSecondaire = 0; uiCompteurSecondaire < uiNbrSommets; uiCompteurSecondaire++)
			{
				SOMsommet = new Csommet(pPARGRGparseur->PARvaleurSuivante("SOMMET", pPARGRGparseur->PARbrut[uiCompteurPrincipal][1]));
				GRAgraph->GRAAjouterSommet(SOMsommet);
			}

	//Et enfin les arcs
	for(uiCompteurPrincipal = 0; uiCompteurPrincipal < pPARGRGparseur->PARLireNbrBalise(); uiCompteurPrincipal++)
		if(strcmp("ARCS", pPARGRGparseur->PARbrut[uiCompteurPrincipal][0]) == 0)
			for(uiCompteurSecondaire = 0; uiCompteurSecondaire < uiNbrSommets; uiCompteurSecondaire++)
				GRAgraph->GRAAjouterArc(pPARGRGparseur->PARvaleurSuivante("DEBUT", pPARGRGparseur->PARbrut[uiCompteurPrincipal][1]),
										pPARGRGparseur->PARvaleurSuivante("FIN", pPARGRGparseur->PARbrut[uiCompteurPrincipal][1]));

	return GRAgraph;
}

void CgraphGenerateur::GRGsetParseur(Cparseur * pPARparseur)
{
	pPARGRGparseur = pPARparseur;
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
		throw Cexception(ERREUR_PARSEUR, "Impossible de reconnaitre l'entier");

	if(liTemp < 0)
		throw Cexception(ERREUR_PARSEUR, "Les parametres doivent etre positifs");

	return (unsigned int)liTemp;
}

CgraphGenerateur & CgraphGenerateur::operator=(CgraphGenerateur const & GRGObjet)
{
	pPARGRGparseur = GRGObjet.pPARGRGparseur;

	return *this;
}