#include <stdafx.h>




AVoid AUIWindow::Add(std::string key, AModule * module)
{


    AModule::Add(key, module);
    GetWindow()->addChild(static_cast<AUIWindow*>(module)->GetWindow());


}






AVoid AUIWindow::DeactivateRecursively()
{



    BOOST_FOREACH(auto window_iterator, *GetModuleMapPointer())
    {
        if (dynamic_cast<AUIWindow*>(window_iterator.second.get()))
            static_cast<AUIWindow*>(window_iterator.second.get())->DeactivateRecursively();
    }
    GetWindow()->deactivate();



}







ABoolean AUIWindow::CloseWindow(const CEGUI::EventArgs &args)
{

    GetWindow()->hide();
    return true;

}

