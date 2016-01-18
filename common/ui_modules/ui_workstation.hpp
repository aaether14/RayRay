#ifndef UI_WORKSTATION_HPP
#define UI_WORKSTATION_CPP




#include <stdafx.h>





class UIWorkStation : public UIManager
{



public:



    /**
    Initializes CEGUI
    */
    AVoid Init();


    /**
    Cleans data
    */
    AVoid Clean();



    /**
    Renders UI to scene
    */
    AVoid Enable();




};





#endif
