#ifndef UI_MANAGER
#define UI_MANAGER




#include <stdafx.h>




/**


CEGUI initialisation


*/
class UIManager : public AUIWindow
{



    inline ABoolean onWindowActivated(const CEGUI::EventArgs &args)
    {
        const CEGUI::WindowEventArgs& window_args = static_cast<const CEGUI::WindowEventArgs&>(args);
        std::cout<<window_args.window->getName()<<std::endl;
        return true;
    }




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
