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
		cout << "Lecture du graph" << endl;
		PARparseur = new Cparseur(ppcBalises, uiNbrBalises);
		PARparseur->PARLire("graph.txt");
		cout << "graph lu" << endl;

		cout << "Creation du graph" << endl;
		GRGgenerateur = new CgraphGenerateur(PARparseur);
		GRAgraph = GRGgenerateur->GRGgenererGraph();
		cout << "graph cree" << endl;

		cout << "Affichage du graph" << endl;
		GRAgraph->GRAafficherGraph();
	}
	catch(Cexception EXCexception)
	{
		cout << "Erreur " << EXCexception.EXCLire_Valeur();
		cout << " " << EXCexception.EXCLire_Message() << endl;
	}


	this_thread::sleep_for(chrono::seconds(5));
}