#include "Carc.h"


/******************************************************************************
Constructeur par d�faut
*******************************************************************************
	Entr�e : Rien
	Necessit� : N�ant
	Sortie : Rien
	Entraine : L'objet en cours est initialis�.
******************************************************************************/
Carc::Carc()
{
	uiARCDestination = 0;
}

/******************************************************************************
Constructeur � un attribut
*******************************************************************************
	Entr�e : l'attribut destination
	Necessit� : la'ttribut pass� en parametre correspond � un sommet
	Sortie : Rien
	Entraine : L'objet en cours est initialis�.
******************************************************************************/
Carc::Carc(unsigned int uiDestination)
{
	uiARCDestination = uiDestination;
}

/******************************************************************************
Constructeur de recopie
*******************************************************************************
	Entr�e : Objet Carc
	Necessit� : N�ant
	Sortie : Rien
	Entraine : L'objet en cours est initialis� par recopie.
******************************************************************************/
Carc::Carc(const Carc & ARCObjet)
{
	uiARCDestination = ARCObjet.uiARCDestination;
}
		
/******************************************************************************
Destructeur
*******************************************************************************
	Entr�e : Rien
	Necessit� : N�ant
	Sortie : Rien
	Entraine : L'objet en cours est d�sallou�.
******************************************************************************/
Carc::~Carc()
{}
		
/******************************************************************************
M�thode de lecture de l'attribut destination
*******************************************************************************
	Entr�e : Rien
	Necessit� : N�ant
	Sortie : retourne la destination
	Entraine : N�ant.
******************************************************************************/
unsigned int Carc::ARCLireDestination()
{
	return uiARCDestination;
}
		
/******************************************************************************
M�thode de modification de l'attribut destination
*******************************************************************************
	Entr�e : la destination de remplacement
	Necessit� : destination corresppndante a un sommet existant
	Sortie : Rien
	Entraine : l'attribut destination est modifi�.
******************************************************************************/
void Carc::ARCModifierDestination(unsigned int uiDestination)
{
	uiARCDestination = uiDestination;
}