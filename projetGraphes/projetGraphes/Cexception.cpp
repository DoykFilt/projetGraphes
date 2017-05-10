#include "Cexception.h"

/******************************************************************************
Constructeur par défaut
*******************************************************************************
	Entrée : Rien
	Necessité : Néant
	Sortie : Rien
	Entraine : L'objet en cours est initialisé.
******************************************************************************/
Cexception::Cexception()
{
	uiEXCValeur = ERREUR_DEFAUT;
	pcEXCMessage = _strdup(MESSAGE_DEFAUT);
	pcEXCMessageDetail = _strdup(MESSAGE_SUPP_DEFAUT);
}

/******************************************************************************
Constructeur à 2 arguments
*******************************************************************************
Entrée : La valeur et le message associé.
Necessité : Néant
Sortie : Rien
Entraine : L'objet en cours est initialisé avec un message détaillé de l'erreur.
******************************************************************************/
Cexception::Cexception(unsigned int uiValeur, char * pcMessageDetail)
{
	uiEXCValeur = uiValeur;
	switch(uiEXCValeur)
	{
		case ERREUR_ALLOCATION :
			pcEXCMessage = _strdup(MESSAGE_ALLOCATION);
			break;
		case ERREUR_REALLOCATION : 
			pcEXCMessage = _strdup(MESSAGE_REALLOCATION);
			break;
		case ERREUR_CALCUL :
			pcEXCMessage = _strdup(MESSAGE_CALCUL);
			break;
		case ERREUR_PARAM :
			pcEXCMessage = _strdup(MESSAGE_PARAM);
			break;
		case ERREUR_FICHIER :
			pcEXCMessage = _strdup(MESSAGE_FICHIER);
			break;
		case ERREUR_PARSEUR :
			pcEXCMessage = _strdup(MESSAGE_PARSEUR);
			break;
		case ERREUR_PRECONDITIONS :
			pcEXCMessage = _strdup(MESSAGE_PRECONDITIONS);
			break;
		default : 
			pcEXCMessage = _strdup(MESSAGE_DEFAUT);
	}
	pcEXCMessageDetail = _strdup(pcMessageDetail);
}

/******************************************************************************
Constructeur de recopie
*******************************************************************************
Entrée : Un objet de la classe.
Necessité : Néant
Sortie :Rien
Entraine : Création d'un objet par recopie.
******************************************************************************/
Cexception::Cexception(const Cexception & EXCObjet)
{
	uiEXCValeur = EXCObjet.uiEXCValeur;
	pcEXCMessage = _strdup(EXCObjet.pcEXCMessage);
	pcEXCMessageDetail = _strdup(EXCObjet.pcEXCMessageDetail);
}

/******************************************************************************
Destructeur par défaut
*******************************************************************************
Entrée : Rien
Necessité : Néant
Sortie : Rien
Entraine : L'espace alloué par l'objet a été libéré
******************************************************************************/
Cexception::~Cexception()
{
	free(pcEXCMessage);
	free(pcEXCMessageDetail);
}

/******************************************************************************
Méthode de lecture de la valeur
*******************************************************************************
Entrée : Rien
Necessité : Néant
Sortie : Valeur
Entraine : Retourne la valeur.
******************************************************************************/
unsigned int Cexception::EXCLire_Valeur() const
{
	return uiEXCValeur;
}

/******************************************************************************
Méhode de modification de la valeur
*******************************************************************************
Entrée : Valeur
Necessité : Valeur existante.
Sortie : Néant
Entraine : Modification de la valeur et du message associé.
******************************************************************************/
void Cexception::EXCModifier_Valeur(unsigned int uiValeur, bool reinitSuppMessage)
{
	uiEXCValeur = uiValeur;
	switch(uiEXCValeur)
	{
		case ERREUR_ALLOCATION :
			pcEXCMessage = _strdup(MESSAGE_ALLOCATION);
			break;
		case ERREUR_REALLOCATION : 
			pcEXCMessage = _strdup(MESSAGE_REALLOCATION);
			break;
		case ERREUR_CALCUL :
			pcEXCMessage = _strdup(MESSAGE_CALCUL);
			break;
		case ERREUR_PARAM :
			pcEXCMessage = _strdup(MESSAGE_PARAM);
			break;
		case ERREUR_FICHIER :
			pcEXCMessage = _strdup(MESSAGE_FICHIER);
			break;
		case ERREUR_PARSEUR :
			pcEXCMessage = _strdup(MESSAGE_PARSEUR);
			break;
		case ERREUR_PRECONDITIONS :
			pcEXCMessage = _strdup(MESSAGE_PRECONDITIONS);
			break;
		default : 
			pcEXCMessage = _strdup(MESSAGE_DEFAUT);
	}

	if(reinitSuppMessage == true)
	{
		free(pcEXCMessageDetail);
		pcEXCMessageDetail= _strdup(MESSAGE_SUPP_DEFAUT);
	}
}

/******************************************************************************
Méthode de lecture du message
*******************************************************************************
Entrée : Rien
Necessité : Néant
Sortie : char * le message
Entraine : Retourne le message entier
******************************************************************************/
char * Cexception::EXCLire_Message() const
{
	size_t stTailleMessage = strlen(pcEXCMessage) + strlen(pcEXCMessageDetail) + 2;
	char* pcMessageComplet = new char[stTailleMessage + 1];
	unsigned int uiCompteurMessage, uiCompteurDetail;

	for(uiCompteurMessage = 0; uiCompteurMessage < strlen(pcEXCMessage); uiCompteurMessage++)
		pcMessageComplet[uiCompteurMessage] = pcEXCMessage[uiCompteurMessage];

	if(strlen(pcEXCMessageDetail) > 0)
	{
		pcMessageComplet[uiCompteurMessage] = ' ';
		uiCompteurMessage++;
		pcMessageComplet[uiCompteurMessage] = '-';
		uiCompteurMessage++;
		pcMessageComplet[uiCompteurMessage] = ' ';
		uiCompteurMessage++;
	}

	for(uiCompteurDetail = 0; uiCompteurDetail < strlen(pcEXCMessageDetail); uiCompteurDetail++)
		pcMessageComplet[uiCompteurMessage + uiCompteurDetail] = pcEXCMessageDetail[uiCompteurDetail];
	pcMessageComplet[uiCompteurMessage + uiCompteurDetail] = '\0';

	return pcMessageComplet;
} 

/******************************************************************************
Méhode de modification du message
*******************************************************************************
Entrée : Char * Message
Necessité : Néant
Sortie : Rien
Entraine : Modification du message.
******************************************************************************/
void Cexception::EXCModifier_Message(char * pcMessage)
{
	free(pcEXCMessageDetail);
	pcEXCMessageDetail = _strdup(pcMessage);
}

/******************************************************************************
Surcharge de l'opérateur d'affectation
*******************************************************************************
Entrée : référence sur un objet de type Cexception
Necessité : Néant
Sortie : Rien
Entraine : L'objet a été affecté par recopie de l'objet en paramètre
******************************************************************************/
Cexception & Cexception::operator=(Cexception const & EXCexception)
{
	uiEXCValeur = EXCexception.uiEXCValeur;
	free(pcEXCMessage);
	pcEXCMessage = _strdup(EXCexception.pcEXCMessage);
	free(pcEXCMessageDetail);
	pcEXCMessageDetail = _strdup(EXCexception.pcEXCMessageDetail);

	return *this;
}