#include <stdafx.h>







AVoid Pipeline::Init()
{



    Add("CLRaytracer", new CLRaytracer());



}






AVoid Pipeline::Enable()
{


    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//-------------------------------------//


	Get("CLRaytracer")->Enable();
   



}




AVoid Pipeline::Clean()
{

	CleanModule();

}





