#ifndef UI_MANAGER
#define UI_MANAGER




#include <stdafx.h>




/**


CEGUI initialisation


*/
class UIManager : public AUIWindow
{




public:




	/**
	Initializes CEGUI
	*/
	AVoid Init();


	/**
	Cleans data
	*/
	AVoid Clean();



	/**
	Renders UI to scene 
	*/
	AVoid Enable();




};






#endif
