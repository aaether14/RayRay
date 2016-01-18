#include <stdafx.h>





AUInt ControllerSource::keys[] = { 0 };



AUInt ControllerSource::fullscreen_key = 0;
ABoolean ControllerSource::fullscreen = false;

AInt ControllerSource::window_width = 0;
AInt ControllerSource::window_height = 0;
std::string ControllerSource::title = "";


AUInt ControllerSource::opengl_major_version = 0;
AUInt ControllerSource::opengl_minor_version = 0;
GLFWwindow*ControllerSource::window = 0;



glm::vec2 ControllerSource::mouse_position = glm::vec2(0.0f, 0.0f);
AUInt ControllerSource::mouse_buttons[] = { 0 };
ADouble ControllerSource::wheel_offset = 0.0;
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
		return -1;
	}




	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, opengl_major_version);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, opengl_minor_version);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	ControllerSource::window_width = window_width;
	ControllerSource::window_height = window_height;
	ControllerSource::fullscreen = fullscreen;
	ControllerSource::opengl_major_version = opengl_major_version;
	ControllerSource::opengl_minor_version = opengl_minor_version;
	ControllerSource::title = title;







	ControllerSource::window = glfwCreateWindow(window_width, window_height,
		title.c_str(), (fullscreen == true) ? glfwGetPrimaryMonitor() : NULL, NULL);
	if (!ControllerSource::window){
		std::cerr<<"Failed to open GLFW window!"<<std::endl;
		glfwTerminate();
		return -1;
	}







	glfwMakeContextCurrent(ControllerSource::window);
	glfwSwapInterval(1);
	glewExperimental = true;






	if (glewInit() != GLEW_OK) {
		std::cerr<<"Failed to initialize GLEW!"<<std::endl;
		return -1;
	}
	ControllerSource::InitCallbacks();
	return 1;

	

}




AVoid ControllerSource::Init()
{



	srand(time(NULL));
    fps.reset(new FPS);




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


}








AVoid ControllerSource::Enable()
{



	fps->FirstPass();
	fps->Compute();




}



AVoid FPS::FirstPass()
{



    ADouble currentTime = glfwGetTime();
    deltaTime = returnable_deltaTime = AFloat(currentTime - lastTime2);
	lastTime2 = glfwGetTime();



}



AVoid FPS::Compute(){



	frames++;
    ADouble currentTime = glfwGetTime();
    deltaTime = AFloat(currentTime - lastTime);


	if (deltaTime > 1.0f)
	{

        fps = AFloat(frames) / deltaTime;
		lastTime = currentTime;
		frames = 0;
		lastTime = currentTime;

	}



}





AVoid ControllerSource::key_callback(GLFWwindow* window, AInt key, AInt scancode, AInt action, AInt mods)
{



	CEGUI::Key::Scan ceguiKey = UI_UTIL::GlfwToCeguiKey(key);
	CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();


	if (action > 0)
    {
		keys[key]++;
		context.injectKeyDown(ceguiKey);
	}
	else if (action == GLFW_RELEASE)
	{
		keys[key] = 0;
		context.injectKeyUp(ceguiKey);
	}





}





AVoid ControllerSource::char_callback(GLFWwindow * window, AUInt code)
{


	CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
	if (context.injectChar(code))
    {
        keys[code + 'A' - 'a'] = 0;
        keys[code] = 0;
	}


}






AVoid ControllerSource::mouse_callback(GLFWwindow* window, AInt button, AInt action, AInt mods)
{


	CEGUI::MouseButton ceguiMouseButton = UI_UTIL::GlfwToCeguiMouseButton(button);
	CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();



	if (action > 0)
	{
		mouse_buttons[button]++;
		context.injectMouseButtonDown(ceguiMouseButton);
	}
	else if (action == GLFW_RELEASE)
	{
		mouse_buttons[button] = 0;
		context.injectMouseButtonUp(ceguiMouseButton);
	}



}





AVoid ControllerSource::cursor_callback(GLFWwindow* window, ADouble x, ADouble y)
{


	ControllerSource::mouse_position = glm::vec2(x, y);


	CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
    context.injectMousePosition(AFloat(x), AFloat(y));



}








AVoid ControllerSource::resize_callback(GLFWwindow* window, AInt width, AInt height)
{

	glViewport(0, 0, width, height);
	ControllerSource::window_width = width;
	ControllerSource::window_height = height;

}




AVoid ControllerSource::scroll_callback(GLFWwindow* window, ADouble xoffset, ADouble yoffset)
{

	wheel_offset = yoffset;

}








AVoid ControllerSource::drop_callback(GLFWwindow* window, AInt count, const GLchar ** paths)
{

    for (AUInt i = 0; i < count; i++)
		drop_files.push_back(paths[i]);

}
