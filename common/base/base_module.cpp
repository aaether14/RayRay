#include <stdafx.h>




void AModule::SetManager(AModule * module)
{

	manager = module;

}



void AModule::CleanModule()
{


    std::pair<std::string, AModule*> it;
    BOOST_FOREACH(it, module_map)
        it.second->Clean();
	
	module_map.clear();


}



void AModule::Add(std::string key, AModule * module)
{

	module_map[key] = module;
	module->SetManager(GetManager());
	module->Init();


}





AModule * AModule::Get(std::string key)
{

	return module_map[key];

}




AModule * AModule::GetManager()
{

	return manager;

}
