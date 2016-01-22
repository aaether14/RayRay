#include <stdafx.h>




AVoid UIConsole::Init()
{



    Load("console.layout");



    GetWindow()->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,
                                CEGUI::Event::Subscriber(&AUIWindow::CloseWindow, (AUIWindow*)this));

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
