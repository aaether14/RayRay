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
	GLdouble camera_speed[4];
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
	Stores the 6 frustum planes
	*/
	Frustum * frustum;




	/**
	Process input to get ViewInfo
	*/
	void ProcessInput();
	/**
	Compute angles out of mouse movement
	*/
	void ComputeAngles();
	/**
	Fill ViewInfo
	*/
	void SetInfo();





public:




enum {CAMERA_SPEED, MOUSE_SPEED, ROTATION_SPEED, CAMERA_BASE_SPEED};




	/**
	Initializes data
	*/
	void Init();
	/**
	Cleans data
	*/
	void Clean();
	/**
	Matches interface
	*/
	void Enable();






	/**
	Get speed
	*/
	inline GLfloat GetSpeed(GLuint ind){ return camera_speed[ind];}
	/**
	Set speed
	*/
	inline void SetSpeed(GLuint ind, GLdouble speed){camera_speed[ind] = speed;}
	/**
	Create frustum out of Projection*View
	*/
	inline void SetFrustum(glm::mat4 MV) { this->frustum->Create(MV); }
	/**
	Set camera angles
	*/
	void SetCameraAngles(glm::vec2 angles){camera_angles = angles;}
	/**
	Get camera angles
	*/
	glm::vec2 GetCameraAngles(){return camera_angles;}







	/**
	Get pointer to View
	*/
    inline View * GetView() { return this->view; }
	/**
	Get pointer to ViewInfo
	*/
	inline ViewInfo *GetInfo() { return this->info; }
	/**
	Get pointer to Frustum
	*/
	inline Frustum *GetFrustum() { return this->frustum; }




};


#endif
