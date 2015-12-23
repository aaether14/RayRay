#ifndef GLSL_RAYTRACER_HPP
#define GLSL_RAYTRACER_HPP



#include <stdafx.h>



/**
Provides functionality for glsl raytracing calculus
*/



class GLSLRaytracer : public AModule
{



	Shader * raytracing_program;



	GLuint sphere_texture;
	GLuint space_texture;



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

