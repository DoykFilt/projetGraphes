#include "Cparseur.h"
#include "Cexception.h"
#include "CgraphGenerateur.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void main(int argc, char * argv[])
{
	Cparseur * PARparseur = nullptr;
	CgraphGenerateur * GRGgenerateur = nullptr;
	Cgraph * GRAgraph = nullptr;
	Cgraph * GRAgraphInverse = nullptr;

	char ** ppcBalises;
	unsigned int uiNbrBalises;

	uiNbrBalises = 4;
	ppcBalises = new char *[uiNbrBalises];
	ppcBalises[0] = _strdup("SOMMETS");
	ppcBalises[1] = _strdup("ARCS");
	ppcBalises[2] = _strdup("NBSOMMETS");
	ppcBalises[3] = _strdup("NBARCS");

	try{
		
		//Si il n'y a aucun fichier en paramètre on s'arrête là
		//if(argc <= 1)
			//throw(Cexception(0, "Pas de parametres"));

		cout << "Lecture du graphe" << endl;
		PARparseur = new Cparseur(ppcBalises, uiNbrBalises);
		PARparseur->PARLire("graph.txt");
		cout << "graphe lu" << endl;

		cout << "Creation du graphe" << endl;
		GRGgenerateur = new CgraphGenerateur(PARparseur);
		GRAgraph = GRGgenerateur->GRGgenererGraph();
		cout << "graph cree" << endl;

		cout << "Affichage du graphe" << endl;
		GRAgraph->GRAafficherGraph();

		cout << "Inversion du graphe" << endl;
		GRAgraphInverse = new Cgraph(*GRAgraph);
		GRAgraphInverse->GRAinverser();
		GRAgraphInverse->GRAafficherGraph();
	}
	catch(Cexception EXCexception)
	{
		cout << "Erreur " << EXCexception.EXCLire_Valeur();
		cout << " " << EXCexception.EXCLire_Message() << endl;
	}

	if(GRAgraph != nullptr)
		GRAgraph->GRAvider();
	delete GRGgenerateur;
	delete GRAgraph;
	delete GRAgraphInverse;
	delete PARparseur;

	this_thread::sleep_for(chrono::seconds(5));
}