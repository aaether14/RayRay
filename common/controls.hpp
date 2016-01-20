#ifndef CONTROLS_HPP
#define CONTROLS_HPP





#include <stdafx.h>







/**
Derives from controller source in order to hold engine data like camera, filters and scene resources
*/
class Controller : public ControllerSource
{



public:




	/**
	Enable controller source and camera computations
	*/
	AVoid Enable();
	/**
	Clean engine's data
	*/
	AVoid Clean();
	/**
	Initializes Controller Source, camera and game object
	*/
	AVoid Init();






};




#endif
