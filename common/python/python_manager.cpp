#include <stdafx.h>





using namespace boost::python;

class World
{
public:
    void set(std::string msg) { this->msg = msg; }
    void greet() {  std::cout<<msg<<std::endl; }
    std::string msg;
};



BOOST_PYTHON_MODULE(hello)
{
    class_<World>("World")
            .def("greet", &World::greet)
            .def("set", &World::set)
            ;
}



void PythonManager::Init()
{


    Py_Initialize();

    try
    {

        inithello();
        std::string py_source = AString::LoadFileToString("data/python_scripts/test.py");
        PyRun_SimpleString(py_source.c_str());



    } catch (error_already_set)
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

