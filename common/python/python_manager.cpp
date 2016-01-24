#include <stdafx.h>







AVoid PythonManager::Init()
{





    //declaring namespace
    main_namespace = boost::python::import("__main__").attr("__dict__");


    //running base script
    boost::python::exec_file(AAETHER_SYSTEM_FOLDER"base.py", main_namespace);


    //passing instances
    main_namespace["setupController"](boost::python::ptr(static_cast<Controller*>(GetManager()->Get("Controller"))));






}





AVoid PythonManager::Clean()
{


    CleanModule();


}





AVoid PythonManager::Enable()
{






}





AVoid PythonManager::RunScriptFromString(std::string script_string)
{


    try
    {

        boost::python::exec(script_string.c_str(), main_namespace);

    }
    catch (boost::python::error_already_set)
    {
        PyErr_Print();
    }



}









