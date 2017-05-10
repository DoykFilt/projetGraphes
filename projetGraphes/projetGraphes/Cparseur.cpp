#include <fstream>
#include <iostream>
#include "Cparseur.h"
#include <string.h>
#include "Cexception.h"

using namespace std;

/******************************************************************************
Constructeur
*******************************************************************************
Entrée : char ** tableau contenant les noms de balise, unsigned int le nombre de balise
Necessité : uiNbrBalises correspond au nombre de balises dans pcBalises
Sortie : Rien
Entraine : L'objet a été initialisé
******************************************************************************/
Cparseur::Cparseur(char ** pcBalises, unsigned int uiNbrBalises)
{	
	unsigned int uiCompteur;

	ppcPARBalises = new char*[uiNbrBalises];
	pppcPARtabBalisesValeurs = new char**[uiNbrBalises];
	uiPARNbrBalises = uiNbrBalises;

	for(uiCompteur = 0; uiCompteur < uiNbrBalises; uiCompteur++)
	{
		ppcPARBalises[uiCompteur] = _strdup(pcBalises[uiCompteur]);
		pppcPARtabBalisesValeurs[uiCompteur] = new char*[2];
		pppcPARtabBalisesValeurs[uiCompteur][0] = _strdup(pcBalises[uiCompteur]);
		pppcPARtabBalisesValeurs[uiCompteur][1] = nullptr;
	}
}

/******************************************************************************
Constructeur de recopie
*******************************************************************************
Entrée : Référence sur un objet de type Cparseur
Necessité : Néant
Sortie : Rien
Entraine : L'objet a été initialisé par recopie de l'objet en paramètre
******************************************************************************/
Cparseur::Cparseur(Cparseur & PARObjet)
{	
	unsigned int uiCompteur;
	
	ppcPARBalises = new char*[PARObjet.uiPARNbrBalises];
	pppcPARtabBalisesValeurs = new char**[PARObjet.uiPARNbrBalises];
	uiPARNbrBalises = PARObjet.uiPARNbrBalises;

	for(uiCompteur = 0; uiCompteur < PARObjet.uiPARNbrBalises; uiCompteur++)
	{
		ppcPARBalises[uiCompteur] = _strdup(PARObjet.ppcPARBalises[uiCompteur]);
		pppcPARtabBalisesValeurs[uiCompteur] = new char*[2];
		pppcPARtabBalisesValeurs[uiCompteur][0] = _strdup(PARObjet.pppcPARtabBalisesValeurs[uiCompteur][0]);
		pppcPARtabBalisesValeurs[uiCompteur][1] = _strdup(PARObjet.pppcPARtabBalisesValeurs[uiCompteur][1]);
	}
}

/******************************************************************************
Destructeur
*******************************************************************************
Entrée : Rien
Necessité : Néant
Sortie : Rien
Entraine : L'espace alloué pour les attributs de l'objet a été libéré
******************************************************************************/
Cparseur::~Cparseur()
{
	unsigned int uiCompteur;

	for( uiCompteur = 0; uiCompteur < uiPARNbrBalises; uiCompteur++)
	{
		free(ppcPARBalises[uiCompteur]);
		free(pppcPARtabBalisesValeurs[uiCompteur][0]);
		free(pppcPARtabBalisesValeurs[uiCompteur][1]);
		delete pppcPARtabBalisesValeurs[uiCompteur];
	}
	delete ppcPARBalises;
	delete pppcPARtabBalisesValeurs;
}

/******************************************************************************
surcharge de l'opérateur d'affectation
*******************************************************************************
	Entrée : un objet du même type
	Necessité : Néant
	Sortie : Une référence sur l'objet en cours qui a été modifié
	Entraine : L'objet en cours est une copie de l'objet en paramètre
******************************************************************************/
Cparseur & Cparseur::operator=(Cparseur const & PARparseur)
{
	unsigned int uiCompteur;
	
	ppcPARBalises = new char*[PARparseur.uiPARNbrBalises];
	pppcPARtabBalisesValeurs = new char**[PARparseur.uiPARNbrBalises];
	uiPARNbrBalises = PARparseur.uiPARNbrBalises;

	for(uiCompteur = 0; uiCompteur < PARparseur.uiPARNbrBalises; uiCompteur++)
	{
		ppcPARBalises[uiCompteur] = _strdup(PARparseur.ppcPARBalises[uiCompteur]);
		pppcPARtabBalisesValeurs[uiCompteur] = new char*[2];
		pppcPARtabBalisesValeurs[uiCompteur][0] = _strdup(PARparseur.pppcPARtabBalisesValeurs[uiCompteur][0]);
		pppcPARtabBalisesValeurs[uiCompteur][1] = _strdup(PARparseur.pppcPARtabBalisesValeurs[uiCompteur][1]);
	}
	return *this;
}

