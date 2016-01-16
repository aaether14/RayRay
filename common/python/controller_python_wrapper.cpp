#include <stdafx.h>




BOOST_PYTHON_MODULE(Controller)
{




    boost::python::class_<FPS>("FPS")
            .def("Get", &FPS::Get)
            .def("Delta", &FPS::Delta);




    boost::python::class_<Controller>("Controller")
            .def("GetKey", &Controller::GetKey)
            .def("GetKeyOnce", &Controller::GetKeyOnce)
            .def("GetMouseButton", &Controller::GetMouseButton)
            .def("GetMouseButtonOnce", &Controller::GetMouseButtonOnce)
            .def("GetMousePosition", &Controller::GetMousePosition)
            .def("GetWindowTitle", &Controller::GetWindowTitle)
            .def("SetWindowTitle", &Controller::SetWindowTitle)
            .def("GetFPS", &Controller::GetFPSCounter, boost::python::return_value_policy<boost::python::reference_existing_object>());



}






namespace Controller_Wrapper
{










void Init()
{

    initController();

}






}
