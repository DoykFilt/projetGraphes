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

Cgraph * CgraphGenerateur::GRGgenererGraph()
{
	Cgraph * GRAgraph;
	unsigned int uiNbrSommets, uiNbrArcs;
	unsigned int uiCompteurPrincipal, uiCompteurSecondaire;
	char *** pppcBrut;

	if(pPARGRGparseur == nullptr)
		throw Cexception(ERREUR_PRECONDITIONS, "Parseur vide");
	pppcBrut = pPARGRGparseur->PARbrut();
	if(pppcBrut == nullptr)
		throw Cexception(ERREUR_PRECONDITIONS, "Parser le fichier avant");

	GRAgraph = new Cgraph();

	//On r�cup�re le nombre de sommets et d'arcs
	for(uiCompteurPrincipal = 0; uiCompteurPrincipal < pPARGRGparseur->PARLireNbrBalise(); uiCompteurPrincipal++)
		if(strcmp("NBSOMMETS", pppcBrut[uiCompteurPrincipal][0]) == 0)
			uiNbrSommets = GRGreconnaitreEntier(pppcBrut[uiCompteurPrincipal][1]);
		else if(strcmp("NBARCS", pppcBrut[uiCompteurPrincipal][0]) == 0)
			uiNbrArcs = GRGreconnaitreEntier(pppcBrut[uiCompteurPrincipal][1]);
	
	//Puis les sommets
	for(uiCompteurPrincipal = 0; uiCompteurPrincipal < pPARGRGparseur->PARLireNbrBalise(); uiCompteurPrincipal++)
		if(strcmp("SOMMETS", pppcBrut[uiCompteurPrincipal][0]) == 0)
			for(uiCompteurSecondaire = 0; uiCompteurSecondaire < uiNbrSommets; uiCompteurSecondaire++)
				GRAgraph->GRAajouterSommet(new Csommet(GRGreconnaitreEntier(pPARGRGparseur->PARvaleurSuivante("NUMERO", pppcBrut[uiCompteurPrincipal][1]))));

	//Et enfin les arcs
	for(uiCompteurPrincipal = 0; uiCompteurPrincipal < pPARGRGparseur->PARLireNbrBalise(); uiCompteurPrincipal++)
		if(strcmp("ARCS", pppcBrut[uiCompteurPrincipal][0]) == 0)
			for(uiCompteurSecondaire = 0; uiCompteurSecondaire < uiNbrSommets; uiCompteurSecondaire++)
				GRAgraph->GRAajouterArc(GRGreconnaitreEntier(pPARGRGparseur->PARvaleurSuivante("DEBUT", pppcBrut[uiCompteurPrincipal][1])),
										GRGreconnaitreEntier(pPARGRGparseur->PARvaleurSuivante("FIN", pppcBrut[uiCompteurPrincipal][1])));

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
Entr�e : une cha�ne de caract�res
Necessit� : le param�tre est convertible en int
Sortie : L'entier d�tect�
Entraine : L'entier retourn� est une taille valide
******************************************************************************/
unsigned int CgraphGenerateur::GRGreconnaitreEntier(char * pcElm)
{
	long int liTemp;
	//on utilise strtol au cas o� l'utilisateur aurait rentr� un long ou un double au lieu d'un int
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