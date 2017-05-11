#include "Carc.h"


/******************************************************************************
Constructeur par défaut
*******************************************************************************
	Entrée : Rien
	Necessité : Néant
	Sortie : Rien
	Entraine : L'objet en cours est initialisé.
******************************************************************************/
Carc::Carc()
{
	uiARCDestination = 0;
}

/******************************************************************************
Constructeur à un attribut
*******************************************************************************
	Entrée : l'attribut destination
	Necessité : la'ttribut passé en parametre correspond à un sommet
	Sortie : Rien
	Entraine : L'objet en cours est initialisé.
******************************************************************************/
Carc::Carc(unsigned int uiDestination)
{
	uiARCDestination = uiDestination;
}

/******************************************************************************
Constructeur de recopie
*******************************************************************************
	Entrée : Objet Carc
	Necessité : Néant
	Sortie : Rien
	Entraine : L'objet en cours est initialisé par recopie.
******************************************************************************/
Carc::Carc(const Carc & ARCObjet)
{
	uiARCDestination = ARCObjet.uiARCDestination;
}
		
/******************************************************************************
Destructeur
*******************************************************************************
	Entrée : Rien
	Necessité : Néant
	Sortie : Rien
	Entraine : L'objet en cours est désalloué.
******************************************************************************/
Carc::~Carc()
{}
		
/******************************************************************************
Méthode de lecture de l'attribut destination
*******************************************************************************
	Entrée : Rien
	Necessité : Néant
	Sortie : retourne la destination
	Entraine : Néant.
******************************************************************************/
unsigned int Carc::ARCLireDestination()
{
	return uiARCDestination;
}
		
/******************************************************************************
Méthode de modification de l'attribut destination
*******************************************************************************
	Entrée : la destination de remplacement
	Necessité : destination corresppndante a un sommet existant
	Sortie : Rien
	Entraine : l'attribut destination est modifié.
******************************************************************************/
void Carc::ARCModifierDestination(unsigned int uiDestination)
{
	uiARCDestination = uiDestination;
}