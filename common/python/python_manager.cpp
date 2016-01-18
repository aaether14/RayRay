#include <stdafx.h>







AVoid PythonManager::Init()
{


    Py_Initialize();

    try
    {


        // initializing modules
        GLM_Wrapper::Init();
        Controller_Wrapper::Init();


        //declaring namespace
        main_module = boost::python::import("__main__");
        main_namespace = main_module.attr("__dict__");


        //running base script
        boost::python::exec_file("data/base.py", main_namespace);


        //passing instances
        main_namespace["setupController"](boost::python::ptr(static_cast<Controller*>(GetManager()->Get("Controller"))));



    }
    catch (boost::python::error_already_set)
    {
        PyErr_Print();
    }



}





AVoid PythonManager::Clean()
{


    Py_Finalize();
    CleanModule();


}





AVoid PythonManager::Enable()
{


    try
    {

        boost::python::exec_file("data/python_scripts/test.py", main_namespace);

    }
    catch (boost::python::error_already_set)
    {
        PyErr_Print();
    }



}

