#include <iostream>
#include "Cgraph.h"
#include "Csommet.h"
#include "Cexception.h"

using namespace std;

/******************************************************************************
Constructeur
*******************************************************************************
Entrée : Rien
Necessité : Néant
Sortie : Rien
Entraine : L'objet a été initialisé
******************************************************************************/
Cgraph::Cgraph()
{
	ppSOMGRAListSommets = (Csommet **)malloc(0);
	if(ppSOMGRAListSommets == nullptr)
		throw Cexception(ERREUR_ALLOCATION, "Constructeur par defaut Cgraph");
	uiGRAnbrSommets = 0;
}
/******************************************************************************
Constructeur de recopie
*******************************************************************************
Entrée : Référence sur un objet de type Cgraph
Necessité : Néant
Sortie : Rien
Entraine : L'objet a été initialisé par recopie de l'objet en paramètre
******************************************************************************/
Cgraph::Cgraph(const Cgraph & GRAObjet)
{
	unsigned int uiCompteur;

	ppSOMGRAListSommets = (Csommet **)malloc(GRAObjet.uiGRAnbrSommets * sizeof(Csommet *));
	if(ppSOMGRAListSommets == nullptr)
		throw Cexception(ERREUR_ALLOCATION, "Constructeur de recopie Cgraph");
	uiGRAnbrSommets = GRAObjet.uiGRAnbrSommets;
	
	for(uiCompteur = 0; uiCompteur < uiGRAnbrSommets; uiCompteur++)
		ppSOMGRAListSommets[uiCompteur] = new Csommet(*GRAObjet.ppSOMGRAListSommets[uiCompteur]);
}
/******************************************************************************
Constructeur avec deux arguments
*******************************************************************************
Entrée : un pointeur sur une liste de pointeur sur des sommets et le nombre de sommet
Necessité : Le nombre de sommets contenus dans la liste correspond à uiNbrSommets
Sortie : Rien
Entraine : L'objet a été initialisé
******************************************************************************/
Cgraph::Cgraph(Csommet *** pppSOMListSommets, unsigned int uiNbrSommets)
{
	unsigned int uiCompteur;

	ppSOMGRAListSommets = (Csommet **)malloc(uiNbrSommets * sizeof(Csommet *));
	if(ppSOMGRAListSommets == nullptr)
		throw Cexception(ERREUR_ALLOCATION, "Constructeur a deux arguments Cgraph");
	uiGRAnbrSommets = uiNbrSommets;
	
	for(uiCompteur = 0; uiCompteur < uiGRAnbrSommets; uiCompteur++)
		ppSOMGRAListSommets[uiCompteur] = new Csommet(*(*(pppSOMListSommets)[uiCompteur]));
}
/******************************************************************************
Destructeur
*******************************************************************************
Entrée : Rien
Necessité : L'arbre a été désalloué
Sortie : Rien
Entraine : L'espace alloué pour les attributs de l'objet a été libéré
******************************************************************************/
Cgraph::~Cgraph()
{
	free(ppSOMGRAListSommets);
}


/******************************************************************************
GRAajouterSommet
*******************************************************************************
Entrée : pSOMSommet un pointeur sur un sommet
Necessité : Le sommet n'est pas déjà contenu dans le graph
Sortie : Rien
Entraine : le sommet a été ajouté au graph ou exception si déjà présent
******************************************************************************/
void Cgraph::GRAajouterSommet(Csommet * pSOMSommet)
{
	unsigned int uiCompteur;

	for(uiCompteur = 0; uiCompteur < uiGRAnbrSommets; uiCompteur++)
		if(ppSOMGRAListSommets[uiCompteur]->SOMLireNumSommet() == pSOMSommet->SOMLireNumSommet())
			throw Cexception(ERREUR_PARAM, "Sommet deja present dans le graph Cgraph");
	
	uiGRAnbrSommets++;
	ppSOMGRAListSommets = (Csommet **)realloc(ppSOMGRAListSommets, uiGRAnbrSommets * sizeof(Csommet *));
	if(ppSOMGRAListSommets == nullptr)
		throw Cexception(ERREUR_REALLOCATION);

	ppSOMGRAListSommets[uiGRAnbrSommets - 1] = new Csommet(*pSOMSommet);
}

