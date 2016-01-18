#include <stdafx.h>




AVoid UIConsole::Init()
{


    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(wmgr.loadLayoutFromFile("console.layout"));


}







AVoid UIConsole::Clean()
{


    CleanModule();


}





AVoid UIConsole::Enable()
{





}
