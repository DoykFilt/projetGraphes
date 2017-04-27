#ifndef CPARSEUR_H
#define CPARSEUR_H

#define PARNBRBALISES 4 // nbr de balises
//Nom des balises
#define PARNBSOMMETS "NBSOMMETS"
#define PARNBARCS "NBARCS"
#define PARSOMMETS "SOMMETS"
#define PARARCS "ARCS"
//Les différentes sous-balises
#define PARNUMERO "NUMERO"
#define PARDEBUT "DEBUT"
#define PARFIN "FIN"

/******************************************************************************
class Cparseur
*******************************************************************************

	Cette classe permet de trnasformer les données d'un fichier en données
	brut à l'aide de balises et d'en sortir un graph

	Attributs
		pcPARtabBalisesValeurs : Les données brutes relevées du fichier, chaque
			ligne correspond à une balise : la première colonne le nom de la 
			balise et la seconde sa valeur détecté

******************************************************************************/
class Cparseur
{
private :
	unsigned int uiPARNbrBalises;
	char ** pcPARBalises;
	char *** pcPARtabBalisesValeurs;

public :
	//Constructeurs et destructeurs
	Cparseur(char ** pcBalises, unsigned int uiNbrBalises);
	Cparseur(Cparseur & PARObjet);
	~Cparseur();

	//Permet de récolter les données d'un fichier et de les stocker sous un format brut
	void PARLire(char * pcfilename);

	//Surcharges d'opérateurs
	Cparseur & operator=(Cparseur const & PARparseur);

private :
	//Méthodes utilisé en interne pour le parsage
	char * PARreconnaitreBalise(char * pcSource);
	void PARstockerValeur(char * pcBalise, char * pcValeur);
	char * PARvaleurSuivante(char * pcBalise, char * pcChaine);
};

#endif