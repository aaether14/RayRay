#include <stdafx.h>







AVoid Application::Init()
{



    Py_Initialize();
    GLM_Wrapper::Init();
    Controller_Wrapper::Init();



    SetManager(this);



    Add("Controller", new Controller());
    Add("CLContextWrapper", new CLContextWrapper());
    Add("DataManager", new DataManager());
    Add("Pipeline", new Pipeline());
    Add("Python", new PythonManager());
    Add("UI", new UIWorkStation());








}






AVoid Application::Enable()
{



    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);




    Controller * ctrl = static_cast<Controller*>(Get("Controller"));



    do{



        try
        {


            Get("Controller")->Enable();
            Get("DataManager")->Enable();
            Get("Pipeline")->Enable();
            Get("UI")->Enable();



        }
        catch (AError err)
        {

            std::cerr << err.what() << std::endl;

        }



        glfwSwapBuffers(ctrl->GetWindow());
        glfwPollEvents();




    } while (!ctrl->GetKey(GLFW_KEY_ESCAPE) &&
             !glfwWindowShouldClose(ctrl->GetWindow()));


}





AVoid Application::Clean()
{


    CleanModule();
    Py_Finalize();


}




