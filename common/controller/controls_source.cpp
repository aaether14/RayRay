#include <stdafx.h>







GLFWwindow*ControllerSource::window = 0;
boost::shared_ptr<AData> ControllerSource::controller_data;
AUInt ControllerSource::keys[] = { 0 };
AUInt ControllerSource::mouse_buttons[] = { 0 };
std::vector<std::string> ControllerSource::drop_files;








ABoolean ControllerSource::CreateWindowContext(AUInt window_width, AUInt window_height,
                                               ABoolean fullscreen,
                                               std::string title,
                                               AUInt opengl_major_version,
                                               AUInt opengl_minor_version)
{






    if (!glfwInit())
    {
        std::cerr<<"Failed to initialize GLFW!"<<std::endl;
        return false;
    }




    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, opengl_major_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, opengl_minor_version);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);






    controller_data->Set("window_width", window_width);
    controller_data->Set("window_height", window_height);
    controller_data->Set("opengl_major_version", opengl_major_version);
    controller_data->Set("opengl_minor_version", opengl_minor_version);
    controller_data->Set("title", title);







    ControllerSource::window = glfwCreateWindow(window_width, window_height,
                                                title.c_str(), (fullscreen == true) ? glfwGetPrimaryMonitor() : NULL, NULL);
    if (!ControllerSource::window)
    {
        std::cerr<<"Failed to open GLFW window!"<<std::endl;
        glfwTerminate();
        return false;
    }







    glfwMakeContextCurrent(ControllerSource::window);
    glfwSwapInterval(1);
    glewExperimental = true;






    if (glewInit() != GLEW_OK) {
        std::cerr<<"Failed to initialize GLEW!"<<std::endl;
        return false;
    }



    ControllerSource::InitCallbacks();
    return true;



}




AVoid ControllerSource::Init()
{





    srand(time(NULL));
    controller_data.reset(new AData);
    fps.reset(new FPS);



    controller_data->Set("IsTyping", 0);
    controller_data->Set("mouseOverRoot", 0);
    controller_data->Set("mouse_position", glm::vec2(0.0f));





}




AVoid ControllerSource::InitCallbacks()
{


    glfwSetKeyCallback(ControllerSource::window, ControllerSource::key_callback);
    glfwSetCharCallback(ControllerSource::window, ControllerSource::char_callback);
    glfwSetMouseButtonCallback(ControllerSource::window, ControllerSource::mouse_callback);
    glfwSetCursorPosCallback(ControllerSource::window, ControllerSource::cursor_callback);
    glfwSetWindowSizeCallback(ControllerSource::window, ControllerSource::resize_callback);
    glfwSetScrollCallback(ControllerSource::window, ControllerSource::scroll_callback);
    glfwSetDropCallback(ControllerSource::window, ControllerSource::drop_callback);


}




AVoid ControllerSource::Clean()
{


    glfwDestroyWindow(window);
    glfwTerminate();
    controller_data.reset();


}








AVoid ControllerSource::Enable()
{


    fps->Compute();



}









ABoolean ControllerSource::GetKeyOnce(AUInt code)
{
    ABoolean result = keys[code] == GLFW_PRESS;
    if (result)keys[code] = GLFW_REPEAT;
    return result && !controller_data->Get<AInt>("IsTyping");
}







ABoolean ControllerSource::GetKey(AUInt code)
{

    return keys[code] > 0 && !controller_data->Get<AInt>("IsTyping");

}





ABoolean ControllerSource::GetMouseButton(AUInt code)
{

    return mouse_buttons[code] > 0;

}





ABoolean ControllerSource::GetMouseButtonOnce(AUInt code)
{

    AUInt result = mouse_buttons[code] == GLFW_PRESS;
    if (result)mouse_buttons[code] = GLFW_REPEAT;
    return result;

}







AVoid ControllerSource::key_callback(GLFWwindow* window, AInt key, AInt scancode, AInt action, AInt mods)
{



    CEGUI::Key::Scan ceguiKey = UI_UTIL::GlfwToCeguiKey(key);
    CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();


    if (action > 0)
    {
        if (!context.injectKeyDown(ceguiKey))
            keys[key]++;
    }
    else if (action == GLFW_RELEASE)
    {
        if (!context.injectKeyUp(ceguiKey))
            keys[key] = action;
    }





}





AVoid ControllerSource::char_callback(GLFWwindow * window, AUInt code)
{


    CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
    if (context.injectChar(code))
    {
    }


}






AVoid ControllerSource::mouse_callback(GLFWwindow* window, AInt button, AInt action, AInt mods)
{


    CEGUI::MouseButton ceguiMouseButton = UI_UTIL::GlfwToCeguiMouseButton(button);
    CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();



    if (action > 0)
    {
        if (!context.injectMouseButtonDown(ceguiMouseButton) || controller_data->Get<AInt>("mouseOverRoot"))
            mouse_buttons[button]++;
    }
    else if (action == GLFW_RELEASE)
    {
        if (!context.injectMouseButtonUp(ceguiMouseButton) || controller_data->Get<AInt>("mouseOverRoot"))
            mouse_buttons[button] = action;
    }



}





AVoid ControllerSource::cursor_callback(GLFWwindow* window, ADouble x, ADouble y)
{


    controller_data->Set("mouse_position", glm::vec2(x, y));


    CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
    context.injectMousePosition(AFloat(x), AFloat(y));



}








AVoid ControllerSource::resize_callback(GLFWwindow* window, AInt width, AInt height)
{

    glViewport(0, 0, width, height);
    controller_data->Set("window_width", width);
    controller_data->Set("window_height", height);

}




AVoid ControllerSource::scroll_callback(GLFWwindow* window, ADouble xoffset, ADouble yoffset)
{

    controller_data->Set("wheel_offset", yoffset);

}








AVoid ControllerSource::drop_callback(GLFWwindow* window, AInt count, const GLchar ** paths)
{

    for (AUInt i = 0; i < count; i++)
        drop_files.push_back(paths[i]);

}
