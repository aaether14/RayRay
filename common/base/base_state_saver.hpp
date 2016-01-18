#ifndef BASE_STATE_SAVER_HPP
#define BASE_STATE_SAVER_HPP



#include <stdafx.h>



/**


Interface for storing any scene information prone to change


*/
class AStateSaver : public AModule
{



private:


	/**
	To be queried to update ui
	*/
    ABoolean should_reset;
	/**
	File management
	*/
	std::string source_path;


public:





	/**
	Initializes data
	*/
    inline AVoid Init() {}
	/**
	Cleans data
	*/
    inline AVoid Clean(){}
	/**
	Enables module to affect scene
	*/
    inline AVoid Enable(){}





	/**
	Saving to file 
	*/
    virtual AVoid Save() = 0;
	/**
	Loading from file
	*/
    virtual AVoid Load() = 0;
	/**
	Reseting state
	*/
    virtual AVoid Reset() = 0;



	/**
	Set reset query variable
	*/
    inline AVoid SetShouldReset(ABoolean should_reset){ this->should_reset = should_reset; }
	/**
	Query should reset
	*/
    inline ABoolean ShouldReset(){ return should_reset; }



	/**
	Set path to be used by Save/Load
	*/
    inline AVoid SetPath(std::string source_path){ this->source_path = source_path; }
	/**
	Get the path of the file the state changer affects
	*/
	inline std::string GetPath(){ return source_path; }


};





#endif
