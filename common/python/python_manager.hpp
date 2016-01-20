#ifndef PYTHON_MANAGER_HPP
#define PYTHON_MANAGER_HPP



#include <stdafx.h>




/**
Wrapper for python interpreter
*/
class PythonManager : public AModule
{



    boost::python::object main_module;
    boost::python::object main_namespace;




public:



    /**
     Initialization
     */
    AVoid Init();
    /**
     Cleaning up
     */
    AVoid Clean();
    /**
     Matching interface
     */
    AVoid Enable();



    /**
    Run a certain script from a file
    */
    AVoid RunScriptFromString(std::string script_string);




};




#endif
