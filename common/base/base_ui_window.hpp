#ifndef BASE_UI_WINDOW_HPP
#define BASE_UI_WINDOW_HPP



#include <stdafx.h>




/**
Interface for ui windows
*/
class AUIWindow : public AModule
{


    CEGUI::Window *window;



public:



    /**
     Get window
     */
    inline CEGUI::Window *GetWindow(){return window; }
    /**
     Set window
     */
    inline AVoid SetWindow(CEGUI::Window *new_window){window = new_window; }
    /**
     Load window from layout
     */
    inline AVoid Load(std::string layout_path){ window = CEGUI::WindowManager::getSingleton().loadLayoutFromFile(layout_path); }
    /**
    Override add function
    */
    virtual AVoid Add(std::string key, AModule * module) override;





};






#endif
