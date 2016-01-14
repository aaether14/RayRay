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
    void Init();
    /**
     Cleaning up
     */
    void Clean();
    /**
     Matching interface
     */
    void Enable();




};




#endif
