#include <stdafx.h>





void CLRaytracer::Init()
{



	Add("RayKernel", new CLKernel());
	Add("SceneBuilder", new RayTracerSceneBuilder());



	//-----------------------------------------//



	Controller *ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
	Camera * cam = static_cast<Camera*>(ctrl->Get("Camera"));
	ViewInfo * info = cam->GetInfo();



	//------------------------------------------//


	cl_float tan_half_fov = info->getTanHalfFov();
	cl_int width = ctrl->GetWindowWidth();
	cl_int height = ctrl->GetWindowHeight();


	//-------------------------------------------//


	CLContextWrapper * cl_cw = static_cast<CLContextWrapper*>(GetManager()->Get("CLContextWrapper"));
	CLKernel * ray_kernel = static_cast<CLKernel*>(Get("RayKernel"));


	//----------------------------------------//



	try
	{


		ray_kernel->Create(cl_cw, L"data/kernels/Godrays.cl", "", "GodRays");
		ray_kernel->AddFloatBuffer("output", width * height * sizeof(cl_float4), CL_MEM_WRITE_ONLY);
		ray_kernel->AddFloatBuffer("view_matrix", sizeof(glm::mat4), CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR);
		ray_kernel->AddFloatBuffer("scene_data", sizeof(cl_float) * 1000, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR);

	}
	catch (Error err)
	{

		std::cerr << err.what() << std::endl;

	}


	//----------------------//


	ray_kernel->SetFloatBufferArg("output", 0);
	ray_kernel->SetFloatBufferArg("view_matrix", 1);
	ray_kernel->SetArgValue(&width, 2);
	ray_kernel->SetArgValue(&height, 3);
	ray_kernel->SetArgValue(&tan_half_fov, 4);
	ray_kernel->SetFloatBufferArg("scene_data", 5);


	//---------------------//


	ray_kernel->SetWorkSize(width * height, 64);
	


    
	//---------------------------------------//


}





void CLRaytracer::Clean()
{

	CleanModule();

}




void CLRaytracer::Enable()
{




	Controller *ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
	Camera * cam = static_cast<Camera*>(ctrl->Get("Camera"));
	ViewInfo * info = cam->GetInfo();
	View * view = cam->GetView();


	//------------------------------------------------------------//



	Techniques * tech = static_cast<Techniques*>(GetManager()->Get("DataManager")->Get("Techniques"));
	CLKernel * ray_kernel = static_cast<CLKernel*>(Get("RayKernel"));
	RayTracerSceneBuilder * scene_builder = static_cast<RayTracerSceneBuilder*>(Get("SceneBuilder"));




	cl_int width = ctrl->GetWindowWidth();
	cl_int height = ctrl->GetWindowHeight();
	glm::mat4 view_matrix = glm::inverse(view->getViewMatrix());



	//------------------------------------------------------------//


	


	//Create scene data

	scene_builder->Enable();


	//Run kernel


	ray_kernel->WriteToFloatBuffer("view_matrix", sizeof(glm::mat4), (cl_float*)(&view_matrix));
	ray_kernel->WriteToFloatBuffer("scene_data", scene_builder->GetSceneSize(), scene_builder->GetSceneDataPointer());
	ray_kernel->Enable();
	ray_kernel->ReadFloatBuffer("output", width * height * sizeof(cl_float4));







	//-----------------------------------------------------------//




	GLuint tex_id;
	glGenTextures(1, &tex_id);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, ray_kernel->GetFloatBuffer("output"));
	glBindTexture(GL_TEXTURE_2D, 0);



	//-------------------------------------------//



	tech->ApplyFilter(NULL_FILTER, tex_id, NULL, width, height);
	tech->Unbind();


	//-----------------------------------------//



	glDeleteTextures(1, &tex_id);


	//------------------------------------------//






}