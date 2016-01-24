#ifndef BASE_DATA_HPP
#define BASE_DATA_HPP





#include <stdafx.h>






/**
Provides functionality for engine data managment
*/
class AData
{


    boost::python::dict data_dictionary;



public:






    /**
    template method for extracting desired data
    */
    template <class T>
    T Get(std::string key);



    /**
    template method for setting desired data
    */
    template <class T>
    AVoid Set(std::string key, T value);




    /**
    Load interface from xml
    */
    AVoid LoadInterface(boost::property_tree::ptree base_index);
    /**
    Debug procedure
    */
    AVoid Debug();
    /**
    Provide xml-saving function
    */
    boost::property_tree::ptree Save();







};




#endif
