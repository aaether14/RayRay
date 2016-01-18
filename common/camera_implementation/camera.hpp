#ifndef CAMERA_HPP
#define CAMERA_HPP




#include <stdafx.h>





/**


Basic camera implementation
Can support 1st and 3rd person views
Also has frustum functionality for frustum culling


*/
class Camera : public AModule
{







	/**
	Variable used by the camera controller
	*/
	ADouble camera_speed[4];
	/**
	Angles to compute spherical coords
	*/
	glm::vec2 camera_angles;
	/**
	Used to compute mouse move
	*/
	glm::vec2 last_mouse_position;


	/**
	Pointer to class that can create World and Camera matrices out of ViewInfo
	*/
	View *view;
	/**
	Info that View can use to create World and Camera matrices
	*/
	ViewInfo *info;




	/**
	Process input to get ViewInfo
	*/
    AVoid ProcessInput();
	/**
	Compute angles out of mouse movement
	*/
    AVoid ComputeAngles();
	/**
	Fill ViewInfo
	*/
    AVoid SetInfo();





public:




enum {CAMERA_SPEED, MOUSE_SPEED, ROTATION_SPEED, CAMERA_BASE_SPEED};




	/**
	Initializes data
	*/
    AVoid Init();
	/**
	Cleans data
	*/
    AVoid Clean();
	/**
	Matches interface
	*/
    AVoid Enable();






	/**
	Get speed
	*/
	inline AFloat GetSpeed(AUInt ind){ return camera_speed[ind];}
	/**
	Set speed
	*/
    inline AVoid SetSpeed(AUInt ind, ADouble speed){camera_speed[ind] = speed;}
	/**
	Set camera angles
	*/
    inline AVoid SetCameraAngles(glm::vec2 angles){camera_angles = angles;}
	/**
	Get camera angles
	*/
    inline glm::vec2 GetCameraAngles(){return camera_angles;}







	/**
	Get pointer to View
	*/
    inline View * GetView() { return this->view; }
	/**
	Get pointer to ViewInfo
	*/
	inline ViewInfo *GetInfo() { return this->info; }




};


#endif
