#include <stdafx.h>




AVoid AModule::SetManager(AModule * module)
{

    manager = module;

}



AVoid AModule::CleanModule()
{


    std::pair<std::string, AModule*> it;
    BOOST_FOREACH(it, module_map)
            it.second->Clean();

    module_map.clear();


}



AVoid AModule::Add(std::string key, AModule * module)
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






std::map < std::string, AModule* > * AModule::GetModuleMapPointer()
{

    return &module_map;

}













