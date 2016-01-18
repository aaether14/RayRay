#ifndef CONTROLS_HPP
#define CONTROLS_HPP





#include <stdafx.h>







/**
Derives from controller source in order to hold engine data like camera, filters and scene resources
*/
class Controller : public ControllerSource
{


    boost::shared_ptr<AData> app_info;


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



    /**
    Get information of application
    */
    inline AData * GetAppInfo(){return app_info.get();}




};




#endif
