#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP




#include <stdafx.h>




/**
Controls the scene resources and the filters pack
*/
class DataManager : public AModule
{





public:



	/**
	Initializes with screen size
	*/
	AVoid Init();
	/**
	Cleans data
	*/
	AVoid Clean();
	/**
	Handles drag&drop entity adition
	*/
	AVoid Enable();






};


#endif