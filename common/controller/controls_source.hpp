#ifndef CONTROLS_SOURCE_HPP
#define CONTROLS_SOURCE_HPP




#include <stdafx.h>






/**
Class used to calculate framerate and time between frames
*/
class FPS
{



    AFloat fps;
    AInt frames;
    ADouble lastTime;
    ADouble lastTime2;
    ADouble deltaTime, returnable_deltaTime;




public:



    /**
    Returns current framerate
    */
    inline AFloat Get() { return fps; }
    /**
    Returns current time between frames
    */
    inline ADouble Delta() { return returnable_deltaTime; }
    /**
    Needs to be called at the begining of each frame
    */
    AVoid FirstPass();
    /**
    Needs to be called the end of each frame - computes required data
    */
    AVoid Compute();



};






/**


Base class for controller
Used to acces window and input


*/
class ControllerSource : public AModule
{



    /**
    Pointer the window to be handled by GLFW
    */
    static GLFWwindow* window;


    /**
    Window data
    */
    static AInt window_width, window_height;
    /**
    Window data
    */
    static ABoolean fullscreen;
    /**
    Window data
    */
    static std::string title;
    /**
    Data regarding OpenGL context version
    */
    static AUInt opengl_major_version;
    /**
    Data regarding OpenGL context version
    */
    static AUInt opengl_minor_version;


    //---


    /**
    Pointer to FPS counter
    */
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
    static AUInt fullscreen_key;


    /**
    Mouse buttons press
    */
    static AVoid mouse_callback(GLFWwindow* window, AInt button, AInt action, AInt mods);
    static glm::vec2 mouse_position;
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
    static ADouble wheel_offset;



    /**
    Initialize callbacks
    */
    static AVoid InitCallbacks();




public:


    /**
    Check if key with 'code' is being pressed
    */
    inline AUInt GetKey(AUInt code){ return ControllerSource::keys[code]; }
    /**
    Check if key with 'code' has been pressed once
    */
    inline AUInt GetKeyOnce(AUInt code){ AUInt result = (ControllerSource::keys[code] == 1); if (result)ControllerSource::keys[code]++; return result; }




    /**
    Return mouse position
    */
    inline glm::vec2 GetMousePosition(){ return ControllerSource::mouse_position; }
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
    Check is mouse button with 'code' was clicked
    */
    inline AUInt GetMouseButton(AUInt code){ return ControllerSource::mouse_buttons[code]; }
    /**
    Check is mouse button with 'code' was clicked once
    */
    inline AUInt GetMouseButtonOnce(AUInt code){ AUInt result = (ControllerSource::mouse_buttons[code] == 1); if (result)ControllerSource::mouse_buttons[code]++; return result; }
    /**
    Return wheel offset
    */
    inline ADouble GetWheelOffset(){ return wheel_offset; }
    /**
    Reset wheel offset
    */
    inline AVoid ResetWheelOffset(){ wheel_offset = 0.0; }





    /**
    Get pointer to FPS counter
    */
    inline FPS * GetFPSCounter(){ return fps.get(); }
    /**
    Return window size
    */
    inline glm::ivec2 GetWindowSize() { return glm::ivec2(window_width, window_height); }
    /**
    Return window size
    */
    inline AInt GetWindowWidth(){ return window_width; }
    /**
    Return window size
    */
    inline AInt GetWindowHeight(){ return window_height; }
    /**
    Get window title
    */
    inline std::string GetWindowTitle(){return title;}
    /**
    Set window title
    */
    inline AVoid SetWindowTitle(std::string new_title){title = new_title; glfwSetWindowTitle(window, title.c_str()); }
    /**
    Set the key to be used for switching to fullscreen
    */
    inline AVoid SetFullscreenKey(AUInt key){ ControllerSource::fullscreen_key = key; }
    /**
    Get pointer to GLFW window
    */
    inline GLFWwindow * GetWindow(){ return window; }








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
