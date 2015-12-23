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
	void Init();
	/**
	Cleans data
	*/
	void Clean();



	/**
	Provide definition for pure virtual function
	*/
	bool isValid(std::string extension);
	/**
	Provide definition for pure virtual function
	*/
	void Load(std::string path, std::string extension);





};




#endif