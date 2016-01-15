#include <stdafx.h>




BOOST_PYTHON_MODULE(Controller)
{


        boost::python::class_<Controller>("Controller")
                .def("GetKey", &Controller::GetKey)
                .def("GetKeyOnce", &Controller::GetKeyOnce)
                .def("GetWindowTitle", &Controller::GetWindowTitle);



}






namespace Controller_Wrapper
{










void Init()
{

   initController();

}






}
