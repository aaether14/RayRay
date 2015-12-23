#ifndef UI_MANAGER
#define UI_MANAGER




#include <stdafx.h>




/**


CEGUI initialisation


*/
class UIManager : public AModule
{




public:




	/**
	Initializes CEGUI
	*/
	void Init();


	/**
	Cleans data
	*/
	void Clean();



	/**
	Renders UI to scene 
	*/
	void Enable();




};






#endif