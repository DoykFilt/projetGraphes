#include <iostream>
#include "Cgraph.h"
#include "Csommet.h"
#include "Cexception.h"

using namespace std;

/******************************************************************************
Constructeur
*******************************************************************************
Entr�e : Rien
Necessit� : N�ant
Sortie : Rien
Entraine : L'objet a �t� initialis�
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
Entr�e : R�f�rence sur un objet de type Cgraph
Necessit� : N�ant
Sortie : Rien
Entraine : L'objet a �t� initialis� par recopie de l'objet en param�tre
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
Entr�e : un pointeur sur une liste de pointeur sur des sommets et le nombre de sommet
Necessit� : Le nombre de sommets contenus dans la liste correspond � uiNbrSommets
Sortie : Rien
Entraine : L'objet a �t� initialis�
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
Entr�e : Rien
Necessit� : L'arbre a �t� d�sallou�
Sortie : Rien
Entraine : L'espace allou� pour les attributs de l'objet a �t� lib�r�
******************************************************************************/
Cgraph::~Cgraph()
{
	free(ppSOMGRAListSommets);
}


/******************************************************************************
GRAajouterSommet
*******************************************************************************
Entr�e : pSOMSommet un pointeur sur un sommet
Necessit� : Le sommet n'est pas d�j� contenu dans le graph
Sortie : Rien
Entraine : le sommet a �t� ajout� au graph ou exception si d�j� pr�sent
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
Entr�e : le num�ro du sommet � supprimer
Necessit� : le num�ro correspond � un sommet
Sortie : Rien
Entraine : le sommet a �t� supprim� du graph ou rien si sommet inexistant
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
Entr�e : le num�ro du sommet � modifier et le nouveau num�ro � lui appliquer
Necessit� : le sommet est existant et le nouveau n'est pas d�j� pris
Sortie : Rien
Entraine : le sommet a �t� modifi�
******************************************************************************/
void Cgraph::GRAmodifierSommet(unsigned int uiAncienNum, unsigned int uiNouveauNum)
{
	unsigned int uiCompteur;
	
	//On test si le num�ro de sommet est disponible
	for(uiCompteur = 0; uiCompteur < uiGRAnbrSommets; uiCompteur++)
		if(ppSOMGRAListSommets[uiCompteur]->SOMLireNumSommet() == uiNouveauNum)
			throw Cexception(ERREUR_PARAM, "Numero de sommet deja present");

	for(uiCompteur = 0; uiCompteur < uiGRAnbrSommets; uiCompteur++)
	{
		//Ensuite on remplace le num�ro du sommet concern�
		if(ppSOMGRAListSommets[uiCompteur]->SOMLireNumSommet() == uiAncienNum)
			ppSOMGRAListSommets[uiCompteur]->SOMModifierSommet(uiNouveauNum);
		//Et dans tout les cas on remplace la destination de l'arc si il correspond � l'ancien pour chaque sommet
		ppSOMGRAListSommets[uiCompteur]->SOMModifierArc(uiAncienNum, true, uiNouveauNum); //pour les arcs entrants
		ppSOMGRAListSommets[uiCompteur]->SOMModifierArc(uiAncienNum, false, uiNouveauNum); //et ceux sortant
	}
}
/******************************************************************************
GRAajouterArc
*******************************************************************************
Entr�e : les deux num�ro des sommets � relier, le destinataire et le destinateur
Necessit� : les sommets existent
Sortie : Rien
Entraine : l'arc a �t� cr��
******************************************************************************/
void Cgraph::GRAajouterArc(unsigned int uiNumSommetDebut, unsigned int uiNumSommetFin)
{
	unsigned int uiCompteur;
	bool bSommetDebutTrouvee = false, bSommetFinTrouvee = false;
	
	//On test si les sommets en param�tre existent
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
Entr�e : les deux num�ro des sommets � relier, le destinataire et le destinateur
Necessit� : les sommets et l'arc existent
Sortie : Rien
Entraine : l'arc a �t� supprimer
******************************************************************************/
void Cgraph::GRAsupprimerArc(unsigned int uiNumSommetDebut, unsigned int uiNumSommetFin)
{
	unsigned int uiCompteur;
	bool bSommetDebutTrouvee = false, bSommetFinTrouvee = false;
	
	if(uiNumSommetDebut == uiNumSommetFin)
		throw Cexception(ERREUR_PARAM, "Valeurs differentes attendues");
	
	//On test si les sommets en param�tre existent
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
Entr�e : Rien
Necessit� : N�ant
Sortie : Rien
Entraine : L'arc a �t� afficher sur la console
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
Entr�e : Rien
Necessit� : N�ant
Sortie : Rien
Entraine : L'espace allou� pour les sommets et les arcs a �t� lib�r�
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
Entr�e : Rien
Necessit� : N�ant
Sortie : Rien
Entraine : Les arcs entrants ont �t� remplac�s par les arcs sortant et vice-versa
******************************************************************************/
void Cgraph::GRAinverser()
{
	unsigned int uiCompteur;

	for(uiCompteur = 0; uiCompteur < uiGRAnbrSommets; uiCompteur++)
		ppSOMGRAListSommets[uiCompteur]->SOMinverserArcs();
}

/******************************************************************************
surcharge de l'op�rateur d'affectation
*******************************************************************************
Entr�e : un objet du m�me type
Necessit� : N�ant
Sortie : Une r�f�rence sur l'objet en cours qui a �t� modifi�
Entraine : L'objet en cours est une copie de l'objet en param�tre
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