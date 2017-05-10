#ifndef CPARSEUR_H
#define CPARSEUR_H

/******************************************************************************
class Cparseur
*******************************************************************************

	Cette classe permet de trnasformer les données d'un fichier en données
	brut à l'aide de balises et d'en sortir un graph

	Attributs
		uiPARNbrBalises : le nombre de balises détectables
		ppcPARBalises : Les balises à repérer dans le texte
		pcPARtabBalisesValeurs : Les données brutes relevées du fichier, chaque
			ligne correspond à une balise : la première colonne le nom de la 
			balise et la seconde sa valeur détecté

******************************************************************************/
class Cparseur
{
private :
	unsigned int uiPARNbrBalises;
	char ** ppcPARBalises;
	char *** pppcPARtabBalisesValeurs;

public :
	//########## Constructeurs et destructeurs ##########//
	/******************************************************************************
	Constructeur
	*******************************************************************************
	Entrée : char ** tableau contenant les noms de balise, unsigned int le nombre de balise
	Necessité : uiNbrBalises correspond au nombre de balises dans pcBalises
	Sortie : Rien
	Entraine : L'objet a été initialisé
	******************************************************************************/
	Cparseur(char ** ppcBalises, unsigned int uiNbrBalises);
	/******************************************************************************
	Constructeur de recopie
	*******************************************************************************
	Entrée : Référence sur un objet de type Cparseur
	Necessité : Néant
	Sortie : Rien
	Entraine : L'objet a été initialisé par recopie de l'objet en paramètre
	******************************************************************************/
	Cparseur(Cparseur & PARObjet);
	/******************************************************************************
	Destructeur
	*******************************************************************************
	Entrée : Rien
	Necessité : Néant
	Sortie : Rien
	Entraine : L'espace alloué pour les attributs de l'objet a été libéré
	******************************************************************************/
	~Cparseur();

	//########## Méthodes ##########//
	/******************************************************************************
	PARbrut
	*******************************************************************************
	Entrée : Rien
	Necessité : Néant
	Sortie : char *** un pointeur sur la matrice contenant les données brutes
	Entraine : la matrice a été renvoyée
	******************************************************************************/
	char *** PARbrut(){ return pppcPARtabBalisesValeurs; }
	/******************************************************************************
	PARvaleurSuivante
	*******************************************************************************
	Entrée : (2 chaînes de caractères)pcBalise et pcChaine
	Necessité : il y a une valeur associée à la balise dans la chaîne de caractère
	Sortie : une chaine de caractère, la valeur associée
	Entraine : la valeur est trouvée, renvoiée et éffacé de la chaîne de caractère
	******************************************************************************/
	char * PARvaleurSuivante(char * pcBalise, char * pcChaine);
	//Permet de récolter les données d'un fichier et de les stocker sous un format brut
	/******************************************************************************
	PARLire (inspiré par les méthodes de compilation)
	*******************************************************************************
	Entrée : pcfilename le chemin d'accès au fichier (chaîne de caractère)
	Necessité : Le fichier existe et les données dont au bon format dans le fichier
	Sortie : Rien
	Entraine : les données sont lues et stockées sous format brut
	******************************************************************************/
	void PARLire(char * pcfilename);
	/******************************************************************************
	PARLireNbrBalise
	*******************************************************************************
	Entrée : Rien
	Necessité : Néant
	Sortie : unsigned int, le nombre de balises
	Entraine : uiPARNbrBalises a été renvoyé
	******************************************************************************/
	unsigned int PARLireNbrBalise() { return uiPARNbrBalises; }

private :
	//Méthodes utilisé en interne pour le parsage
	/******************************************************************************
	PARreconnaitreBalise
	*******************************************************************************
	Entrée : pcSource(chaîne de caractère)
	Necessité : Rien
	Sortie : chaîne de caractères la balise reconnue
	Entraine : La balise est reconnue ou levée d'une exception
	******************************************************************************/
	char * PARreconnaitreBalise(char * pcSource);
	/******************************************************************************
	PARstockerValeur
	*******************************************************************************
	Entrée : (2 chaînes de caractères)pcBalise et pcValeur, la valeur à stocker dans la balise
	Necessité : Le fichier existe
	Sortie : Un objet CMatrice de type MType
	Entraine : la matrice est lue puis retourné
	******************************************************************************/
	void PARstockerValeur(char * pcBalise, char * pcValeur);

public :
	//########## Surcharges d'opérateurs ##########//
	/******************************************************************************
	surcharge de l'opérateur d'affectation
	*******************************************************************************
	Entrée : un objet du même type
	Necessité : Néant
	Sortie : Une référence sur l'objet en cours qui a été modifié
	Entraine : L'objet en cours est une copie de l'objet en paramètre
	******************************************************************************/
	Cparseur & operator=(Cparseur const & PARparseur);
};

#endif