#include <stdafx.h>




BOOST_PYTHON_MODULE(Controller)
{


    boost::python::def("GetKey", &ControllerSource::GetKey);



}






namespace Controller_Wrapper
{










void Init()
{

   initController();

}






}