/******************************************************************************
GRAsupprimerSommet
*******************************************************************************
Entrée : le numéro du sommet à supprimer
Necessité : le numéro correspond à un sommet
Sortie : Rien
Entraine : le sommet a été supprimé du graph ou rien si sommet inexistant
******************************************************************************/
void Cgraph::GRAsupprimerSommet(unsigned int uiNumSommet)
{
	unsigned int uiCompteur;

	//En premier lieu on supprime tout les arcs entrant et sortant vers ce sommet
	for(uiCompteur = 0; uiCompteur < uiGRAnbrSommets; uiCompteur++)
	{
		ppSOMGRAListSommets[uiCompteur]->SOMSupprimerArc(uiNumSommet, true);
		ppSOMGRAListSommets[uiCompteur]->SOMSupprimerArc(uiNumSommet, false);
	}

	//Ensuite on retire le sommet
	uiCompteur = 0;
	while(ppSOMGRAListSommets[uiCompteur]->SOMLireNumSommet() != uiNumSommet)
	{
		uiCompteur++;
		if(uiCompteur >= uiGRAnbrSommets)
			throw Cexception(ERREUR_PARAM, "Sommet inexistant");
	}
	delete ppSOMGRAListSommets[uiCompteur];
	for(; uiCompteur < uiGRAnbrSommets - 1; uiCompteur++)
		ppSOMGRAListSommets[uiCompteur] = ppSOMGRAListSommets[uiCompteur + 1];
	
	ppSOMGRAListSommets = (Csommet **)realloc(ppSOMGRAListSommets, (uiGRAnbrSommets - 1) * sizeof(Csommet *));
	if(ppSOMGRAListSommets == nullptr)
		throw Cexception(ERREUR_REALLOCATION);

	uiGRAnbrSommets--;
}

