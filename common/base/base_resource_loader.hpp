#ifndef BASE_RESOURCE_LOADER_HPP
#define BASE_RESOURCE_LOADER_HPP





#include <stdafx.h>






/**


Can be derived to store any state changers
for centralised save/load


*/
class BaseResourceLoader : public AModule
{


private:





protected:




public:



	/**
	Initializes data
	*/
    AVoid Init();
	/**
	Cleans data
	*/
    AVoid Clean();
	/**
	Enables module to affect scene
	*/
    AVoid Enable();




	/**
	Iterates through all state changer map and use their save function
	*/
    AVoid SaveChanges();
	/**
	Iterates through all state changer map and use their load function
	*/
    AVoid LoadChanges();
	/**
	Iterates through all state changer map and use their reset function
	*/
    AVoid NoChanges();



};





#endif
