#include <stdafx.h>







void PythonManager::Init()
{


    Py_Initialize();

    try
    {
        GLM_Wrapper::Init();
        Controller_Wrapper::Init();
        main_module = boost::python::import("__main__");
        main_namespace = main_module.attr("__dict__");
    }
    catch (boost::python::error_already_set)
    {
        PyErr_Print();
    }



}





void PythonManager::Clean()
{


    Py_Finalize();
    CleanModule();


}





void PythonManager::Enable()
{


    try
    {

        boost::python::object ignored = exec_file("data/python_scripts/test.py", main_namespace);

    }
    catch (boost::python::error_already_set)
    {
        PyErr_Print();
    }



}

