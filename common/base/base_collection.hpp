#ifndef BASE_COLLECTION_HPP
#define BASE_COLLECTION_HPP



#include <stdafx.h>





/**
Collection interface
*/
class ACollection
{


public:



    virtual bool InCollection(std::string name) = 0;



    /**
    get an available name
    */
    std::string GetAvailableName(std::string initial_name)
    {



        if (!InCollection(initial_name))
            return initial_name;
        else
        {
            GLuint number_sufix = 2;
            while (InCollection(initial_name + std::to_string(number_sufix)))
                number_sufix++;

            return initial_name + std::to_string(number_sufix);

        }



    }



};







#endif
