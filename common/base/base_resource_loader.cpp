#include <stdafx.h>








AVoid BaseResourceLoader::SaveChanges()
{


    try
    {

        BOOST_FOREACH(auto it, module_map)
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

        BOOST_FOREACH(auto it, module_map)
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

        BOOST_FOREACH(auto it, module_map)
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




