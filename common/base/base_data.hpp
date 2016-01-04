#ifndef BASE_DATA_HPP
#define BASE_DATA_HPP



#include <stdafx.h>





/**
Provides functionality for engine data managment
*/
class AData
{


	std::map<std::string, GLfloat> float_map;
	std::map<std::string, GLint> int_map;
    std::map<std::string, std::string> string_map;
	std::map<std::string, glm::vec2> vec2_map;
	std::map<std::string, glm::vec3> vec3_map;
	std::map<std::string, glm::vec4> vec4_map;



	std::string data_component_name;



public:



	//Getters----------------------------------------------------------------



	/**
	Get float from map
	*/
	inline GLfloat GetFloat(std::string name){ return float_map[name]; }

	/**
	Get int from map
	*/
	inline GLint GetInt(std::string name){ return int_map[name]; }
	
    /**
    Get string from map
    */
    inline std::string GetString(std::string name){return string_map[name];}

	/**
	Get vec2 from map
	*/
	inline glm::vec2 GetVec2(std::string name){ return vec2_map[name]; }


	/**
	Get vec3 from map
	*/
	inline glm::vec3 GetVec3(std::string name){ return vec3_map[name]; }


	/**
	Get vec4 from map
	*/
	inline glm::vec4 GetVec4(std::string name){ return vec4_map[name]; }

	/**
	Get component name
	*/
	inline std::string GetComponentName(){ return data_component_name; }






	//Setters-------------------------------------------------------------



	/**
	Set float
	*/
	inline void SetFloat(std::string name, GLfloat value){ float_map[name] = value; }

	/**
	Set int
	*/
	inline void SetInt(std::string name, GLint value){ int_map[name] = value; }

    /**
    Set string
    */
    inline void SetString(std::string name, std::string value){string_map[name] = value;}

	/**
	Set vec2
	*/
	inline void SetVec2(std::string name, glm::vec2 value){ vec2_map[name] = value; }

	/**
	Set vec3
	*/
	inline void SetVec3(std::string name, glm::vec3 value){ vec3_map[name] = value; }

	/**
	Set vec4
	*/
	inline void SetVec4(std::string name, glm::vec4 value){ vec4_map[name] = value; }

	/**
	Set component name
	*/

	inline void SetComponentName(std::string name){ data_component_name = name; }



	//Other--------------------------------------------------------------------




	/**
	Load interface from xml
	*/
	void LoadInterface(boost::property_tree::ptree base_index);
	/**
	Debug procedure
	*/
	void Debug();

	/**
	Cleaning procedure
	*/
	void Clean();

	/**
	Provide xml-saving function
	*/
	boost::property_tree::ptree Save();




};




#endif
