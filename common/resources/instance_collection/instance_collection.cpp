#include <stdafx.h>








AVoid InstanceCollection::Load()
{




    Reset();





    boost::property_tree::ptree pt = AFile::GetPtree(GetPath()).get_child("Scene");
    BOOST_FOREACH(auto v, pt)
    {




        if (v.first == "EntityInstance")
        {


            //Names handling


            std::string instance_name = v.second.get<std::string>("Name");
            EntityInstance * new_instance = new EntityInstance();
            new_instance->SetEntityName(v.second.get<std::string>("EntityName"));




            //Component loading



            BOOST_FOREACH(auto instance_info_index, v.second)
            {
                if (instance_info_index.first == "Component")
                {
                    AData * adata = new AData();
                    adata->LoadInterface(instance_info_index.second);
                    new_instance->AddAData("DataComponent_" + adata->Get<std::string>("__name__"), adata);
                }
            }



            //If entity in cause exists, create instance


            EntityCollection * entity_collection = static_cast<EntityCollection*>(GetManager()->Get("DataManager")->Get("EntityCollection"));
            if (entity_collection->InCollection(new_instance->GetEntityName()))
                AddInstance(instance_name, new_instance);





        }



    }



    SetShouldReset(true);


}




AVoid InstanceCollection::Save()
{




    boost::property_tree::ptree pt;
    boost::property_tree::ptree rootNode;





    BOOST_FOREACH(auto it, instance_map)
    {



        EntityInstance * instance = it.second.get();




        //Signature


        boost::property_tree::ptree new_info;
        new_info.push_back(boost::property_tree::ptree::value_type("EntityName", boost::property_tree::ptree(instance->GetEntityName())));
        new_info.push_back(boost::property_tree::ptree::value_type("Name", boost::property_tree::ptree(it.first)));



        //Components

        BOOST_FOREACH(auto adatas_iterator, *instance->GetADatasMapPointer())
                new_info.add_child("Component", adatas_iterator.second.get()->Save());
        rootNode.add_child("EntityInstance", new_info);


    }



    //Saving to xml


    pt.add_child("Scene", rootNode);
    AFile::SavePtree(GetPath(), pt);




}




AVoid InstanceCollection::Reset()
{


    ClearInstances();
    CleanModule();


}






