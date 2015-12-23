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




	inline char* GetSceneFile(){ return AString::char_to_str(scene_file); }



	/**
	Loads all resrouce paths
	*/
	void LoadResourcePaths(char *path);


};





#endif