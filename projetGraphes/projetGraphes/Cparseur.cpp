#include <fstream>
#include <iostream>
#include "Cparseur.h"
#include <string.h>
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
Cparseur::Cparseur(char ** pcBalises, unsigned int uiNbrBalises)
{	
	unsigned int uiCompteur;

	pcPARBalises = new char*[uiNbrBalises];
	pcPARtabBalisesValeurs = new char**[uiNbrBalises];
	uiPARNbrBalises = uiNbrBalises;

	for(uiCompteur = 0; uiCompteur < uiNbrBalises; uiCompteur++)
	{
		pcPARBalises[uiCompteur] = _strdup(pcBalises[uiCompteur]);
		pcPARtabBalisesValeurs[uiCompteur] = new char*[2];
		pcPARtabBalisesValeurs[uiCompteur][0] = _strdup(pcBalises[uiCompteur]);
		pcPARtabBalisesValeurs[uiCompteur][1] = nullptr;
	}
}

/******************************************************************************
Constructeur de recopie
*******************************************************************************
Entr�e : R�f�rence sur un objet de type Cparseur
Necessit� : N�ant
Sortie : Rien
Entraine : L'objet a �t� initialis� par recopie de l'objet en param�tre
******************************************************************************/
Cparseur::Cparseur(Cparseur & PARObjet)
{	
	unsigned int uiCompteur;
	
	pcPARBalises = new char*[PARObjet.uiPARNbrBalises];
	pcPARtabBalisesValeurs = new char**[PARObjet.uiPARNbrBalises];
	uiPARNbrBalises = PARObjet.uiPARNbrBalises;

	for(uiCompteur = 0; uiCompteur < PARObjet.uiPARNbrBalises; uiCompteur++)
	{
		pcPARBalises[uiCompteur] = _strdup(PARObjet.pcPARBalises[uiCompteur]);
		pcPARtabBalisesValeurs[uiCompteur] = new char*[2];
		pcPARtabBalisesValeurs[uiCompteur][0] = _strdup(PARObjet.pcPARtabBalisesValeurs[uiCompteur][0]);
		pcPARtabBalisesValeurs[uiCompteur][1] = _strdup(PARObjet.pcPARtabBalisesValeurs[uiCompteur][1]);
	}
}

/******************************************************************************
Destructeur
*******************************************************************************
Entr�e : Rien
Necessit� : N�ant
Sortie : Rien
Entraine : L'espace allou� pour les attributs de l'objet a �t� lib�r�
******************************************************************************/
Cparseur::~Cparseur()
{
	unsigned int uiCompteur;

	for( uiCompteur = 0; uiCompteur < uiPARNbrBalises; uiCompteur++)
	{
		free(pcPARBalises[uiCompteur]);
		free(pcPARtabBalisesValeurs[uiCompteur][0]);
		free(pcPARtabBalisesValeurs[uiCompteur][1]);
		free(pcPARtabBalisesValeurs[uiCompteur]);
	}
	free(pcPARBalises);
	free(pcPARtabBalisesValeurs);
}

/******************************************************************************
surcharge de l'op�rateur d'affectation
*******************************************************************************
	Entr�e : un objet du m�me type
	Necessit� : N�ant
	Sortie : Une r�f�rence sur l'objet en cours qui a �t� modifi�
	Entraine : L'objet en cours est une copie de l'objet en param�tre
******************************************************************************/
Cparseur & Cparseur::operator=(Cparseur const & PARparseur)
{
	free(pcPARtabBalisesValeurs[0][1]);
	free(pcPARtabBalisesValeurs[1][1]);
	free(pcPARtabBalisesValeurs[2][1]);
	free(pcPARtabBalisesValeurs[3][1]);

	pcPARtabBalisesValeurs[0][1] = _strdup(PARparseur.pcPARtabBalisesValeurs[0][1]);
	pcPARtabBalisesValeurs[1][1] = _strdup(PARparseur.pcPARtabBalisesValeurs[1][1]);
	pcPARtabBalisesValeurs[2][1] = _strdup(PARparseur.pcPARtabBalisesValeurs[2][1]);
	pcPARtabBalisesValeurs[3][1] = _strdup(PARparseur.pcPARtabBalisesValeurs[3][1]);

	return *this;
}

