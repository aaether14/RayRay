#include <stdafx.h>




void Camera::Init()
{


	//Initialising


	verticalAngle = -M_PI / 24;
	horizontalAngle = M_PI;
	base_speed = speed = 30.0f;
	mouse_speed = 0.0025f;
	rotation_speed = M_PI;



	view = new View();
	info = new ViewInfo();
	frustum = new Frustum();



}



void Camera::Clean()
{


	//Cleaning up...



	if (view)
	delete view;


	if (info)
	delete info;


	if (frustum)
	delete frustum;


}



void Camera::ProcessInput(ControllerSource * source)
{




	if (source->GetKey(GLFW_KEY_LEFT_SHIFT))
		speed = 3 * base_speed;
	else
		speed = base_speed;



	if (source->GetKey(GLFW_KEY_W))
		info->SetCameraPos(info->getCameraPos() + info->getDirection() * GLfloat(source->GetFpsPointer()->Delta()) * speed);



	if (source->GetKey(GLFW_KEY_S))
		info->SetCameraPos(info->getCameraPos() - info->getDirection() * GLfloat(source->GetFpsPointer()->Delta()) * speed);





	if (source->GetKey(GLFW_KEY_A))
		horizontalAngle += source->GetFpsPointer()->Delta()*rotation_speed;



	if (source->GetKey(GLFW_KEY_D))
		horizontalAngle -= source->GetFpsPointer()->Delta()*rotation_speed;







}





void Camera::ComputeAngles(ControllerSource * source){



	//Preparing mouse input for world movement



	GLdouble delta_x, delta_y;



	if (glfwGetMouseButton(source->GetWindow(), GLFW_MOUSE_BUTTON_RIGHT))
	{


		glfwGetCursorPos(source->GetWindow(), &delta_x, &delta_y);
		glfwSetCursorPos(source->GetWindow(), last_x, last_y);



		delta_x = mouse_speed * GLdouble(last_x - delta_x);
		delta_y = mouse_speed * GLdouble(last_y - delta_y);


		horizontalAngle += delta_x;
		verticalAngle += delta_y;




	}
	else
	{
		glfwGetCursorPos(source->GetWindow(), &last_x, &last_y);
	}




	SetInfo(source);
	glfwSetInputMode(source->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);



}





void Camera::SetInfo(ControllerSource * source)
{


	//converting mouse movement to spherical coodrs to view direction



	info->setDirection(glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
		));



	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - M_PI / 2.0f),
		0,
		cos(horizontalAngle - M_PI / 2.0f)
		);




	info->setUpVec(glm::cross(right, info->getDirection()));
	info->setRatio(GLfloat(source->GetWindowWidth()) / GLfloat(source->GetWindowHeight()));
	info->setNear(1.0f);



	//Computing the view state


	view->Create1st(info);



}