#include <stdafx.h>








void BaseResourceLoader::SaveChanges()
{


    try
    {

        std::pair<std::string, AModule*> it;



        BOOST_FOREACH(it, module_map)
                if (dynamic_cast<AStateSaver*>(it.second))
                static_cast<AStateSaver*>(it.second)->Save();


    }
    catch (const boost::filesystem::filesystem_error& ex)
    {
        std::cerr << ex.what();
    }


}



void BaseResourceLoader::LoadChanges()
{




    try
    {

        std::pair<std::string, AModule*> it;



        BOOST_FOREACH(it, module_map)
                if (dynamic_cast<AStateSaver*>(it.second))
                static_cast<AStateSaver*>(it.second)->Load();


    }
    catch (const boost::filesystem::filesystem_error& ex)
    {
        std::cerr << ex.what();
    }




}



void BaseResourceLoader::NoChanges()
{


    try
    {

        std::pair<std::string, AModule*> it;



        BOOST_FOREACH(it, module_map)
                if (dynamic_cast<AStateSaver*>(it.second))
                static_cast<AStateSaver*>(it.second)->Reset();


    }
    catch (const boost::filesystem::filesystem_error& ex)
    {
        std::cerr << ex.what();
    }




}




void BaseResourceLoader::Init()
{



}




void BaseResourceLoader::Clean()
{



}




void BaseResourceLoader::Enable()
{



}




