#include <stdafx.h>




AVoid UIConsole::Init()
{



    Load("console.layout");



    GetWindow()->getChild("Button")->subscribeEvent(CEGUI::MenuItem::EventClicked,
            CEGUI::Event::Subscriber(&UIConsole::RunScript, this));




}







AVoid UIConsole::Clean()
{


    CleanModule();


}





AVoid UIConsole::Enable()
{





}
