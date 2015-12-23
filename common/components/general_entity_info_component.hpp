#ifndef GENERAL_ENTITY_INFO_COMPONENT
#define GENERAL_ENTITY_INFO_COMPONENT





#include <stdafx.h>




/**


Info component implementation
Affects entity


*/
class InfoComponent : public AComponent
{



	/**
	Actual info for an entity
	*/
	class GeneralEntityInfo
	{


	public:


		std::string entity_name;


		/**
		Read general information regarding the entity from a file
		*/
		void Read(std::string path);
		/**
		Create a boost::property_tree::ptree from the data
		*/
		boost::property_tree::ptree GetPtree();
		



	}*info;
	


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


	/**
	Get pointer to entity information
	*/
	GeneralEntityInfo * GetInfo(){ return info; }



};





#endif