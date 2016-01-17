#ifndef STRING_HELPER_HPP
#define STRING_HELPER_HPP



#include <stdafx.h>





/**
Useful functions regarding strings
*/
namespace AString
{


/**
    Load a file to a string
    */
boost::optional<std::string> LoadFileToString(std::string path);
/**
    Gives the posibility to recursive load files through directives
    */
std::string ManageDirective(std::string path, std::string code, std::string first_delimiter, std::string second_delimiter);





/**
    Generate float array from string
    */
void FloatArrayFromString(GLfloat * _array, GLint &number_of_floats, std::string str);



/**
    Gets 2d vector from string
    */
glm::vec2 GetVec2FromString(std::string str);
/**
    Gets string from 2d vector
    */
std::string GetStringFromVec2(glm::vec2 v);



/**
    Gets 3d vector from string
    */
glm::vec3 GetVec3FromString(std::string str);
/**
    Gets string from 3d vector
    */
std::string GetStringFromVec3(glm::vec3 v);


/**
    Gets 4d vector from string
    */
glm::vec4 GetVec4FromString(std::string str);
/**
    Gets string from 4d vector
    */
std::string GetStringFromVec4(glm::vec4 v);



/**
    Gets mat4x4 from string
    */
glm::mat4 GetMat4FromString(std::string str);
/**
    Gets string from mat4
    */
std::string GetStringFromMat4(glm::mat4 v);






}




#endif
