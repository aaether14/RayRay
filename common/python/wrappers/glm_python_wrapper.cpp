#include <stdafx.h>




BOOST_PYTHON_MODULE(GLM)
{




    boost::python::class_<glm::vec2>("vec2")
            .def(boost::python::init<AFloat>())
            .def(boost::python::init<AFloat, AFloat>())
            .def("__str__", &AString::GetStringFromFloatArray<glm::vec2>)
            .def("__div__", &GLM_Wrapper::Operators::Div<glm::vec2, AFloat>)
            .def("__div__", &GLM_Wrapper::Operators::Div<glm::vec2, glm::vec2>)
            .def("__mul__", &GLM_Wrapper::Operators::Mult<glm::vec2, AFloat>)
            .def("__mul__", &GLM_Wrapper::Operators::Mult<glm::vec2, glm::vec2>)
            .def("__add__", &GLM_Wrapper::Operators::Add<glm::vec2, AFloat>)
            .def("__add__", &GLM_Wrapper::Operators::Add<glm::vec2, glm::vec2>)
            .def("__sub__", &GLM_Wrapper::Operators::Sub<glm::vec2, AFloat>)
            .def("__sub__", &GLM_Wrapper::Operators::Sub<glm::vec2, glm::vec2>)
            .def_readwrite("x", &glm::vec2::x)
            .def_readwrite("y", &glm::vec2::y)
            ;





    boost::python::class_<glm::vec3>("vec3")
            .def(boost::python::init<AFloat>())
            .def(boost::python::init<AFloat, AFloat, AFloat>())
            .def("__str__", &AString::GetStringFromFloatArray<glm::vec3>)
            .def("__div__", &GLM_Wrapper::Operators::Div<glm::vec3, AFloat>)
            .def("__div__", &GLM_Wrapper::Operators::Div<glm::vec3, glm::vec3>)
            .def("__mul__", &GLM_Wrapper::Operators::Mult<glm::vec3, AFloat>)
            .def("__mul__", &GLM_Wrapper::Operators::Mult<glm::vec3, glm::vec3>)
            .def("__add__", &GLM_Wrapper::Operators::Add<glm::vec3, AFloat>)
            .def("__add__", &GLM_Wrapper::Operators::Add<glm::vec3, glm::vec3>)
            .def("__sub__", &GLM_Wrapper::Operators::Sub<glm::vec3, AFloat>)
            .def("__sub__", &GLM_Wrapper::Operators::Sub<glm::vec3, glm::vec3>)
            .def_readwrite("x", &glm::vec3::x)
            .def_readwrite("y", &glm::vec3::y)
            .def_readwrite("z", &glm::vec3::z)
            ;




    boost::python::class_<glm::vec4>("vec4")
            .def(boost::python::init<AFloat>())
            .def(boost::python::init<AFloat, AFloat, AFloat, AFloat>())
            .def("__str__", &AString::GetStringFromFloatArray<glm::vec4>)
            .def("__div__", &GLM_Wrapper::Operators::Div<glm::vec4, AFloat>)
            .def("__div__", &GLM_Wrapper::Operators::Div<glm::vec4, glm::vec4>)
            .def("__mul__", &GLM_Wrapper::Operators::Mult<glm::vec4, AFloat>)
            .def("__mul__", &GLM_Wrapper::Operators::Mult<glm::vec4, glm::vec4>)
            .def("__add__", &GLM_Wrapper::Operators::Add<glm::vec4, AFloat>)
            .def("__add__", &GLM_Wrapper::Operators::Add<glm::vec4, glm::vec4>)
            .def("__sub__", &GLM_Wrapper::Operators::Sub<glm::vec4, AFloat>)
            .def("__sub__", &GLM_Wrapper::Operators::Sub<glm::vec4, glm::vec4>)
            .def_readwrite("x", &glm::vec4::x)
            .def_readwrite("y", &glm::vec4::y)
            .def_readwrite("z", &glm::vec4::z)
            .def_readwrite("w", &glm::vec4::w)
            ;




    boost::python::class_<std::vector<glm::vec4> >("vec4list")
           .def(boost::python::vector_indexing_suite<std::vector<glm::vec4> >())
       ;






    boost::python::class_<glm::mat4>("mat4")
            .def(boost::python::init<AFloat>())
            .def(boost::python::init<glm::vec4, glm::vec4, glm::vec4, glm::vec4>())
            .def("__str__", &AString::GetStringFromFloatArray<glm::mat4>)
            .def("__div__", &GLM_Wrapper::Operators::Div<glm::mat4, AFloat>)
            .def("__div__", &GLM_Wrapper::Operators::Div<glm::mat4, glm::mat4>)
            .def("__mul__", &GLM_Wrapper::Operators::Mult<glm::mat4, AFloat>)
            .def("__mul__", &GLM_Wrapper::Operators::Mult<glm::mat4, glm::mat4>)
            .def("__add__", &GLM_Wrapper::Operators::Add<glm::mat4, AFloat>)
            .def("__add__", &GLM_Wrapper::Operators::Add<glm::mat4, glm::mat4>)
            .def("__sub__", &GLM_Wrapper::Operators::Sub<glm::mat4, AFloat>)
            .def("__sub__", &GLM_Wrapper::Operators::Sub<glm::mat4, glm::mat4>)
            ;





    boost::python::def("perspective", &glm::perspective<AFloat>);
    boost::python::def("lookAt", &glm::lookAt<AFloat, glm::highp>);
    boost::python::def("GetFrustumPlanes", &Math::GetFrustumPlanes);






    glm::detail::tvec2<AFloat, glm::highp> (*vec2_normalize)(glm::detail::tvec2<AFloat, glm::highp> const &) = &glm::normalize;
    glm::detail::tvec3<AFloat, glm::highp> (*vec3_normalize)(glm::detail::tvec3<AFloat, glm::highp> const &) = &glm::normalize;
    glm::detail::tvec4<AFloat, glm::highp> (*vec4_normalize)(glm::detail::tvec4<AFloat, glm::highp> const &) = &glm::normalize;
    boost::python::def("normalize", vec2_normalize);
    boost::python::def("normalize", vec3_normalize);
    boost::python::def("normalize", vec4_normalize);




}




AVoid GLM_Wrapper::Init()
{

    initGLM();

}
