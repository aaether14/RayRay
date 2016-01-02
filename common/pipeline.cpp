#include <stdafx.h>







void Pipeline::Init()
{



	Add("CLRaytracer", new CLRaytracer());



}






void Pipeline::Enable()
{


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//-------------------------------------//


	Get("CLRaytracer")->Enable();
   



}




void Pipeline::Clean()
{

	CleanModule();

}





