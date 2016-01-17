#ifndef AAETHER_ERROR_HPP
#define AAETHER_ERROR_HPP




#include <stdafx.h>




/**
Error handling functionality
*/
class AError : public std::runtime_error
{
public:
    AError(const std::string& msg) :
        std::runtime_error(msg)
    {
    }
};





#endif
