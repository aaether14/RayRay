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
	void Enable();
	/**
	Clean engine's data
	*/
	void Clean();
	/**
	Initializes Controller Source, camera and game object
	*/
	void Init();



    /**
    Get information of application
    */
    inline AData * GetAppInfo(){return app_info.get();}




};




#endif
