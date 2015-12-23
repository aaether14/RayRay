#include <stdafx.h>





void GLSLRaytracer::Init()
{


	raytracing_program = new Shader();
	raytracing_program->Add("data/shaders/raytracer_vert.glsl", GL_VERTEX_SHADER);
	raytracing_program->Add("data/shaders/raytracer_frag.glsl", GL_FRAGMENT_SHADER);
	raytracing_program->Link();


	//---------------------------------//


	raytracing_program->AddVariable("gAspectRatio");
	raytracing_program->AddVariable("gTanHalfFOV");
	raytracing_program->AddVariable("ViewMatrix");
	raytracing_program->AddVariable("camera_pos");
	raytracing_program->AddVariable("texture_adress1");
	raytracing_program->AddVariable("texture_adress2");
	raytracing_program->AddVariable("time");


	//---------------------------------------//



	sphere_texture = TextureObject::load_texture("sphere.png", GL_LINEAR, GL_LINEAR);
	space_texture = TextureObject::load_texture("space.jpg", GL_LINEAR, GL_LINEAR);


	
}





void GLSLRaytracer::Clean()
{


	CleanModule();


}




void GLSLRaytracer::Enable()
{


	Techniques * tech = static_cast<Techniques*>(GetManager()->Get("DataManager")->Get("Techniques"));
	Camera * cam = static_cast<Camera*>(GetManager()->Get("Controller")->Get("Camera"));
	ViewInfo * info = cam->GetInfo();
	View * view = cam->GetView();


	//-------------------------------------------//


	raytracing_program->Enable();


	//------------------------------------------//


	raytracing_program->Set("gAspectRatio", info->getRatio());
	raytracing_program->Set("gTanHalfFOV", info->getTanHalfFov());
	raytracing_program->Set("ViewMatrix", glm::inverse(view->getViewMatrix()));
	raytracing_program->Set("camera_pos", info->getCameraPos());
	raytracing_program->Set("time", GLfloat(glfwGetTime()));
	raytracing_program->Set("texture_adress1", 0);
	raytracing_program->Set("texture_adress2", 1);


	//-------------------------------------------//


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sphere_texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, space_texture);


	//-------------------------------------------//

	tech->GetBasic()->GetQuad()->Render();
	raytracing_program->Stop();




}




