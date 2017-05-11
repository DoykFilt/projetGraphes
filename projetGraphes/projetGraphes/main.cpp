#include "Cparseur.h"
#include "Cexception.h"
#include "CgraphGenerateur.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void main(int argc, char * argv[])
{
	//Déclarations
	Cparseur * pPARparseur = nullptr;
	CgraphGenerateur * pGRGgenerateur = nullptr;
	Cgraph * pGRAgraph = nullptr;
	Cgraph * pGRAgraphInverse = nullptr;

	char ** ppcBalises;
	unsigned int uiNbrBalises;

	//les balises principales à trouver dans le fichier
	uiNbrBalises = 4;
	ppcBalises = new char *[uiNbrBalises];
	ppcBalises[0] = _strdup("SOMMETS");
	ppcBalises[1] = _strdup("ARCS");
	ppcBalises[2] = _strdup("NBSOMMETS");
	ppcBalises[3] = _strdup("NBARCS");

	//Bloc principal
	try{
		
		//Si il n'y a aucun fichier en paramètre on s'arrête là
		if(argc <= 1)
			throw(Cexception(0, "Pas de parametres"));

		cout << "1 -------------------- Lecture du graphe.." << endl << endl;
		pPARparseur = new Cparseur(ppcBalises, uiNbrBalises);
		pPARparseur->PARLire(argv[1]);

		cout << "2 -------------------- Generation du graphe.." << endl << endl;
		pGRGgenerateur = new CgraphGenerateur(pPARparseur);
		pGRAgraph = pGRGgenerateur->GRGgenererGraph();

		cout << "3 -------------------- Affichage du graphe.." << endl << endl;
		pGRAgraph->GRAafficherGraph();

		cout << "4 -------------------- Inversion du graphe.." << endl << endl;
		pGRAgraphInverse = new Cgraph(*pGRAgraph);
		pGRAgraphInverse->GRAinverser();
		pGRAgraphInverse->GRAafficherGraph();
	}
	catch(Cexception EXCexception)
	{
		cout << "Erreur " << EXCexception.EXCLire_Valeur();
		cout << " " << EXCexception.EXCLire_Message() << endl;
	}

	if(pGRAgraph != nullptr)
		pGRAgraph->GRAvider();
	delete pGRGgenerateur;
	delete pGRAgraph;
	delete pGRAgraphInverse;
	delete pPARparseur;

	//this_thread::sleep_for(chrono::seconds(20));
}