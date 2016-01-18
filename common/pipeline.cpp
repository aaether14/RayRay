#include <stdafx.h>







AVoid Pipeline::Init()
{



    Add("CLRaytracer", new CLRaytracer());



}






AVoid Pipeline::Enable()
{


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//-------------------------------------//


	Get("CLRaytracer")->Enable();
   



}




AVoid Pipeline::Clean()
{

	CleanModule();

}





