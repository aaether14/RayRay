#include <stdafx.h>



void DataManager::Init()
{



    ControllerSource * ctrl = static_cast<ControllerSource*>(GetManager()->Get("Controller"));
	Techniques * techniques = new Techniques();
    techniques->Create(ctrl->GetWindowSize());




	Add("Techniques", techniques);
    Add("EntityCollection", new EntityCollection());
	Add("Resources", new ResourceLoader());








}




void DataManager::Enable()
{




}


void DataManager::Clean()
{


	CleanModule();


}



