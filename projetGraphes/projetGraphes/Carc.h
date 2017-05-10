#ifndef CARC
#define CARC

class Carc 
{
private :

	unsigned int uiARCDestination;

public : 

	/******************************************************************************
	Constructeur par d�faut
	*******************************************************************************
		Entr�e : Rien
		Necessit� : N�ant
		Sortie : Rien
		Entraine : L'objet en cours est initialis�.
	******************************************************************************/
	Carc();

/******************************************************************************
Constructeur � un attribut
*******************************************************************************
Entr�e : l'attribut destination
Necessit� : la'ttribut pass� en parametre correspond � un sommet
Sortie : Rien
Entraine : L'objet en cours est initialis�.
******************************************************************************/
	Carc(unsigned int uiDestination);

/******************************************************************************
Constructeur de recopie
*******************************************************************************
Entr�e : Objet Carc
Necessit� : N�ant
Sortie : Rien
Entraine : L'objet en cours est initialis� par recopie.
******************************************************************************/
	Carc(const Carc & ARCObjet);

/******************************************************************************
Destructeur
*******************************************************************************
Entr�e : Rien
Necessit� : N�ant
Sortie : Rien
Entraine : L'objet en cours est d�sallou�.
******************************************************************************/
	~Carc();

/******************************************************************************
M�thode de lecture de l'attribut destination
*******************************************************************************
Entr�e : Rien
Necessit� : N�ant
Sortie : retourne la destination
Entraine : N�ant.
******************************************************************************/
	unsigned int ARCLireDestination();

/******************************************************************************
M�thode de modification de l'attribut destination
*******************************************************************************
Entr�e : la destination de remplacement
Necessit� : destination corresppndante a un sommet existant
Sortie : Rien
Entraine : l'attribut destination est modifi�.
******************************************************************************/
	void ARCModifierDestination(unsigned int uiDestination);
	
};
#endif

