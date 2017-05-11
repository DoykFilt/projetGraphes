#include <iostream>
#include "CgraphGenerateur.h"
#include "Cexception.h"


/******************************************************************************
Constructeur
*******************************************************************************
Entr�e : Rien
Necessit� : N�ant
Sortie : Rien
Entraine : L'objet a �t� initialis�
******************************************************************************/
CgraphGenerateur::CgraphGenerateur()
{
	pPARGRGparseur = nullptr;
}
/******************************************************************************
Constructeur avec un argument
*******************************************************************************
Entr�e : un pointeur sur un objet de type Cparseur
Necessit� : N�ant
Sortie : Rien
Entraine : L'objet a �t� initialis�
******************************************************************************/
CgraphGenerateur::CgraphGenerateur(Cparseur * pPARparseur)
{
	pPARGRGparseur = pPARparseur;
}
/******************************************************************************
Constructeur de recopie
*******************************************************************************
Entr�e : R�f�rence sur un objet de type CgraphGenerateur
Necessit� : N�ant
Sortie : Rien
Entraine : L'objet a �t� initialis� par recopie de l'objet en param�tre
******************************************************************************/
CgraphGenerateur::CgraphGenerateur(const CgraphGenerateur & GRGObjet)
{
	pPARGRGparseur = GRGObjet.pPARGRGparseur;
}
/******************************************************************************
Destructeur
*******************************************************************************
Entr�e : Rien
Necessit� : L'arbre a �t� d�sallou�
Sortie : Rien
Entraine : L'espace allou� pour les attributs de l'objet a �t� lib�r�
******************************************************************************/
CgraphGenerateur::~CgraphGenerateur(){}

/******************************************************************************
GRGgenererGraph
*******************************************************************************
Entr�e : Rien
Necessit� : Le parseur a r�cup�r� les donn�es brutes pr�alablement
Sortie : l'objet reconnu de type Cgraph 
Entraine : un objet de type Cgraph a �t� allou� et retourn�
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
Entr�e : Un pointeur sur un objet de type Cparseur
Necessit� : N�ant
Sortie : Rien
Entraine : L'ancien parseur a �t� remplac� par le nouveau
******************************************************************************/
void CgraphGenerateur::GRGsetParseur(Cparseur * pPARparseur)
{
	pPARGRGparseur = pPARparseur;
}

/******************************************************************************
GRGgetParseur
*******************************************************************************
Entr�e : Rien
Necessit� : N�ant
Sortie : Un poiteur sur le parseur
Entraine : Le pointeur a �t� retourn�
******************************************************************************/
Cparseur * CgraphGenerateur::GRGgetParseur()
{
	return pPARGRGparseur;
}

/******************************************************************************
GRGreconnaitreEntier
*******************************************************************************
Entr�e : une chaine de caract�re contenant l'entier � reconnaitre
Necessit� : La chaine est convertible en entier
Sortie : L'entier reconnu
Entraine : L'entier a �t� reconnu et renvoy�
******************************************************************************/
unsigned int CgraphGenerateur::GRGreconnaitreEntier(char * pcElm)
{
	//Version manuelle
	unsigned int uiCompteur = 0;

	//On test d'abord si on a affaire � un nombre
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
	//on utilise strtol au cas o� l'utilisateur aurait rentr� un long ou un double au lieu d'un int
	liTemp = strtol(pcElm, NULL, 0);
	if(liTemp == 0L || liTemp == liTemp * (-1))
		throw Cexception(ERREUR_PARSEUR, "Impossible de reconnaitre l'entier");

	if(liTemp < 0)
		throw Cexception(ERREUR_PARSEUR, "Les parametres doivent etre positifs");

	return (unsigned int)liTemp;*/
}

/******************************************************************************
surcharge de l'op�rateur d'affectation
*******************************************************************************
Entr�e : un objet du m�me type
Necessit� : N�ant
Sortie : Une r�f�rence sur l'objet en cours qui a �t� modifi�
Entraine : L'objet en cours est une copie de l'objet en param�tre
******************************************************************************/
CgraphGenerateur & CgraphGenerateur::operator=(CgraphGenerateur const & GRGObjet)
{
	pPARGRGparseur = GRGObjet.pPARGRGparseur;

	return *this;
}