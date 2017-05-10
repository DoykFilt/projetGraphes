#ifndef CEXCEPTION_H
#define CEXCEPTION_H

#include <string.h>
#include <stdlib.h>
using namespace std;

#define ERREUR_DEFAUT 0
#define MESSAGE_DEFAUT "Erreur non definie"
#define MESSAGE_SUPP_DEFAUT ""
#define ERREUR_ALLOCATION 1
#define MESSAGE_ALLOCATION "Echec de l'allocation"
#define ERREUR_REALLOCATION 2
#define MESSAGE_REALLOCATION "Echec de la reallocation"
#define ERREUR_CALCUL 3
#define MESSAGE_CALCUL "Calculs imcompatibles"
#define ERREUR_PARAM 4
#define MESSAGE_PARAM "Parametres inappriopries"
#define ERREUR_FICHIER 5
#define MESSAGE_FICHIER "Echec de l'ouverture du fichier"
#define ERREUR_PARSEUR 6
#define MESSAGE_PARSEUR "Echec lors du parsage"
#define ERREUR_PRECONDITIONS 7
#define MESSAGE_PRECONDITIONS "Impossible d'utiliser la methode/fonction"

class Cexception
{
private :

	//Attributs
	unsigned int uiEXCValeur;
	char * pcEXCMessage;
	char * pcEXCMessageDetail;

public :

	//Constructeurs et destructeurs
	Cexception(); 
	Cexception(const Cexception & EXCObjet);
	Cexception(unsigned int uiValeur, char * pcMessageDetail=MESSAGE_SUPP_DEFAUT); 
	~Cexception();

	//Methodes
	unsigned int EXCLire_Valeur() const;
	void EXCModifier_Valeur(unsigned int uiValeur, bool reinitSuppMessage=false);
	char * EXCLire_Message() const;
	void EXCModifier_Message(char *pcMessage);

	//Surcharges d'opérateurs
	Cexception & operator=(Cexception const & EXCexception);
};

#endif