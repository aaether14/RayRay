#ifndef CONTROLS_SOURCE_HPP
#define CONTROLS_SOURCE_HPP




#include <stdafx.h>







/**
Base class for controller
Used to acces window and input
*/
class ControllerSource : public AModule
{




    static GLFWwindow* window;
    static boost::shared_ptr<AData> controller_data;
    boost::shared_ptr<FPS> fps;





    /**
    Callback to return key presses
    */
    static AVoid key_callback(GLFWwindow* window, AInt key, AInt scancode, AInt action, AInt mods);
    /**
    Callback to return key presses (ASCI information)
    */
    static AVoid char_callback(GLFWwindow * window, AUInt code);
    static AUInt keys[512];


    /**
    Mouse buttons press
    */
    static AVoid mouse_callback(GLFWwindow* window, AInt button, AInt action, AInt mods);
    static AUInt mouse_buttons[8];



    static std::vector<std::string> drop_files;
    /**
    Get list of files dropped on window
    */
    static AVoid drop_callback(GLFWwindow* window, AInt count, const GLchar ** paths);
    /**
    Cursor movement
    */
    static AVoid cursor_callback(GLFWwindow* window, ADouble x, ADouble y);
    /**
    Recives resize information
    */
    static AVoid resize_callback(GLFWwindow* window, AInt width, AInt height);
    /**
    Mouse wheel information
    */
    static AVoid scroll_callback(GLFWwindow* window, ADouble xoffset, ADouble yoffset);



    /**
    Initialize callbacks
    */
    static AVoid InitCallbacks();




public:







    /**
    Check if key with 'code' is being pressed
    */
    ABoolean GetKey(AUInt code);
    /**
    Check if key with 'code' has been pressed once
    */
    ABoolean GetKeyOnce(AUInt code);
    /**
    Check is mouse button with 'code' was clicked
    */
    ABoolean GetMouseButton(AUInt code);
    /**
    Check is mouse button with 'code' was clicked once
    */
    ABoolean GetMouseButtonOnce(AUInt code);









    /**
    Return mouse position
    */
    inline glm::vec2 GetMousePosition(){ return controller_data->GetVec2("mouse_position"); }
    /**
    Set mouse position
    */
    inline AVoid SetMousePosition(glm::vec2 new_position){glfwSetCursorPos(window, new_position.x, new_position.y); }
    /**
    Show cursor
    */
    inline AVoid ShowCursor(){glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); }
    /**
    Hide cursor
    */
    inline AVoid HideCursor(){glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); }
    /**
    Return wheel offset
    */
    inline ADouble GetWheelOffset(){ return controller_data->GetFloat("wheel_offset"); }
    /**
    Reset wheel offset
    */
    inline AVoid ResetWheelOffset(){ controller_data->SetFloat("wheel_offset", 0.0); }






    /**
    Get pointer to FPS counter
    */
    inline FPS * GetFPSCounter(){ return fps.get(); }
    /**
    Return window size
    */
    inline glm::ivec2 GetWindowSize() { return glm::ivec2(controller_data->GetInt("window_width"), controller_data->GetInt("window_height")); }
    /**
    Return window size
    */
    inline AInt GetWindowWidth(){ return controller_data->GetInt("window_width"); }
    /**
    Return window size
    */
    inline AInt GetWindowHeight(){ return controller_data->GetInt("window_height"); }
    /**
    Get window title
    */
    inline std::string GetWindowTitle(){return controller_data->GetString("title"); }
    /**
    Set window title
    */
    inline AVoid SetWindowTitle(std::string new_title){controller_data->SetString("title", new_title); glfwSetWindowTitle(window, new_title.c_str()); }
    /**
    Get pointer to GLFW window
    */
    inline GLFWwindow * GetWindow(){ return window; }
    /**
    Get pointer to controller data
    */
    inline AData * GetControllerData(){return controller_data.get(); }
    /**
    Close current window
    */
    inline AVoid CloseWindow(){glfwSetWindowShouldClose(window, true); }








    /**
    Get current list of files dropped inside window
    */
    inline std::vector<std::string> GetDropFiles(){ return drop_files; }

    /**
    Reset list of files dropped inside window
    */
    inline AVoid ResetDropList(){ drop_files.clear(); }






    /**
    Create window out of 'window_window', 'window_height', 'fullscreen', 'title' and OpenGL context version
    */
    static ABoolean CreateWindowContext(AUInt window_width, AUInt window_height,
                                         ABoolean fullscreen,
                                         std::string title,
                                         AUInt opengl_major_version,
                                         AUInt opengl_minor_version);



    /**
    Initialize data
    */
    AVoid Init();
    /**
    Compute data
    */
    AVoid Enable();
    /**
    Clean data
    */
    AVoid Clean();




};




#endif
