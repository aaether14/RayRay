#include <stdafx.h>



void DataManager::Init()
{



	ControllerSource * controller_source = static_cast<ControllerSource*>(GetManager()->Get("Controller"));
	GLuint window_width = controller_source->GetWindowWidth();
	GLuint window_height = controller_source->GetWindowHeight();





	Techniques * techniques = new Techniques();
    techniques->Create(window_width, window_height);





	Add("Techniques", techniques);
	Add("Resources", new ResourceLoader());








}




void DataManager::Enable()
{




}


void DataManager::Clean()
{


	CleanModule();


}



