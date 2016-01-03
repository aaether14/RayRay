#ifndef RESOURCE_LOADER_HPP
#define RESOURCE_LOADER_HPP






#include <stdafx.h>




class ResourceLoader : public BaseResourceLoader
{


	std::string scene_file;



public:




	/**
	Initialize state savers and resource paths
	*/
	void Init();



	/**
	Cleans scene data
	*/
	void Clean();




	inline std::string GetSceneFile(){ return scene_file;}



	/**
	Loads all resrouce paths
	*/
	void LoadResourcePaths(std::string path);


};





#endif