#ifndef RAY_TRACER_SCENE_BUILDER_HPP
#define RAY_TRACER_SCENE_BUILDER_HPP



#include <stdafx.h>





/**
Provdies functionality for building scene float array from scene manager
*/
class RayTracerSceneBuilder : public AModule
{



	std::vector<cl_float> scene_data;




	/**
	Add sphere to scene
	*/
	void AddSphere(glm::vec4 pos, cl_float sq_dist, cl_uint mat);
	/**
	Add plane to scene
	*/
	void AddPlane(glm::vec4 normal, cl_float dist, cl_uint mat);
	/**
	Add material to scene
	*/
	void AddMaterial(cl_float relf, cl_float refr, cl_float spec, cl_float diff, glm::vec4 amb);
	/**
	Add light scene
	*/
	void AddLight(cl_uint mat, glm::vec4 center);



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
	Updates scene data
	*/
	void Enable();




	/**
	Give scene data pointer
	*/
	cl_float * GetSceneDataPointer(){ return &scene_data[0]; }


	/**
	Get scene size
	*/
	size_t GetSceneSize(){ return sizeof(cl_float) * scene_data.size(); }








};





#endif