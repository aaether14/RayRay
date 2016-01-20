#ifndef CONSOLE_UI_HPP
#define CONSOLE_UI_HPP




#include <stdafx.h>




class UIConsole : public AUIWindow
{




    inline ABoolean RunScript(const CEGUI::EventArgs &args)
    {
        static_cast<PythonManager*>(GetManager()->Get("Python"))->RunScriptFromString(
                    static_cast<CEGUI::MultiLineEditbox*>(GetWindow()->getChild("Source"))->getText().c_str());
        static_cast<CEGUI::MultiLineEditbox*>(GetWindow()->getChild("Source"))->setText("");
        return true;
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
