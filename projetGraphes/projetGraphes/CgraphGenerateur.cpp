#include <iostream>
#include "CgraphGenerateur.h"
#include "Cexception.h"


/******************************************************************************
Constructeur
*******************************************************************************
Entrée : Rien
Necessité : Néant
Sortie : Rien
Entraine : L'objet a été initialisé
******************************************************************************/
CgraphGenerateur::CgraphGenerateur()
{
	pPARGRGparseur = nullptr;
}
/******************************************************************************
Constructeur avec un argument
*******************************************************************************
Entrée : un pointeur sur un objet de type Cparseur
Necessité : Néant
Sortie : Rien
Entraine : L'objet a été initialisé
******************************************************************************/
CgraphGenerateur::CgraphGenerateur(Cparseur * pPARparseur)
{
	pPARGRGparseur = pPARparseur;
}
/******************************************************************************
Constructeur de recopie
*******************************************************************************
Entrée : Référence sur un objet de type CgraphGenerateur
Necessité : Néant
Sortie : Rien
Entraine : L'objet a été initialisé par recopie de l'objet en paramètre
******************************************************************************/
CgraphGenerateur::CgraphGenerateur(const CgraphGenerateur & GRGObjet)
{
	pPARGRGparseur = GRGObjet.pPARGRGparseur;
}
/******************************************************************************
Destructeur
*******************************************************************************
Entrée : Rien
Necessité : L'arbre a été désalloué
Sortie : Rien
Entraine : L'espace alloué pour les attributs de l'objet a été libéré
******************************************************************************/
CgraphGenerateur::~CgraphGenerateur(){}

/******************************************************************************
GRGgenererGraph
*******************************************************************************
Entrée : Rien
Necessité : Le parseur a récupéré les données brutes préalablement
Sortie : l'objet reconnu de type Cgraph 
Entraine : un objet de type Cgraph a été alloué et retourné
******************************************************************************/
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

	//On récupère le nombre de sommets et d'arcs
	for(uiCompteurPrincipal = 0; uiCompteurPrincipal < pPARGRGparseur->PARLireNbrBalise(); uiCompteurPrincipal++)
		if(strcmp("NBSOMMETS", pppcBrut[uiCompteurPrincipal][0]) == 0)
			uiNbrSommets = GRGreconnaitreEntier(pppcBrut[uiCompteurPrincipal][1]);
		else if(strcmp("NBARCS", pppcBrut[uiCompteurPrincipal][0]) == 0)
			uiNbrArcs = GRGreconnaitreEntier(pppcBrut[uiCompteurPrincipal][1]);
	
	//Puis les sommets
	for(uiCompteurPrincipal = 0; uiCompteurPrincipal < pPARGRGparseur->PARLireNbrBalise(); uiCompteurPrincipal++)
		if(strcmp("SOMMETS", pppcBrut[uiCompteurPrincipal][0]) == 0)
			for(uiCompteurSecondaire = 0; uiCompteurSecondaire < uiNbrSommets; uiCompteurSecondaire++)
			{
				try
				{
					GRAgraph->GRAajouterSommet(new Csommet(GRGreconnaitreEntier(pPARGRGparseur->PARvaleurSuivante("NUMERO", pppcBrut[uiCompteurPrincipal][1]))));
				}
				catch(Cexception EXCexception)
				{
					cout << "Erreur " << EXCexception.EXCLire_Valeur();
					cout << " " << EXCexception.EXCLire_Message() << endl;
				}
			}

	//Et enfin les arcs
	for(uiCompteurPrincipal = 0; uiCompteurPrincipal < pPARGRGparseur->PARLireNbrBalise(); uiCompteurPrincipal++)
		if(strcmp("ARCS", pppcBrut[uiCompteurPrincipal][0]) == 0)
			for(uiCompteurSecondaire = 0; uiCompteurSecondaire < uiNbrArcs; uiCompteurSecondaire++)
			{
				try
				{
					GRAgraph->GRAajouterArc(GRGreconnaitreEntier(pPARGRGparseur->PARvaleurSuivante("DEBUT", pppcBrut[uiCompteurPrincipal][1])),
											GRGreconnaitreEntier(pPARGRGparseur->PARvaleurSuivante("FIN", pppcBrut[uiCompteurPrincipal][1])));
				}
				catch(Cexception EXCexception)
				{
					cout << "Erreur " << EXCexception.EXCLire_Valeur();
					cout << " " << EXCexception.EXCLire_Message() << endl;
				}
			}

	return GRAgraph;
}

/******************************************************************************
GRGsetParseur
*******************************************************************************
Entrée : Un pointeur sur un objet de type Cparseur
Necessité : Néant
Sortie : Rien
Entraine : L'ancien parseur a été remplacé par le nouveau
******************************************************************************/
void CgraphGenerateur::GRGsetParseur(Cparseur * pPARparseur)
{
	pPARGRGparseur = pPARparseur;
}

/******************************************************************************
GRGgetParseur
*******************************************************************************
Entrée : Rien
Necessité : Néant
Sortie : Un poiteur sur le parseur
Entraine : Le pointeur a été retourné
******************************************************************************/
Cparseur * CgraphGenerateur::GRGgetParseur()
{
	return pPARGRGparseur;
}

/******************************************************************************
GRGreconnaitreEntier
*******************************************************************************
Entrée : une chaine de caractère contenant l'entier à reconnaitre
Necessité : La chaine est convertible en entier
Sortie : L'entier reconnu
Entraine : L'entier a été reconnu et renvoyé
******************************************************************************/
unsigned int CgraphGenerateur::GRGreconnaitreEntier(char * pcElm)
{
	//Version manuelle
	unsigned int uiCompteur = 0;

	//On test d'abord si on a affaire à un nombre
	while(pcElm[uiCompteur] == ' ' || pcElm[uiCompteur] == '\n' && pcElm[uiCompteur] != '\0')
		uiCompteur++;
	while(pcElm[uiCompteur] != '\0' && pcElm[uiCompteur] != ' ' && pcElm[uiCompteur] != '\n' && pcElm[uiCompteur] != ',')
	{
		if(!isdigit(pcElm[uiCompteur]))
			throw Cexception(ERREUR_PARSEUR, "Impossible de reconnaitre un entier positif");
		uiCompteur++;
	}
	while(pcElm[uiCompteur] != '\0')
	{
		pcElm[uiCompteur] = ' ';
		uiCompteur++;
	}

	//puis on le renvoit
	return strtol(pcElm, NULL, 0);


	/*
	long int liTemp;
	//on utilise strtol au cas où l'utilisateur aurait rentré un long ou un double au lieu d'un int
	liTemp = strtol(pcElm, NULL, 0);
	if(liTemp == 0L || liTemp == liTemp * (-1))
		throw Cexception(ERREUR_PARSEUR, "Impossible de reconnaitre l'entier");

	if(liTemp < 0)
		throw Cexception(ERREUR_PARSEUR, "Les parametres doivent etre positifs");

	return (unsigned int)liTemp;*/
}

/******************************************************************************
surcharge de l'opérateur d'affectation
*******************************************************************************
Entrée : un objet du même type
Necessité : Néant
Sortie : Une référence sur l'objet en cours qui a été modifié
Entraine : L'objet en cours est une copie de l'objet en paramètre
******************************************************************************/
CgraphGenerateur & CgraphGenerateur::operator=(CgraphGenerateur const & GRGObjet)
{
	pPARGRGparseur = GRGObjet.pPARGRGparseur;

	return *this;
}