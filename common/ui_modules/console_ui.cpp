#include <stdafx.h>




AVoid UIConsole::Init()
{



    Load("console.layout");
    GetWindow()->hide();



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



    Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
    if (ctrl->GetKey(GLFW_KEY_LEFT_CONTROL) && ctrl->GetKey(GLFW_KEY_T))
        if(!GetWindow()->isVisible())
            GetWindow()->show();



}






ABoolean UIConsole::RunScript(const CEGUI::EventArgs &args)
{


    static_cast<PythonManager*>(GetManager()->Get("Python"))->RunScriptFromString(
                static_cast<CEGUI::MultiLineEditbox*>(GetWindow()->getChild("Source"))->getText().c_str());
    static_cast<CEGUI::MultiLineEditbox*>(GetWindow()->getChild("Source"))->setText("");
    return true;



}

















