#ifndef RESOURCE_LOADER_HPP
#define RESOURCE_LOADER_HPP






#include <stdafx.h>
#define PROJECT_FOLDER "data/projects/"





class ResourceLoader : public BaseResourceLoader
{





public:




	/**
	Initialize state savers and resource paths
	*/
	void Init();



	/**
	Cleans scene data
	*/
	void Clean();


    /**
    Load a certain project
    */
    void LoadProject(std::string path);





};





#endif
