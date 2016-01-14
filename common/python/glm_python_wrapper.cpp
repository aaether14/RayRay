#include <stdafx.h>




BOOST_PYTHON_MODULE(GLM)
{




    boost::python::class_<glm::vec2>("vec2")
            .def(boost::python::init<float>())
            .def(boost::python::init<float, float>())
            .def("__str__", &AString::GetStringFromVec2)
            .def("__div__", &GLM_Wrapper::Operators::Div<glm::vec2, float>)
            .def("__div__", &GLM_Wrapper::Operators::Div<glm::vec2, glm::vec2>)
            .def("__mul__", &GLM_Wrapper::Operators::Mult<glm::vec2, float>)
            .def("__mul__", &GLM_Wrapper::Operators::Mult<glm::vec2, glm::vec2>)
            .def("__add__", &GLM_Wrapper::Operators::Add<glm::vec2, float>)
            .def("__add__", &GLM_Wrapper::Operators::Add<glm::vec2, glm::vec2>)
            .def("__sub__", &GLM_Wrapper::Operators::Sub<glm::vec2, float>)
            .def("__sub__", &GLM_Wrapper::Operators::Sub<glm::vec2, glm::vec2>)
            .def_readwrite("x", &glm::vec2::x)
            .def_readwrite("y", &glm::vec2::y)
            ;





    boost::python::class_<glm::vec3>("vec3")
            .def(boost::python::init<float>())
            .def(boost::python::init<float, float, float>())
            .def("__str__", &AString::GetStringFromVec3)
            .def("__div__", &GLM_Wrapper::Operators::Div<glm::vec3, float>)
            .def("__div__", &GLM_Wrapper::Operators::Div<glm::vec3, glm::vec3>)
            .def("__mul__", &GLM_Wrapper::Operators::Mult<glm::vec3, float>)
            .def("__mul__", &GLM_Wrapper::Operators::Mult<glm::vec3, glm::vec3>)
            .def("__add__", &GLM_Wrapper::Operators::Add<glm::vec3, float>)
            .def("__add__", &GLM_Wrapper::Operators::Add<glm::vec3, glm::vec3>)
            .def("__sub__", &GLM_Wrapper::Operators::Sub<glm::vec3, float>)
            .def("__sub__", &GLM_Wrapper::Operators::Sub<glm::vec3, glm::vec3>)
            .def_readwrite("x", &glm::vec3::x)
            .def_readwrite("y", &glm::vec3::y)
            .def_readwrite("z", &glm::vec3::z)
            ;




    boost::python::class_<glm::vec4>("vec4")
            .def(boost::python::init<float>())
            .def(boost::python::init<float, float, float, float>())
            .def("__str__", &AString::GetStringFromVec4)
            .def("__div__", &GLM_Wrapper::Operators::Div<glm::vec4, float>)
            .def("__div__", &GLM_Wrapper::Operators::Div<glm::vec4, glm::vec4>)
            .def("__mul__", &GLM_Wrapper::Operators::Mult<glm::vec4, float>)
            .def("__mul__", &GLM_Wrapper::Operators::Mult<glm::vec4, glm::vec4>)
            .def("__add__", &GLM_Wrapper::Operators::Add<glm::vec4, float>)
            .def("__add__", &GLM_Wrapper::Operators::Add<glm::vec4, glm::vec4>)
            .def("__sub__", &GLM_Wrapper::Operators::Sub<glm::vec4, float>)
            .def("__sub__", &GLM_Wrapper::Operators::Sub<glm::vec4, glm::vec4>)
            .def_readwrite("x", &glm::vec4::x)
            .def_readwrite("y", &glm::vec4::y)
            .def_readwrite("z", &glm::vec4::z)
            .def_readwrite("w", &glm::vec4::w)
            ;




    boost::python::class_<glm::mat4>("mat4")
            .def(boost::python::init<float>())
            .def(boost::python::init<glm::vec4, glm::vec4, glm::vec4, glm::vec4>())
            .def("__str__", &AString::GetStringFromMat4)
            .def("__div__", &GLM_Wrapper::Operators::Div<glm::mat4, float>)
            .def("__div__", &GLM_Wrapper::Operators::Div<glm::mat4, glm::mat4>)
            .def("__mul__", &GLM_Wrapper::Operators::Mult<glm::mat4, float>)
            .def("__mul__", &GLM_Wrapper::Operators::Mult<glm::mat4, glm::mat4>)
            .def("__add__", &GLM_Wrapper::Operators::Add<glm::mat4, float>)
            .def("__add__", &GLM_Wrapper::Operators::Add<glm::mat4, glm::mat4>)
            .def("__sub__", &GLM_Wrapper::Operators::Sub<glm::mat4, float>)
            .def("__sub__", &GLM_Wrapper::Operators::Sub<glm::mat4, glm::mat4>)
            ;




}




void GLM_Wrapper::Init()
{

    initGLM();

}
