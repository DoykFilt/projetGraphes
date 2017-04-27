#ifndef CPARSEUR_H
#define CPARSEUR_H

#define PARNBRBALISES 4 // nbr de balises
//Nom des balises
#define PARNBSOMMETS "NBSOMMETS"
#define PARNBARCS "NBARCS"
#define PARSOMMETS "SOMMETS"
#define PARARCS "ARCS"
//Les diff�rentes sous-balises
#define PARNUMERO "NUMERO"
#define PARDEBUT "DEBUT"
#define PARFIN "FIN"

/******************************************************************************
class Cparseur
*******************************************************************************

	Cette classe permet de trnasformer les donn�es d'un fichier en donn�es
	brut � l'aide de balises et d'en sortir un graph

	Attributs
		pcPARtabBalisesValeurs : Les donn�es brutes relev�es du fichier, chaque
			ligne correspond � une balise : la premi�re colonne le nom de la 
			balise et la seconde sa valeur d�tect�

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

	//Permet de r�colter les donn�es d'un fichier et de les stocker sous un format brut
	void PARLire(char * pcfilename);

	//Surcharges d'op�rateurs
	Cparseur & operator=(Cparseur const & PARparseur);

private :
	//M�thodes utilis� en interne pour le parsage
	char * PARreconnaitreBalise(char * pcSource);
	void PARstockerValeur(char * pcBalise, char * pcValeur);
	char * PARvaleurSuivante(char * pcBalise, char * pcChaine);
};

#endif