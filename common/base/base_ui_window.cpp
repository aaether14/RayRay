#include <stdafx.h>




AVoid AUIWindow::Add(std::string key, AModule * module)
{


    AModule::Add(key, module);
    GetWindow()->addChild(static_cast<AUIWindow*>(module)->GetWindow());


}






AVoid AUIWindow::DeactivateRecursively()
{


    std::pair<std::string, boost::shared_ptr<AModule> > window_iterator;
    BOOST_FOREACH(window_iterator, *GetModuleMapPointer())
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

