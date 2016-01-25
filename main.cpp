#include <stdafx.h>







AInt main(AInt argc, AChar *argv[])
{



    Py_Initialize();




    try
    {


        GLM_Wrapper::Init();
        Controller_Wrapper::Init();
        Application*app = new Application();
        app->Enable();
        delete app;


    }
    catch(boost::python::error_already_set)
    {
        PyErr_Print();
    }




    Py_Finalize();





    return 0;



}
