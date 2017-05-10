#include "Cparseur.h"
#include "Cexception.h"
#include "CgraphGenerateur.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void main()
{
	Cparseur * PARparseur;
	CgraphGenerateur * GRGgenerateur;
	Cgraph * GRAgraph;

	char ** ppcBalises;
	unsigned int uiNbrBalises;

	uiNbrBalises = 4;
	ppcBalises = new char *[uiNbrBalises];
	ppcBalises[0] = _strdup("SOMMETS");
	ppcBalises[1] = _strdup("ARCS");
	ppcBalises[2] = _strdup("NBSOMMETS");
	ppcBalises[3] = _strdup("NBARCS");

	try{
		cout << "Lecture du grph" << endl;
		PARparseur = new Cparseur(ppcBalises, uiNbrBalises);
		PARparseur->PARLire("graph.txt");
	}
	catch(Cexception EXCexception)
	{
		cout << "Erreur " << EXCexception.EXCLire_Valeur();
		cout << " " << EXCexception.EXCLire_Message() << endl;
	}

	try{
		cout << "Création du graph" << endl;
		GRGgenerateur = new CgraphGenerateur(PARparseur);
		GRAgraph = GRGgenerateur->GRGgenererGraph();
	}
	catch(Cexception EXCexception)
	{
		cout << "Erreur " << EXCexception.EXCLire_Valeur();
		cout << " " << EXCexception.EXCLire_Message() << endl;
	}

	cout << "Affichage du graph" << endl;
	GRAgraph->GRAafficherGraph();

	this_thread::sleep_for(chrono::seconds(5));
}