/******************************************************************************
PARLire (inspiré par les méthodes de compilation)
*******************************************************************************
Entrée : pcfilename le chemin d'accès au fichier (chaîne de caractère)
Necessité : Le fichier existe et les données dont au bon format dans le fichier
Sortie : Rien
Entraine : les données sont lues et stockées sous format brut
******************************************************************************/
void Cparseur::PARLire(char* pcfilename)
{
	char cLecture;
	char * pcTemp = (char *)malloc(sizeof(char));
	if(pcTemp == nullptr)
		throw Cexception(ERREUR_ALLOCATION, "Dans PARLire");
	pcTemp[0] = '\0';
	char * pcBaliseActuelle;
	bool bLectureBalise = true, bLectureValeur = false, bLectureMultiple = false;
	unsigned int uiCompteur, uiCptrTemp = 0;

	//Ouverture du fichier
	ifstream fichier(pcfilename, ios::in);
	if(fichier.fail())
		throw Cexception(ERREUR_FICHIER);

	while(fichier.get(cLecture))
	{
		//On met le caractère en majuscule
		if(!bLectureMultiple && cLecture >= 'a' && cLecture <= 'z')
			cLecture = cLecture - 'a' + 'A';

		//Ensuite on teste chaque valeur possible
		switch(cLecture)
		{
		case '=' :
			bLectureBalise = false;
			if(!bLectureValeur && !bLectureMultiple)
			{
				pcBaliseActuelle = PARreconnaitreBalise(pcTemp);
				bLectureValeur = true;
				uiCptrTemp = 0;
				pcTemp = (char *)realloc(pcTemp, sizeof(char));
				if(pcTemp == nullptr)
					throw Cexception(ERREUR_REALLOCATION);
				pcTemp[uiCptrTemp] = '\0';
			}
			else
			if(bLectureMultiple)
			{	
				uiCptrTemp++;
				pcTemp = (char *)realloc(pcTemp, (uiCptrTemp + 1) * sizeof(char));
				if(pcTemp == nullptr)
					throw Cexception(ERREUR_REALLOCATION);
				pcTemp[uiCptrTemp - 1] = cLecture;
				pcTemp[uiCptrTemp] = '\0';
			}
			else if(!bLectureMultiple)
				throw Cexception(ERREUR_PARSEUR, "= non attendu");
			break;
		case ' ' :
		case '\n' :
			if(bLectureValeur && !bLectureMultiple)
			{
				PARstockerValeur(pcBaliseActuelle, pcTemp);
				uiCptrTemp = 0;
				pcTemp = (char *)realloc(pcTemp, sizeof(char));
				if(pcTemp == nullptr)
					throw Cexception(ERREUR_REALLOCATION);
				pcTemp[uiCptrTemp] = '\0';
				bLectureValeur = false;
				bLectureBalise = true;
			}
			if(bLectureMultiple)
			{	
				if(*pcTemp != '\0')
				{
					uiCptrTemp++;
					pcTemp = (char *)realloc(pcTemp, (uiCptrTemp + 1) * sizeof(char));
					if(pcTemp == nullptr)
						throw Cexception(ERREUR_REALLOCATION);
					pcTemp[uiCptrTemp - 1] = ' ';
					pcTemp[uiCptrTemp] = '\0';
				}
			}
			break;
		case '[' :
			if(bLectureValeur && !bLectureMultiple)
				bLectureMultiple = true;
			else
				throw Cexception(ERREUR_PARSEUR, "[ non attendu");
			break;
		case ']' :
			if(bLectureValeur && bLectureMultiple)
			{
				bLectureValeur = false;
				bLectureMultiple = false;
				bLectureBalise = true;
				PARstockerValeur(pcBaliseActuelle, pcTemp);
				uiCptrTemp = 0;
				pcTemp = (char *)realloc(pcTemp, sizeof(char));
				if(pcTemp == nullptr)
					throw Cexception(ERREUR_REALLOCATION);
				pcTemp[uiCptrTemp] = '\0';
			}
			else
				throw Cexception(ERREUR_PARSEUR, "] non attendu");
			break;
		default :
			if(!bLectureBalise)
				bLectureValeur = true;
			uiCptrTemp++;
			pcTemp = (char *)realloc(pcTemp, (uiCptrTemp + 1) * sizeof(char));
			if(pcTemp == nullptr)
				throw Cexception(ERREUR_REALLOCATION);
			pcTemp[uiCptrTemp - 1] = cLecture;
			pcTemp[uiCptrTemp] = '\0';
			break;
		}
	}
	
	//Finalement test si tout a bien été récupéré
	for(uiCompteur = 0; uiCompteur < uiPARNbrBalises; uiCompteur++)
	{
		if(pppcPARtabBalisesValeurs[uiCompteur][1] == nullptr)
			throw Cexception(ERREUR_PARSEUR, "Fin du fichier, toutes les informations n'ont pas ete renseignees");
	}

	//Pour enfin fermer le fichier et libérer les variables intermédiaires
	fichier.close();
	free(pcTemp);
}

