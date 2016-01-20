#ifndef UI_MANAGER
#define UI_MANAGER




#include <stdafx.h>




/**


CEGUI initialisation


*/
class UIManager : public AUIWindow
{





    /**
    callback for when typing window gets activated
    */
    ABoolean onTypingWindowActivated(const CEGUI::EventArgs &args);
    /**
    callback for when typing window gets deactivated
    */
    ABoolean onTypingWindowDeactivated(const CEGUI::EventArgs &args);








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
