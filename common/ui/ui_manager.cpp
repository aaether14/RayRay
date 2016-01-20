#include <stdafx.h>




AVoid UIManager::Init()
{


    //Initialising renderer


    CEGUI::OpenGL3Renderer& renderer = CEGUI::OpenGL3Renderer::bootstrapSystem();



    CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>
            (CEGUI::System::getSingleton().getResourceProvider());


    //Managing resource directories


    rp->setResourceGroupDirectory("schemes", "data/ui/schemes/");
    rp->setResourceGroupDirectory("imagesets", "data/ui/imagesets/");
    rp->setResourceGroupDirectory("fonts", "data/ui/fonts/");
    rp->setResourceGroupDirectory("layouts", "data/ui/layouts/");
    rp->setResourceGroupDirectory("looknfeels", "data/ui/looknfeel/");
    rp->setResourceGroupDirectory("lua_scripts", "data/ui/lua_scripts/");
    rp->setResourceGroupDirectory("schemas", "data/ui/xml_schemas/");


    CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
    CEGUI::Font::setDefaultResourceGroup("fonts");
    CEGUI::Scheme::setDefaultResourceGroup("schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
    CEGUI::WindowManager::setDefaultResourceGroup("layouts");
    CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
    CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();
    if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
        parser->setProperty("SchemaDefaultResourceGroup", "schemas");



    //Adding skins



    CEGUI::SchemeManager::getSingleton().createFromFile("GlossySerpent.scheme");
    CEGUI::SchemeManager::getSingleton().createFromFile("GlossySerpentFHD.scheme");
    CEGUI::SchemeManager::getSingleton().createFromFile("VanillaSkin.scheme");
    CEGUI::SchemeManager::getSingleton().createFromFile("VanillaCommonDialogs.scheme");
    CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
    CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-10.font");



    CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont("DejaVuSans-10");
    CEGUI::System::getSingleton().getDefaultGUIContext().
            getMouseCursor().setDefaultImage("GlossySerpentFHDCursors/MouseArrow");




    initialiseCEGUICommonDialogs();





    Load("ui.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(GetWindow());




    CEGUI::GlobalEventSet::getSingleton().subscribeEvent(CEGUI::Window::EventNamespace + "/" + CEGUI::Window::EventDeactivated,
                                                         CEGUI::Event::Subscriber(&UIWorkStation::onTypingWindowDeactivated, this));



    CEGUI::GlobalEventSet::getSingleton().subscribeEvent(CEGUI::Window::EventNamespace + "/" + CEGUI::Window::EventActivated,
                                                         CEGUI::Event::Subscriber(&UIWorkStation::onTypingWindowActivated, this));






}



AVoid UIManager::Clean()
{




}




AVoid UIManager::Enable()
{


    ControllerSource * ctrl = static_cast<ControllerSource*>(GetManager()->Get("Controller"));





    CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
    context.injectTimePulse(ctrl->GetFPSCounter()->Delta());
    CEGUI::System::getSingleton().injectTimePulse(ctrl->GetFPSCounter()->Delta());






    glActiveTexture(GL_TEXTURE0);
    glDisable(GL_DEPTH_TEST);
    CEGUI::System::getSingleton().renderAllGUIContexts();
    glDisable(GL_BLEND);
    glDisable(GL_SCISSOR_TEST);
    glEnable(GL_DEPTH_TEST);




}






ABoolean UIManager::onTypingWindowActivated(const CEGUI::EventArgs &args)
{
    const CEGUI::WindowEventArgs& window_args = static_cast<const CEGUI::WindowEventArgs&>(args);
    std::string window_type = window_args.window->getType().c_str();
    window_type = window_type.substr(window_type.find_last_of("/") + 1);
     if (!window_type.compare("MultiLineEditbox") || !window_type.compare("Editbox") || !window_type.compare("Spinner"))
    {
        ControllerSource * ctrl = static_cast<ControllerSource*>(GetManager()->Get("Controller"));
        ctrl->GetControllerData()->SetInt("IsTyping", ctrl->GetControllerData()->GetInt("IsTyping") + 1);
    }
    return true;
}







ABoolean UIManager::onTypingWindowDeactivated(const CEGUI::EventArgs &args)
{
    const CEGUI::WindowEventArgs& window_args = static_cast<const CEGUI::WindowEventArgs&>(args);
    std::string window_type = window_args.window->getType().c_str();
    window_type = window_type.substr(window_type.find_last_of("/") + 1);
    if (!window_type.compare("MultiLineEditbox") || !window_type.compare("Editbox") || !window_type.compare("Spinner"))
    {
        ControllerSource * ctrl = static_cast<ControllerSource*>(GetManager()->Get("Controller"));
        ctrl->GetControllerData()->SetInt("IsTyping", ctrl->GetControllerData()->GetInt("IsTyping") - 1);
    }
    return true;
}





















