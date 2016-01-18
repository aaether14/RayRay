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
	AVoid Init();



	/**
	Cleans scene data
	*/
	AVoid Clean();


    /**
    Load a certain project
    */
    AVoid LoadProject(std::string path);





};





#endif
