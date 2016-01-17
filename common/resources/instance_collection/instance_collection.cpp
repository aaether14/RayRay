#include <stdafx.h>








void InstanceCollection::Load()
{




    Reset();




    using boost::property_tree::ptree;
    ptree pt;
    read_xml(GetPath(), pt);




    BOOST_FOREACH(ptree::value_type const& v, pt.get_child("Scene"))
    {




        if (v.first == "EntityInstance")
        {


            //Names handling


            std::string instance_name = v.second.get<std::string>("Name");
            EntityInstance * new_instance = new EntityInstance();
            new_instance->SetEntityName(v.second.get<std::string>("EntityName"));




            //Component loading



            BOOST_FOREACH(ptree::value_type const& instance_info_index, v.second)
            {
                if (instance_info_index.first == "Component")
                {
                    AData * adata = new AData();
                    adata->LoadInterface(instance_info_index.second);
                    new_instance->AddAData("DataComponent_" + adata->GetComponentName(), adata);
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




void InstanceCollection::Save()
{





    using boost::property_tree::ptree;
    ptree pt;
    ptree rootNode;





    std::pair<std::string, boost::shared_ptr<EntityInstance>> it;
    BOOST_FOREACH(it, instance_map)
    {



        EntityInstance * instance = it.second.get();




        //Signature


        ptree new_info;
        new_info.push_back(ptree::value_type("EntityName", ptree(instance->GetEntityName())));
        new_info.push_back(ptree::value_type("Name", ptree(it.first)));



        //Components

        std::pair<std::string, boost::shared_ptr<AData> > adatas_iterator;
        BOOST_FOREACH(adatas_iterator, *instance->GetADatasMapPointer())
        {
            new_info.add_child("Component", adatas_iterator.second.get()->Save());
        }
        rootNode.add_child("EntityInstance", new_info);


    }



    //Saving to xml


    pt.add_child("Scene", rootNode);
    AFile::SavePtree(GetPath(), pt);




}




void InstanceCollection::Reset()
{


    ClearInstances();
    CleanModule();


}






