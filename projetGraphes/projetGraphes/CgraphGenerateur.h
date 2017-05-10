#ifndef CGRAPHGENERATEUR_H
#define CGRAPHGENERATEUR_H

#include "Cparseur.h"
#include "Cgraph.h"

/******************************************************************************
class CgraphGenerateur
*******************************************************************************

	Cette classe permet de créer un Cgraph à partir des des données brutes du parseur

	Attributs
		pPARGRGparseur : le parseur où sont contenues les données brutes

******************************************************************************/
class CgraphGenerateur
{
private :
	//########## Attributs ##########//
	Cparseur * pPARGRGparseur;

public :
	//########## Constructeurs - Desctructeur ##########//
	/******************************************************************************
	Constructeur
	*******************************************************************************
	Entrée : Rien
	Necessité : Néant
	Sortie : Rien
	Entraine : L'objet a été initialisé
	******************************************************************************/
	CgraphGenerateur();
	/******************************************************************************
	Constructeur avec un argument
	*******************************************************************************
	Entrée : un pointeur sur un objet de type Cparseur
	Necessité : Néant
	Sortie : Rien
	Entraine : L'objet a été initialisé
	******************************************************************************/
	CgraphGenerateur(Cparseur * pPARparseur);
	/******************************************************************************
	Constructeur de recopie
	*******************************************************************************
	Entrée : Référence sur un objet de type CgraphGenerateur
	Necessité : Néant
	Sortie : Rien
	Entraine : L'objet a été initialisé par recopie de l'objet en paramètre
	******************************************************************************/
	CgraphGenerateur(const CgraphGenerateur & GRGObjet);
	/******************************************************************************
	Destructeur
	*******************************************************************************
	Entrée : Rien
	Necessité : L'arbre a été désalloué
	Sortie : Rien
	Entraine : L'espace alloué pour les attributs de l'objet a été libéré
	******************************************************************************/
	~CgraphGenerateur();

	//########## Methodes ##########//
	/******************************************************************************
	GRGgenererGraph
	*******************************************************************************
	Entrée : Rien
	Necessité : Le parseur a récupéré les données brutes préalablement
	Sortie : l'objet reconnu de type Cgraph 
	Entraine : un objet de type Cgraph a été alloué et retourné
	******************************************************************************/
	Cgraph * GRGgenererGraph();
	/******************************************************************************
	GRGsetParseur
	*******************************************************************************
	Entrée : Un pointeur sur un objet de type Cparseur
	Necessité : Néant
	Sortie : Rien
	Entraine : L'ancien parseur a été remplacé par le nouveau
	******************************************************************************/
	void GRGsetParseur(Cparseur * pPARparseur);
	/******************************************************************************
	GRGgetParseur
	*******************************************************************************
	Entrée : Rien
	Necessité : Néant
	Sortie : Un poiteur sur le parseur
	Entraine : Le pointeur a été retourné
	******************************************************************************/
	Cparseur * GRGgetParseur();
	/******************************************************************************
	GRGreconnaitreEntier
	*******************************************************************************
	Entrée : une chaine de caractère contenant l'entier à reconnaitre
	Necessité : La chaine est convertible en entier
	Sortie : L'entier reconnu
	Entraine : L'entier a été reconnu et renvoyé
	******************************************************************************/
	unsigned int GRGreconnaitreEntier(char * pcElm);
	
	//########## Surcharge d'operateur ##########//
	/******************************************************************************
	surcharge de l'opérateur d'affectation
	*******************************************************************************
	Entrée : un objet du même type
	Necessité : Néant
	Sortie : Une référence sur l'objet en cours qui a été modifié
	Entraine : L'objet en cours est une copie de l'objet en paramètre
	******************************************************************************/
	CgraphGenerateur & operator=(CgraphGenerateur const & GRGObjet);
};

#endif