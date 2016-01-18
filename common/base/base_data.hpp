#ifndef BASE_DATA_HPP
#define BASE_DATA_HPP



#include <stdafx.h>





/**
Provides functionality for engine data managment
*/
class AData
{


    std::map<std::string, AFloat> float_map;
    std::map<std::string, AInt> int_map;
    std::map<std::string, std::string> string_map;
    std::map<std::string, glm::vec2> vec2_map;
    std::map<std::string, glm::vec3> vec3_map;
    std::map<std::string, glm::vec4> vec4_map;



    std::string data_component_name;



public:



    //Getters----------------------------------------------------------------



    /**
    Get AFloat from map
    */
    inline AFloat GetFloat(std::string name){ return float_map[name]; }

    /**
    Get AInt from map
    */
    inline AInt GetInt(std::string name){ return int_map[name]; }

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
    Set AFloat
    */
    inline AVoid SetFloat(std::string name, AFloat value){ float_map[name] = value; }

    /**
    Set AInt
    */
    inline AVoid SetInt(std::string name, AInt value){ int_map[name] = value; }

    /**
    Set string
    */
    inline AVoid SetString(std::string name, std::string value){string_map[name] = value;}

    /**
    Set vec2
    */
    inline AVoid SetVec2(std::string name, glm::vec2 value){ vec2_map[name] = value; }

    /**
    Set vec3
    */
    inline AVoid SetVec3(std::string name, glm::vec3 value){ vec3_map[name] = value; }

    /**
    Set vec4
    */
    inline AVoid SetVec4(std::string name, glm::vec4 value){ vec4_map[name] = value; }

    /**
    Set component name
    */

    inline AVoid SetComponentName(std::string name){ data_component_name = name; }



    //Other--------------------------------------------------------------------




    /**
    Load interface from xml
    */
    AVoid LoadInterface(boost::property_tree::ptree base_index);
    /**
    Debug procedure
    */
    AVoid Debug();

    /**
    Cleaning procedure
    */
    AVoid Clean();

    /**
    Provide xml-saving function
    */
    boost::property_tree::ptree Save();



    /**
    Basic destructor
    */
    inline ~AData(){Clean();}




};




#endif
