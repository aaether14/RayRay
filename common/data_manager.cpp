#include <stdafx.h>






AVoid DataManager::Init()
{



    ControllerSource * ctrl = static_cast<ControllerSource*>(GetManager()->Get("Controller"));
	Techniques * techniques = new Techniques();
    techniques->Create(ctrl->GetWindowSize());




    Add("Techniques", techniques);
    Add("EntityCollection", new EntityCollection());
	Add("Resources", new ResourceLoader());








}




AVoid DataManager::Enable()
{




}


AVoid DataManager::Clean()
{


	CleanModule();


}



