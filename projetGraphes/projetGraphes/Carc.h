#ifndef CARC
#define CARC

class Carc 
{
	private :
		unsigned int uiARCDestination;

	public : 
		Carc();
		Carc(unsigned int uiDestination);
		Carc(const Carc & ARCObjet);
		~Carc();
		unsigned int ARCLireDestination();
		void ARCModifierDestination(unsigned int uiDestination);
	
};
#endif

