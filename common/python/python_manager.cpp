#include <stdafx.h>







void PythonManager::Init()
{


    Py_Initialize();

    try
    {

        GLM_Wrapper::Init();
        boost::python::object main_module = boost::python::import("__main__");
        boost::python::object main_namespace = main_module.attr("__dict__");
        boost::python::scope main_scope(main_module);
        boost::python::def("print_vec2", &AString::print_vec2);
        boost::python::def("print_vec3", &AString::print_vec3);
        boost::python::object ignored = exec_file("data/python_scripts/test.py", main_namespace);



    }
    catch (boost::python::error_already_set)
    {
        PyErr_Print();
    }

    Py_Finalize();


}





void PythonManager::Clean()
{



    CleanModule();


}





void PythonManager::Enable()
{




}

