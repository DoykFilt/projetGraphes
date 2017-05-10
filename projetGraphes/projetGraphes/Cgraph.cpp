#include <iostream>
#include "Cgraph.h"
#include "Csommet.h"
#include "Cexception.h"

using namespace std;

Cgraph::Cgraph()
{
	ppSOMGRAListSommets = (Csommet **)malloc(0);
	if(ppSOMGRAListSommets == nullptr)
		throw Cexception(ERREUR_ALLOCATION);
	uiGRAnbrSommets = 0;
}

Cgraph::Cgraph(const Cgraph & GRAObjet)
{
	unsigned int uiCompteur;

	ppSOMGRAListSommets = (Csommet **)malloc(GRAObjet.uiGRAnbrSommets * sizeof(Csommet));
	if(ppSOMGRAListSommets == nullptr)
		throw Cexception(ERREUR_ALLOCATION);
	uiGRAnbrSommets = GRAObjet.uiGRAnbrSommets;
	
	for(uiCompteur = 0; uiCompteur < uiGRAnbrSommets; uiCompteur++)
		ppSOMGRAListSommets[uiCompteur] = GRAObjet.ppSOMGRAListSommets[uiCompteur];
}

Cgraph::Cgraph(Csommet *** pppSOMListSommets, unsigned int uiNbrSommets)
{
	unsigned int uiCompteur;

	ppSOMGRAListSommets = (Csommet **)malloc(uiNbrSommets * sizeof(Csommet));
	if(ppSOMGRAListSommets == nullptr)
		throw Cexception(ERREUR_ALLOCATION);
	uiGRAnbrSommets = uiNbrSommets;
	
	for(uiCompteur = 0; uiCompteur < uiGRAnbrSommets; uiCompteur++)
		ppSOMGRAListSommets[uiCompteur] = (*pppSOMListSommets)[uiCompteur];
}

Cgraph::~Cgraph()
{
	free(ppSOMGRAListSommets);
}


void Cgraph::GRAajouterSommet(Csommet * pSOMSommet)
{
	unsigned int uiCompteur;

	for(uiCompteur = 0; uiCompteur < uiGRAnbrSommets; uiCompteur++)
		if(ppSOMGRAListSommets[uiCompteur]->SOMLireNumSommet() == pSOMSommet->SOMLireNumSommet())
			throw Cexception(ERREUR_PARAM, "Sommet deja present dans le graph");
	
	uiGRAnbrSommets++;
	ppSOMGRAListSommets = (Csommet **)realloc(ppSOMGRAListSommets, uiGRAnbrSommets * sizeof(Csommet *));
	if(ppSOMGRAListSommets == nullptr)
		throw Cexception(ERREUR_REALLOCATION);

	ppSOMGRAListSommets[uiGRAnbrSommets - 1] = pSOMSommet;
}

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

void Cgraph::GRAajouterArc(unsigned int uiNumSommetDebut, unsigned int uiNumSommetFin)
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

	//Ensuite on ajoute l'arc en question
	for(uiCompteur = 0; uiCompteur < uiGRAnbrSommets; uiCompteur++)
	{
		if(ppSOMGRAListSommets[uiCompteur]->SOMLireNumSommet() == uiNumSommetDebut)
			ppSOMGRAListSommets[uiCompteur]->SOMAjouterArc(uiNumSommetFin, false);

		if(ppSOMGRAListSommets[uiCompteur]->SOMLireNumSommet() == uiNumSommetFin)
			ppSOMGRAListSommets[uiCompteur]->SOMAjouterArc(uiNumSommetDebut, true);
	}
}

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

void Cgraph::GRAafficherGraph()
{
	unsigned int uiCompteurSommets, uiCompteurArcs;

	for(uiCompteurSommets = 0; uiCompteurSommets < uiGRAnbrSommets; uiCompteurSommets++)
	{
		cout << "Sommet " << ppSOMGRAListSommets[uiCompteurSommets]->SOMLireNumSommet() << ", ";
		cout << ppSOMGRAListSommets[uiCompteurSommets]->SOMLireNbArcEntrant() << " arcs entrants ";
		cout << ppSOMGRAListSommets[uiCompteurSommets]->SOMLireNbArcSortant() << " arcs sortants";
		cout << endl;

		cout << "Arcs entrants :" << endl;
		for(uiCompteurArcs = 0; uiCompteurArcs < ppSOMGRAListSommets[uiCompteurSommets]->SOMLireNbArcEntrant(); uiCompteurArcs++)
			cout <<  ppSOMGRAListSommets[uiCompteurSommets]->SOMLireArcs(true)[uiCompteurArcs]->ARCLireDestination() << " -> " << endl;
		
		cout << "Arcs sortants :" << endl;
		for(uiCompteurArcs = 0; uiCompteurArcs < ppSOMGRAListSommets[uiCompteurSommets]->SOMLireNbArcSortant(); uiCompteurArcs++)
			cout << " -> " << ppSOMGRAListSommets[uiCompteurSommets]->SOMLireArcs(false)[uiCompteurArcs]->ARCLireDestination() << endl;
	}
}

void Cgraph::GRAvider()
{
	unsigned int uiCompteur;

	for(uiCompteur = 0; uiCompteur < uiGRAnbrSommets; uiCompteur++)
		delete ppSOMGRAListSommets[uiCompteur];
	free(ppSOMGRAListSommets);
}

Cgraph & Cgraph::operator=(Cgraph const & GRAObjet)
{
	unsigned int uiCompteur;

	ppSOMGRAListSommets = (Csommet **)realloc(ppSOMGRAListSommets, GRAObjet.uiGRAnbrSommets * sizeof(Csommet *));
	if(ppSOMGRAListSommets == nullptr)
		throw Cexception(ERREUR_REALLOCATION);

	uiGRAnbrSommets = GRAObjet.uiGRAnbrSommets;
	
	for(uiCompteur = 0; uiCompteur < uiGRAnbrSommets; uiCompteur++)
		ppSOMGRAListSommets[uiCompteur] = GRAObjet.ppSOMGRAListSommets[uiCompteur];

	return *this;
}