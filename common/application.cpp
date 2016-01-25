#include <stdafx.h>







AVoid Application::Init()
{




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




    Controller * ctrl = static_cast<Controller*>(Get("Controller"));



    do{





        Get("Controller")->Enable();
        Get("DataManager")->Enable();
        Get("Pipeline")->Enable();
        Get("UI")->Enable();





        glfwSwapBuffers(ctrl->GetWindow());
        glfwPollEvents();




    } while (!ctrl->GetKey(GLFW_KEY_ESCAPE) &&
             !glfwWindowShouldClose(ctrl->GetWindow()));


}





AVoid Application::Clean()
{


    CleanModule();


}




