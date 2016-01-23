#ifndef GLM_PYTHON_WRAPPER_HPP
#define GLM_PYTHON_WRAPPER_HPP



#include <stdafx.h>




/**
Basic glm wrapper
*/
namespace GLM_Wrapper {



/**
glm operators
*/
namespace Operators
{

template<class T1, class T2>
T1 Div(const T1& v, T2 value)
{
    return v / value;
}

template<class T1, class T2>
T1 Mult(const T1& v, T2 value)
{
    return v * value;
}

template<class T1, class T2>
T1 Add(const T1& v, T2 value)
{
    return v + value;
}

template<class T1, class T2>
T1 Sub(const T1& v, T2 value)
{
    return v - value;
}


}



/**
  Module init
*/
AVoid Init();




}






#endif

