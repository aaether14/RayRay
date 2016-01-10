#ifndef PYTHON_MANAGER_HPP
#define PYTHON_MANAGER_HPP



#include <stdafx.h>




/**
Wrapper for python interpreter
*/
class PythonManager : public AModule
{


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
