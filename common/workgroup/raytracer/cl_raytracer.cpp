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


        ray_kernel->Create(cl_cw, L"data/kernels/GodRays.cl", "", "GodRays", "-I data/kernels/");
        ray_kernel->AddGLTexture("KernelOutput", width, height, GL_RGBA, GL_RGBA, GL_FLOAT, CL_MEM_WRITE_ONLY);
        ray_kernel->AddDataBuffer<cl_float*>("view_matrix", sizeof(glm::mat4), CL_MEM_READ_ONLY);
        ray_kernel->AddDataBuffer<cl_float*>("scene_data", sizeof(cl_float) * 1024, CL_MEM_READ_ONLY);



	}
    catch (AError err)
	{

		std::cerr << err.what() << std::endl;

	}


	//----------------------//


    ray_kernel->SetGLTextureArg("KernelOutput", 0);
    ray_kernel->SetDataBufferArg("view_matrix", 1);
    ray_kernel->SetArgValue(width, 2);
    ray_kernel->SetArgValue(height, 3);
    ray_kernel->SetArgValue(tan_half_fov, 4);
    ray_kernel->SetDataBufferArg("scene_data", 5);


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


    ray_kernel->WriteToDataBuffer<cl_float*>("view_matrix", sizeof(glm::mat4), (cl_float*)(&view_matrix));
    ray_kernel->WriteToDataBuffer<cl_float*>("scene_data", scene_builder->GetSceneSize(), scene_builder->GetSceneDataPointer());
    ray_kernel->Enable();



    //------------------------------------------------------------//



    tech->ApplyFilter(NULL_FILTER, ray_kernel->GetGLTextureID("KernelOutput"), NULL, width, height);
    tech->Unbind();





}
