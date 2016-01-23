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
    Generate AFloat array from string
    */
AVoid FloatArrayFromString(AFloat * _array, AInt &number_of_floats, std::string str);




/**
template function for loading float array from string
*/
template <class T>
T GetFloatArrayFromString(std::string str);


/**
template function for writting float array as string
*/
template <class T>
std::string GetStringFromFloatArray(T float_array);






}




#endif
