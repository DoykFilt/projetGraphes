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

/******************************************************************************
class Cexception
*******************************************************************************

	Cette classe permet de conte nir les informations nécessaire à la 
	compréhension d'erreurs levées

	Attributs
		uiEXCValeur : la valeur associée à l'erreur
		pcEXCMessage : le message automatiquement associé suivant la valeur
		pcEXCMessageDetail : un message complémentaire optionnel

******************************************************************************/
class Cexception
{
private :
	//###############################//
	//########## Attributs ##########//
	//###############################//
	unsigned int uiEXCValeur;
	char * pcEXCMessage;
	char * pcEXCMessageDetail;

public :

	//###################################################//
	//########## Constructeurs et destructeurs ##########//
	//###################################################//
	/******************************************************************************
	Constructeur par défaut
	*******************************************************************************
	Entrée : Rien
	Necessité : Néant
	Sortie : Rien
	Entraine : L'objet en cours est initialisé.
	******************************************************************************/
	Cexception(); 
	/******************************************************************************
	Constructeur de recopie
	*******************************************************************************
	Entrée : Un objet de la classe.
	Necessité : Néant
	Sortie :Rien
	Entraine : Création d'un objet par recopie.
	******************************************************************************/
	Cexception(const Cexception & EXCObjet);
	/******************************************************************************
	Constructeur à 2 arguments
	*******************************************************************************
	Entrée : La valeur et le message associé.
	Necessité : Néant
	Sortie : Rien
	Entraine : L'objet en cours est initialisé avec un message détaillé de l'erreur.
	******************************************************************************/
	Cexception(unsigned int uiValeur, char * pcMessageDetail=MESSAGE_SUPP_DEFAUT); 
	/******************************************************************************
	Destructeur par défaut
	*******************************************************************************
	Entrée : Rien
	Necessité : Néant
	Sortie : Rien
	Entraine : L'espace alloué par l'objet a été libéré
	******************************************************************************/
	~Cexception();

	//##############################//
	//########## Methodes ##########//
	//##############################//
	/******************************************************************************
	Méthode de lecture de la valeur
	*******************************************************************************
	Entrée : Rien
	Necessité : Néant
	Sortie : Valeur
	Entraine : Retourne la valeur.
	******************************************************************************/
	unsigned int EXCLire_Valeur() const;
	/******************************************************************************
	Méhode de modification de la valeur
	*******************************************************************************
	Entrée : Valeur
	Necessité : Valeur existante.
	Sortie : Néant
	Entraine : Modification de la valeur et du message associé.
	******************************************************************************/
	void EXCModifier_Valeur(unsigned int uiValeur, bool reinitSuppMessage=false);
	/******************************************************************************
	Méthode de lecture du message
	*******************************************************************************
	Entrée : Rien
	Necessité : Néant
	Sortie : char * le message
	Entraine : Retourne le message entier (concaténation entre celui par défaut et l'optionnel)
	******************************************************************************/
	char * EXCLire_Message() const;
	/******************************************************************************
	Méhode de modification du message
	*******************************************************************************
	Entrée : Char * Message
	Necessité : Néant
	Sortie : Rien
	Entraine : Modification du message.
	******************************************************************************/
	void EXCModifier_Message(char * pcMessage);

	//#############################################//
	//########## Surcharges d'opérateurs ##########//
	//#############################################//
	/******************************************************************************
	Surcharge de l'opérateur d'affectation
	*******************************************************************************
	Entrée : référence sur un objet de type Cexception
	Necessité : Néant
	Sortie : Rien
	Entraine : L'objet a été affecté par recopie de l'objet en paramètre
	******************************************************************************/
	Cexception & operator=(Cexception const & EXCexception);
};

#endif