#include <stdafx.h>








AVoid BaseResourceLoader::SaveChanges()
{


    try
    {

        std::pair<std::string, boost::shared_ptr<AModule> > it;
        BOOST_FOREACH(it, module_map)
                if (dynamic_cast<AStateSaver*>(it.second.get()))
                static_cast<AStateSaver*>(it.second.get())->Save();


    }
    catch (const boost::filesystem::filesystem_error& ex)
    {
        std::cerr << ex.what();
    }


}



AVoid BaseResourceLoader::LoadChanges()
{




    try
    {

        std::pair<std::string, boost::shared_ptr<AModule> > it;
        BOOST_FOREACH(it, module_map)
                if (dynamic_cast<AStateSaver*>(it.second.get()))
                static_cast<AStateSaver*>(it.second.get())->Load();


    }
    catch (const boost::filesystem::filesystem_error& ex)
    {
        std::cerr << ex.what();
    }




}



AVoid BaseResourceLoader::NoChanges()
{


    try
    {

        std::pair<std::string, boost::shared_ptr<AModule> > it;
        BOOST_FOREACH(it, module_map)
                if (dynamic_cast<AStateSaver*>(it.second.get()))
                static_cast<AStateSaver*>(it.second.get())->Reset();


    }
    catch (const boost::filesystem::filesystem_error& ex)
    {
        std::cerr << ex.what();
    }




}




AVoid BaseResourceLoader::Init()
{



}




AVoid BaseResourceLoader::Clean()
{



}




AVoid BaseResourceLoader::Enable()
{



}




