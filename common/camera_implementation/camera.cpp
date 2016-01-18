#include <stdafx.h>




AVoid Camera::Init()
{


    //Initialising


    camera_angles = glm::vec2(-M_PI / 24, M_PI);
    camera_speed[CAMERA_BASE_SPEED] = camera_speed[CAMERA_SPEED] = 30.0;
    camera_speed[MOUSE_SPEED] = 0.25f;
    camera_speed[ROTATION_SPEED] = M_PI;



    view = new View();
    info = new ViewInfo();



}



AVoid Camera::Clean()
{


    //Cleaning up...



    if (view)
        delete view;


    if (info)
        delete info;




}



AVoid Camera::ProcessInput()
{



    ControllerSource * source = static_cast<ControllerSource*>(GetManager()->Get("Controller"));




    if (source->GetKey(GLFW_KEY_LEFT_SHIFT))
        camera_speed[CAMERA_SPEED] = 3 * camera_speed[CAMERA_BASE_SPEED];
    else
        camera_speed[CAMERA_SPEED] = camera_speed[CAMERA_BASE_SPEED];



    if (source->GetKey(GLFW_KEY_W))
        info->SetCameraPos(info->getCameraPos() + info->getDirection() * AFloat(source->GetFPSCounter()->Delta() * camera_speed[CAMERA_SPEED]));



    if (source->GetKey(GLFW_KEY_S))
        info->SetCameraPos(info->getCameraPos() - info->getDirection() * AFloat(source->GetFPSCounter()->Delta() * camera_speed[CAMERA_SPEED]));





    if (source->GetKey(GLFW_KEY_A))
        camera_angles.x += source->GetFPSCounter()->Delta()*camera_speed[ROTATION_SPEED];



    if (source->GetKey(GLFW_KEY_D))
        camera_angles.x -= source->GetFPSCounter()->Delta()*camera_speed[ROTATION_SPEED];







}





AVoid Camera::ComputeAngles(){




    ControllerSource * source = static_cast<ControllerSource*>(GetManager()->Get("Controller"));


    //Preparing mouse input for world movement



    if (source->GetMouseButton(GLFW_MOUSE_BUTTON_RIGHT))
    {


        source->SetMousePosition(last_mouse_position);


        camera_angles.x += camera_speed[MOUSE_SPEED] * ADouble(last_mouse_position.x - source->GetMousePosition().x) * source->GetFPSCounter()->Delta();
        camera_angles.y -= camera_speed[MOUSE_SPEED] * ADouble(last_mouse_position.y - source->GetMousePosition().y) * source->GetFPSCounter()->Delta();




    }
    else
    {
        last_mouse_position.x = source->GetMousePosition().x;
        last_mouse_position.y = source->GetMousePosition().y;
    }








}





AVoid Camera::SetInfo()
{



    ControllerSource * source = static_cast<ControllerSource*>(GetManager()->Get("Controller"));



    //converting mouse movement to spherical coodrs to view direction



    info->setDirection(glm::vec3(
                           cos(camera_angles.y) * sin(camera_angles.x),
                           sin(camera_angles.y),
                           cos(camera_angles.y) * cos(camera_angles.x)
                           ));



    glm::vec3 right = glm::vec3(
                sin(camera_angles.x - M_PI / 2.0f),
                0,
                cos(camera_angles.x - M_PI / 2.0f)
                );




    info->setUpVec(glm::cross(info->getDirection(), right));
    info->setRatio(AFloat(source->GetWindowWidth()) / AFloat(source->GetWindowHeight()));
    info->setNear(1.0f);



    //Computing the view state


    view->Create1st(info);



}




AVoid Camera::Enable()
{


    ControllerSource * source = static_cast<ControllerSource*>(GetManager()->Get("Controller"));


    ProcessInput();
    ComputeAngles();
    SetInfo();
    source->HideCursor();



}
