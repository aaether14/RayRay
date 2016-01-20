#ifndef CONSOLE_UI_HPP
#define CONSOLE_UI_HPP




#include <stdafx.h>




class UIConsole : public AUIWindow
{




    inline ABoolean RunScript(const CEGUI::EventArgs &args)
    {
        static_cast<PythonManager*>(GetManager()->Get("Python"))->Enable();
        return 1;
    }





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
