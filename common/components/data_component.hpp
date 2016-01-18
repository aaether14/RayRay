#ifndef DATA_COMPONENT_HPP
#define DATA_COMPONENT_HPP



#include <stdafx.h>



/**
Holds data for component
*/
class DataComponent : public AComponent
{


public:



	/**
	Initialize data
	*/
	AVoid Init();
	/**
	Cleans data
	*/
	AVoid Clean();



	/**
	Provide definition for pure virtual function
	*/
	ABoolean isValid(std::string extension);
	/**
	Provide definition for pure virtual function
	*/
	AVoid Load(std::string path, std::string extension);





};




#endif