/******************************************************************************
PARLire (inspir� par les m�thodes de compilation)
*******************************************************************************
Entr�e : pcfilename le chemin d'acc�s au fichier (cha�ne de caract�re)
Necessit� : Le fichier existe
Sortie : Rien
Entraine : la matrice est lue sous format brut
******************************************************************************/
void Cparseur::PARLire(char* pcfilename)
{
	char cLecture;
	char * pcTemp = (char *)malloc(sizeof(char));
	pcTemp[0] = '\0';
	char * pcBaliseActuelle = _strdup("");
	bool bLectureBalise = true, bLectureValeur = false, bLectureMultiple = false;
	unsigned int uiCompteur, uiCptrTemp = 0;

	//Ouverture du fichier
	ifstream fichier(pcfilename, ios::in);
	if(fichier.fail())
		throw Cexception(5);

	while(fichier.get(cLecture))
	{
		//On met le caract�re en majuscule
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
				pcTemp[uiCptrTemp] = '\0';
			}
			else
			if(bLectureMultiple)
			{	
				uiCptrTemp++;
				pcTemp = (char *)realloc(pcTemp, uiCptrTemp * sizeof(char));
				pcTemp[uiCptrTemp - 1] = cLecture;
				pcTemp[uiCptrTemp] = '\0';
			}
			else if(!bLectureMultiple)
				throw Cexception(6, "= non attendu");
			break;
		case ' ' :
		case '\n' :
			if(bLectureValeur && !bLectureMultiple)
			{
				PARstockerValeur(pcBaliseActuelle, pcTemp);
				uiCptrTemp = 0;
				pcTemp = (char *)realloc(pcTemp, sizeof(char));
				pcTemp[uiCptrTemp] = '\0';
				bLectureValeur = false;
				bLectureBalise = true;
			}
			if(bLectureMultiple)
			{	
				if(*pcTemp != '\0')
				{
					uiCptrTemp++;
					pcTemp = (char *)realloc(pcTemp, uiCptrTemp * sizeof(char));
					pcTemp[uiCptrTemp - 1] = ' ';
					pcTemp[uiCptrTemp] = '\0';
				}
			}
			break;
		case '[' :
			if(bLectureValeur && !bLectureMultiple)
				bLectureMultiple = true;
			else
				throw Cexception(6, "[ non attendu");
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
				pcTemp[uiCptrTemp] = '\0';
			}
			else
				throw Cexception(6, "] non attendu");
			break;
		default :
			if(!bLectureBalise)
				bLectureValeur = true;
			uiCptrTemp++;
			pcTemp = (char *)realloc(pcTemp, uiCptrTemp * sizeof(char));
			pcTemp[uiCptrTemp - 1] = cLecture;
			pcTemp[uiCptrTemp] = '\0';
			break;
		}
	}
	
	//Finalement test si tout a bien �t� r�cup�r�
	for(uiCompteur = 0; uiCompteur < PARNBRBALISES; uiCompteur++)
	{
		if(pcPARtabBalisesValeurs[uiCompteur][1] == nullptr)
			throw Cexception(6, "Fin du fichier, toutes les informations n'ont pas ete renseignees");
	}

	//Pour enfin fermer le fichier et lib�rer les variables interm�diaires
	fichier.close();
	free(pcTemp);
	free(pcBaliseActuelle);
}

/******************************************************************************
PARreconnaitreBalise
*******************************************************************************
Entr�e : pcSource(cha�ne de caract�re)
Necessit� : Rien
Sortie : cha�ne de caract�res la balise reconnue
Entraine : La balise est reconnue ou lev�e d'une exception
******************************************************************************/
char * Cparseur::PARreconnaitreBalise(char * pcSource)
{
	unsigned int uiCptr;

	if(pcSource == nullptr)
		throw Cexception(4);

	for(uiCptr = 0; uiCptr < PARNBRBALISES; uiCptr++)
		if(strcmp(pcPARtabBalisesValeurs[uiCptr][0],pcSource) == 0)
			return pcPARtabBalisesValeurs[uiCptr][0];

	throw Cexception(6, "Balise inconnue");
}

/******************************************************************************
PARstockerValeur
*******************************************************************************
Entr�e : (2 cha�nes de caract�res)pcBalise et pcValeur, la valeur � stocker dans la balise
Necessit� : Le fichier existe
Sortie : Un objet CMatrice de type MType
Entraine : la matrice est lue puis retourn�
******************************************************************************/
void Cparseur::PARstockerValeur(char * pcBalise, char * pcValeur)
{
	unsigned int uiCptr;

	if(pcBalise == nullptr || pcValeur == nullptr)
		throw Cexception(4);

	for(uiCptr = 0; uiCptr < PARNBRBALISES; uiCptr++)
		if(strcmp(pcPARtabBalisesValeurs[uiCptr][0], pcBalise) == 0)
			pcPARtabBalisesValeurs[uiCptr][1] = _strdup(pcValeur);
}

char * Cparseur::PARvaleurSuivante(char * pcBalise, char * pcChaine)
{
	char * pcTemp;
	char * pcRetour;
	unsigned int uiCompteur = 0;

	if(pcBalise == nullptr || pcBalise == nullptr)
		throw Cexception(4);

	pcTemp = strstr(pcChaine, pcBalise);

	//On va jusqu'au �gal en supprimant la balise
	while(*pcTemp != '=')
	{
		if(*pcTemp == '\0')
			throw Cexception(6, "Valeur non trouvee");
		*pcTemp = ' ';
		pcTemp++;
	}
	//Ensuite on supprime le �gal et tout les espace
	while(*pcTemp == '=' || *pcTemp == ' ' || *pcTemp == '\n')	
	{
		if(*pcTemp == '\0')
			throw Cexception(6, "Valeur non trouvee");
		*pcTemp = ' ';
		pcTemp++;
	}
	//Puis on retire la valeur de la chaine pour la renvoyer
	pcRetour = (char *)malloc(uiCompteur + 1);
	if(pcRetour == nullptr)
		throw Cexception(1);
	pcRetour[uiCompteur] = '\0';
	
	while(*pcTemp != ' ' && *pcTemp != '\n')
	{
		if(*pcTemp == '\0')
			throw Cexception(6, "Valeur non trouvee");
		uiCompteur++;
		pcRetour = (char *)realloc(pcRetour, uiCompteur + 1);
		if(pcRetour == nullptr)
			throw Cexception(2);
		pcRetour[uiCompteur - 1] = *pcTemp;
		pcRetour[uiCompteur] = '\0';
		*pcTemp = ' ';
		pcTemp++;
	}
	return pcRetour;
}