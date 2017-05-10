#ifndef CARC
#define CARC

class Carc 
{
private :

	unsigned int uiARCDestination;

public : 

	/******************************************************************************
	Constructeur par défaut
	*******************************************************************************
		Entrée : Rien
		Necessité : Néant
		Sortie : Rien
		Entraine : L'objet en cours est initialisé.
	******************************************************************************/
	Carc();

/******************************************************************************
Constructeur à un attribut
*******************************************************************************
Entrée : l'attribut destination
Necessité : la'ttribut passé en parametre correspond à un sommet
Sortie : Rien
Entraine : L'objet en cours est initialisé.
******************************************************************************/
	Carc(unsigned int uiDestination);

/******************************************************************************
Constructeur de recopie
*******************************************************************************
Entrée : Objet Carc
Necessité : Néant
Sortie : Rien
Entraine : L'objet en cours est initialisé par recopie.
******************************************************************************/
	Carc(const Carc & ARCObjet);

/******************************************************************************
Destructeur
*******************************************************************************
Entrée : Rien
Necessité : Néant
Sortie : Rien
Entraine : L'objet en cours est désalloué.
******************************************************************************/
	~Carc();

/******************************************************************************
Méthode de lecture de l'attribut destination
*******************************************************************************
Entrée : Rien
Necessité : Néant
Sortie : retourne la destination
Entraine : Néant.
******************************************************************************/
	unsigned int ARCLireDestination();

/******************************************************************************
Méthode de modification de l'attribut destination
*******************************************************************************
Entrée : la destination de remplacement
Necessité : destination corresppndante a un sommet existant
Sortie : Rien
Entraine : l'attribut destination est modifié.
******************************************************************************/
	void ARCModifierDestination(unsigned int uiDestination);
	
};
#endif

