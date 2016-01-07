#ifndef OPENCL_RAYTRACER_HPP
#define OPENCL_RAYTRACER_HPP



#include <stdafx.h>





/**
Provides functionality for opencl raytracing calculus
*/
class CLRaytracer : public AModule
{







public:



	/**
	Initailizes data
	*/
	void Init();


	/**
	Cleans data
	*/
	void Clean();



	/**
	Determines how raytracer will affect scene
	*/
	void Enable();





};




#endif