/******************************************************************************
PARreconnaitreBalise
*******************************************************************************
Entrée : pcSource(chaîne de caractère)
Necessité : Rien
Sortie : chaîne de caractères la balise reconnue
Entraine : La balise est reconnue ou levée d'une exception
******************************************************************************/
char * Cparseur::PARreconnaitreBalise(char * pcSource)
{
	unsigned int uiCptr;

	if(pcSource == nullptr)
		throw Cexception(ERREUR_PARAM);

	for(uiCptr = 0; uiCptr < uiPARNbrBalises; uiCptr++)
		if(strcmp(pppcPARtabBalisesValeurs[uiCptr][0],pcSource) == 0)
			return pppcPARtabBalisesValeurs[uiCptr][0];

	throw Cexception(ERREUR_PARSEUR, "Balise inconnue");
}

/******************************************************************************
PARstockerValeur
*******************************************************************************
Entrée : (2 chaînes de caractères)pcBalise et pcValeur, la valeur à stocker dans la balise
Necessité : Le fichier existe
Sortie : Un objet CMatrice de type MType
Entraine : la matrice est lue puis retourné
******************************************************************************/
void Cparseur::PARstockerValeur(char * pcBalise, char * pcValeur)
{
	unsigned int uiCptr;

	if(pcBalise == nullptr || pcValeur == nullptr)
		throw Cexception(ERREUR_PARAM);

	if(pcValeur == '\0')
	{
		pcValeur = (char *)realloc(pcValeur, sizeof(char) * 2);
		pcValeur[0] = ' ';
		pcValeur[1] = '\0';
	}

	for(uiCptr = 0; uiCptr < uiPARNbrBalises; uiCptr++)
		if(strcmp(pppcPARtabBalisesValeurs[uiCptr][0], pcBalise) == 0)
			pppcPARtabBalisesValeurs[uiCptr][1] = _strdup(pcValeur);
}

/******************************************************************************
PARvaleurSuivante
*******************************************************************************
Entrée : (2 chaînes de caractères)pcBalise et pcChaine
Necessité : il y a une valeur associée à la balise dans la chaîne de caractère
Sortie : une chaine de caractère, la valeur associée
Entraine : la valeur est trouvée, renvoiée et éffacé de la chaîne de caractère
******************************************************************************/
char * Cparseur::PARvaleurSuivante(char * pcBalise, char * pcChaine)
{
	char * pcTemp;
	char * pcRetour;
	unsigned int uiCompteur;

	if(pcBalise == nullptr || pcBalise == nullptr)
		throw Cexception(ERREUR_PARAM);

	//On met tout en majuscule
	for(uiCompteur = 0; uiCompteur < strlen(pcChaine); uiCompteur++)
		if(pcChaine[uiCompteur] >= 'a' && pcChaine[uiCompteur] <= 'z')
			pcChaine[uiCompteur] = pcChaine[uiCompteur] - 'a' + 'A';

	pcTemp = strstr(pcChaine, pcBalise);
	if(pcTemp == nullptr)
		throw Cexception(ERREUR_PARSEUR, "Balise non trouvee");

	//On va jusqu'au égal en supprimant la balise
	while(*pcTemp != '=')
	{
		if(*pcTemp == '\0')
			throw Cexception(ERREUR_PARSEUR, "Valeur non trouvee");
		*pcTemp = ' ';
		pcTemp++;
	}
	//Ensuite on supprime le égal et tout les espace
	while(*pcTemp == '=' || *pcTemp == ' ' || *pcTemp == '\n')	
	{
		if(*pcTemp == '\0')
			throw Cexception(ERREUR_PARSEUR, "Valeur non trouvee");
		*pcTemp = ' ';
		pcTemp++;
	}
	//Puis on retire la valeur de la chaine pour la renvoyer
	uiCompteur = 0;
	pcRetour = (char *)malloc(uiCompteur + 1);
	if(pcRetour == nullptr)
		throw Cexception(ERREUR_ALLOCATION, "Dans PARValeurSuivante");
	pcRetour[uiCompteur] = '\0';
	
	while(*pcTemp != ' ' && *pcTemp != '\n')
	{
		if(*pcTemp == '\0')
			throw Cexception(ERREUR_PARSEUR, "Valeur non trouvee");
		uiCompteur++;
		pcRetour = (char *)realloc(pcRetour, uiCompteur + 1);
		if(pcRetour == nullptr)
			throw Cexception(ERREUR_REALLOCATION);
		pcRetour[uiCompteur - 1] = *pcTemp;
		pcRetour[uiCompteur] = '\0';
		*pcTemp = ' ';
		pcTemp++;
	}
	return pcRetour;
}