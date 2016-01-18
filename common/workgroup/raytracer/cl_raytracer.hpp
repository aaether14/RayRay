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
	AVoid Init();


	/**
	Cleans data
	*/
	AVoid Clean();



	/**
	Determines how raytracer will affect scene
	*/
	AVoid Enable();





};




#endif