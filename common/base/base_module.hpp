#ifndef BASE_MODEL_HPP
#define BASE_MODEL_HPP



#include <stdafx.h>



/**
Interface for modules
*/
class AModule
{


private:


	AModule * manager;


public:

	/**
	Add 'module' to 'key'
	*/
    virtual AVoid Add(std::string key, AModule*module);
	/**
	Get module from 'key'
	*/
	virtual AModule * Get(std::string key);
    /**
    Get module map pointer
    */
    virtual std::map < std::string, AModule* > * GetModuleMapPointer();



	/**
	Determine how module affects engine
	*/
    virtual AVoid Enable() = 0;
	/**
	Clean data
	*/
    virtual AVoid Clean() = 0;
	/**
	Initialize data
	*/
    virtual AVoid Init() = 0;
	/**
	Get manager
	*/
	virtual AModule * GetManager();


protected:


	std::map < std::string, AModule* > module_map;


	/**
	Set manager of module
	*/
    virtual AVoid SetManager(AModule * module);
	/**
	Standardized cleaning routine
	*/
    virtual AVoid CleanModule();



};





#endif