/******************************************************************************
GRAmodifierSommet
*******************************************************************************
Entrée : le numéro du sommet à modifier et le nouveau numéro à lui appliquer
Necessité : le sommet est existant et le nouveau n'est pas déjà pris
Sortie : Rien
Entraine : le sommet a été modifié
******************************************************************************/
void Cgraph::GRAmodifierSommet(unsigned int uiAncienNum, unsigned int uiNouveauNum)
{
	unsigned int uiCompteur;
	
	//On test si le numéro de sommet est disponible
	for(uiCompteur = 0; uiCompteur < uiGRAnbrSommets; uiCompteur++)
		if(ppSOMGRAListSommets[uiCompteur]->SOMLireNumSommet() == uiNouveauNum)
			throw Cexception(ERREUR_PARAM, "Numero de sommet deja present");

	for(uiCompteur = 0; uiCompteur < uiGRAnbrSommets; uiCompteur++)
	{
		//Ensuite on remplace le numéro du sommet concerné
		if(ppSOMGRAListSommets[uiCompteur]->SOMLireNumSommet() == uiAncienNum)
			ppSOMGRAListSommets[uiCompteur]->SOMModifierSommet(uiNouveauNum);
		//Et dans tout les cas on remplace la destination de l'arc si il correspond à l'ancien pour chaque sommet
		ppSOMGRAListSommets[uiCompteur]->SOMModifierArc(uiAncienNum, true, uiNouveauNum); //pour les arcs entrants
		ppSOMGRAListSommets[uiCompteur]->SOMModifierArc(uiAncienNum, false, uiNouveauNum); //et ceux sortant
	}
}
/******************************************************************************
GRAajouterArc
*******************************************************************************
Entrée : les deux numéro des sommets à relier, le destinataire et le destinateur
Necessité : les sommets existent
Sortie : Rien
Entraine : l'arc a été créé
******************************************************************************/
void Cgraph::GRAajouterArc(unsigned int uiNumSommetDebut, unsigned int uiNumSommetFin)
{
	unsigned int uiCompteur;
	bool bSommetDebutTrouvee = false, bSommetFinTrouvee = false;
	
	//On test si les sommets en paramètre existent
	for(uiCompteur = 0; uiCompteur < uiGRAnbrSommets; uiCompteur++)
	{
		if(ppSOMGRAListSommets[uiCompteur]->SOMLireNumSommet() == uiNumSommetDebut)
			bSommetDebutTrouvee = true;
		if(ppSOMGRAListSommets[uiCompteur]->SOMLireNumSommet() == uiNumSommetFin)
			bSommetFinTrouvee = true;
	}
	if(!bSommetDebutTrouvee || !bSommetFinTrouvee)
		throw Cexception(ERREUR_PARAM, "Sommets inexistants");

	//Ensuite on ajoute l'arc en question
	for(uiCompteur = 0; uiCompteur < uiGRAnbrSommets; uiCompteur++)
	{
		if(ppSOMGRAListSommets[uiCompteur]->SOMLireNumSommet() == uiNumSommetDebut)
			ppSOMGRAListSommets[uiCompteur]->SOMAjouterArc(uiNumSommetFin, false);

		if(ppSOMGRAListSommets[uiCompteur]->SOMLireNumSommet() == uiNumSommetFin)
			ppSOMGRAListSommets[uiCompteur]->SOMAjouterArc(uiNumSommetDebut, true);
	}
}
/******************************************************************************
GRASupprimerArc
*******************************************************************************
Entrée : les deux numéro des sommets à relier, le destinataire et le destinateur
Necessité : les sommets et l'arc existent
Sortie : Rien
Entraine : l'arc a été supprimer
******************************************************************************/
void Cgraph::GRAsupprimerArc(unsigned int uiNumSommetDebut, unsigned int uiNumSommetFin)
{
	unsigned int uiCompteur;
	bool bSommetDebutTrouvee = false, bSommetFinTrouvee = false;
	
	if(uiNumSommetDebut == uiNumSommetFin)
		throw Cexception(ERREUR_PARAM, "Valeurs differentes attendues");
	
	//On test si les sommets en paramètre existent
	for(uiCompteur = 0; uiCompteur < uiGRAnbrSommets; uiCompteur++)
	{
		if(ppSOMGRAListSommets[uiCompteur]->SOMLireNumSommet() == uiNumSommetDebut)
			bSommetDebutTrouvee = true;
		if(ppSOMGRAListSommets[uiCompteur]->SOMLireNumSommet() == uiNumSommetFin)
			bSommetFinTrouvee = true;
	}
	if(!bSommetDebutTrouvee || !bSommetFinTrouvee)
		throw Cexception(ERREUR_PARAM, "Sommets inexistants");

	//Puis on supprime l'arc en question
	for(uiCompteur = 0; uiCompteur < uiGRAnbrSommets; uiCompteur++)
	{
		if(ppSOMGRAListSommets[uiCompteur]->SOMLireNumSommet() == uiNumSommetDebut)
			ppSOMGRAListSommets[uiCompteur]->SOMSupprimerArc(uiNumSommetFin, false);

		if(ppSOMGRAListSommets[uiCompteur]->SOMLireNumSommet() == uiNumSommetFin)
			ppSOMGRAListSommets[uiCompteur]->SOMSupprimerArc(uiNumSommetDebut, true);
	}
}
/******************************************************************************
GRAafficherGraph
*******************************************************************************
Entrée : Rien
Necessité : Néant
Sortie : Rien
Entraine : L'arc a été afficher sur la console
******************************************************************************/
void Cgraph::GRAafficherGraph()
{
	unsigned int uiCompteurSommets, uiCompteurArcs;

	cout << "#########################################################################" << endl;
	cout << "#---------- Graphe a " << uiGRAnbrSommets << " sommets ----------" << endl << "#" << endl;

	for(uiCompteurSommets = 0; uiCompteurSommets < uiGRAnbrSommets; uiCompteurSommets++)
	{
		cout << "#---------- SOMMET " << ppSOMGRAListSommets[uiCompteurSommets]->SOMLireNumSommet() << " ---- ";
		cout << ppSOMGRAListSommets[uiCompteurSommets]->SOMLireNbArcEntrant() << " arcs entrants " << " ---- ";
		cout << ppSOMGRAListSommets[uiCompteurSommets]->SOMLireNbArcSortant() << " arcs sortants";
		cout << " ----------" << endl << "#" << endl;

		cout << "#--Arcs entrants :" << endl;
		for(uiCompteurArcs = 0; uiCompteurArcs < ppSOMGRAListSommets[uiCompteurSommets]->SOMLireNbArcEntrant(); uiCompteurArcs++)
			cout << "# " << ppSOMGRAListSommets[uiCompteurSommets]->SOMLireArcs(true)[uiCompteurArcs]->ARCLireDestination() << " -> " << endl;
		
		cout << "#--Arcs sortants :" << endl;
		for(uiCompteurArcs = 0; uiCompteurArcs < ppSOMGRAListSommets[uiCompteurSommets]->SOMLireNbArcSortant(); uiCompteurArcs++)
			cout << "# -> " << ppSOMGRAListSommets[uiCompteurSommets]->SOMLireArcs(false)[uiCompteurArcs]->ARCLireDestination() << endl;
		cout << "#" << endl;
	}
	cout << "#########################################################################" << endl << endl;
}

