#ifndef CONSOLE_UI_HPP
#define CONSOLE_UI_HPP




#include <stdafx.h>




class UIConsole : public AUIWindow
{




    /**
    callback for running script
    */
    ABoolean RunScript(const CEGUI::EventArgs &args);





public:



    /**
    Initializes console
    */
    AVoid Init();


    /**
    Cleans data
    */
    AVoid Clean();



    /**
    Console actions
    */
    AVoid Enable();



};





#endif
