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
    CEGUI::SchemeManager::getSingleton().createFromFile("GWEN.scheme");
    CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-10.font");



    CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont("DejaVuSans-10");
    CEGUI::System::getSingleton().getDefaultGUIContext().
            getMouseCursor().setDefaultImage("GlossySerpentFHDCursors/MouseArrow");



    CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultTooltipType("GlossySerpentFHD/Tooltip");
    CEGUI::System::getSingleton().getDefaultGUIContext().getDefaultTooltipObject()->setHoverTime(1.5f);




    initialiseCEGUICommonDialogs();





    Load("ui.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(GetWindow());




    CEGUI::GlobalEventSet::getSingleton().subscribeEvent(CEGUI::Window::EventNamespace + "/" + CEGUI::Window::EventDeactivated,
                                                         CEGUI::Event::Subscriber(&UIWorkStation::onTypingWindowDeactivated, this));



    CEGUI::GlobalEventSet::getSingleton().subscribeEvent(CEGUI::Window::EventNamespace + "/" + CEGUI::Window::EventActivated,
                                                         CEGUI::Event::Subscriber(&UIWorkStation::onTypingWindowActivated, this));



    GetWindow()->subscribeEvent(CEGUI::Window::EventMouseButtonDown,
                                CEGUI::Event::Subscriber(&UIManager::onClick, this));


    GetWindow()->subscribeEvent(CEGUI::Window::EventMouseEntersSurface,
                                CEGUI::Event::Subscriber(&UIManager::onEnterSurface, this));


    GetWindow()->subscribeEvent(CEGUI::Window::EventMouseLeavesSurface,
                                CEGUI::Event::Subscriber(&UIManager::onLeaveSurface, this));






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
        ctrl->GetControllerData()->Set("IsTyping", ctrl->GetControllerData()->Get<AInt>("IsTyping") + 1);
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
        ctrl->GetControllerData()->Set("IsTyping", ctrl->GetControllerData()->Get<AInt>("IsTyping") - 1);
    }
    return true;



}








ABoolean UIManager::onClick(const CEGUI::EventArgs &args)
{


    DeactivateRecursively();
    return true;


}









ABoolean UIManager::onEnterSurface(const CEGUI::EventArgs &args)
{


    ControllerSource * ctrl = static_cast<ControllerSource*>(GetManager()->Get("Controller"));
    ctrl->GetControllerData()->Set("mouseOverRoot", 1);
    return true;


}






ABoolean UIManager::onLeaveSurface(const CEGUI::EventArgs &args)
{


    ControllerSource * ctrl = static_cast<ControllerSource*>(GetManager()->Get("Controller"));
    ctrl->GetControllerData()->Set("mouseOverRoot", 0);
    return true;


}