/******************************************************************************
GRAvider
*******************************************************************************
Entrée : Rien
Necessité : Néant
Sortie : Rien
Entraine : L'espace alloué pour les sommets et les arcs a été libéré
******************************************************************************/
void Cgraph::GRAvider()
{
	unsigned int uiCompteur;

	for(uiCompteur = 0; uiCompteur < uiGRAnbrSommets; uiCompteur++)
		delete ppSOMGRAListSommets[uiCompteur];
	uiGRAnbrSommets = 0;
	ppSOMGRAListSommets = (Csommet **)realloc(ppSOMGRAListSommets, uiGRAnbrSommets);
}

/******************************************************************************
GRAinverser
*******************************************************************************
Entrée : Rien
Necessité : Néant
Sortie : Rien
Entraine : Les arcs entrants ont été remplacés par les arcs sortant et vice-versa
******************************************************************************/
void Cgraph::GRAinverser()
{
	unsigned int uiCompteur;

	for(uiCompteur = 0; uiCompteur < uiGRAnbrSommets; uiCompteur++)
		ppSOMGRAListSommets[uiCompteur]->SOMinverserArcs();
}

/******************************************************************************
surcharge de l'opérateur d'affectation
*******************************************************************************
Entrée : un objet du même type
Necessité : Néant
Sortie : Une référence sur l'objet en cours qui a été modifié
Entraine : L'objet en cours est une copie de l'objet en paramètre
******************************************************************************/
Cgraph & Cgraph::operator=(Cgraph const & GRAObjet)
{
	unsigned int uiCompteur;

	ppSOMGRAListSommets = (Csommet **)realloc(ppSOMGRAListSommets, GRAObjet.uiGRAnbrSommets * sizeof(Csommet *));
	if(ppSOMGRAListSommets == nullptr)
		throw Cexception(ERREUR_REALLOCATION);

	uiGRAnbrSommets = GRAObjet.uiGRAnbrSommets;
	
	for(uiCompteur = 0; uiCompteur < uiGRAnbrSommets; uiCompteur++)
		ppSOMGRAListSommets[uiCompteur] = new Csommet(*GRAObjet.ppSOMGRAListSommets[uiCompteur]);

	return *this;
}