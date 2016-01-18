#include <stdafx.h>




AVoid UIConsole::Init()
{


    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(wmgr.loadLayoutFromFile("console.layout"));




    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("Console/Button")->subscribeEvent(CEGUI::MenuItem::EventClicked,
            CEGUI::Event::Subscriber(&UIConsole::RunScript, this));




}







AVoid UIConsole::Clean()
{


    CleanModule();


}





AVoid UIConsole::Enable()
{





}
