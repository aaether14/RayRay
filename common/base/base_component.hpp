#ifndef BASE_COMPONENT_HPP
#define BASE_COMPONENT_HPP



#include <stdafx.h>



/**


Base component implementation
Interface for adding components to entities
Dependent on file's extension to determine it's actions


*/
class AComponent : public AData
{

private:


protected:


public:


	/**
	Check if the component can handle the extension
	*/
    virtual ABoolean isValid(std::string extension) = 0;
	/**
	Provide resource loading function for the component based on extension
	*/
    virtual AVoid Load(std::string path, std::string extension) = 0;
	/**
	Provide initialization routine
	*/
    virtual AVoid Init() = 0;
	/**
	Provide cleaning routine
	*/
    virtual AVoid Clean() = 0;



};



#endif
