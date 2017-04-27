#include "Cparseur.h"
#include "Cexception.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void main()
{
	try{

		Cparseur * PARparseur = new Cparseur();
		PARparseur->PARLire("graph.txt");
	}
	catch(Cexception EXCexception)
	{
		cout << "Erreur " << EXCexception.EXCLire_Valeur();
		cout << " " << EXCexception.EXCLire_Message() << endl;
	}

	this_thread::sleep_for(chrono::seconds(5));
}