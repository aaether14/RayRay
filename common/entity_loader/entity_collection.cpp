#include <stdafx.h>






AVoid EntityCollection::CreateComponentInstance(boost::filesystem::directory_iterator iterator, AComponent * new_component, std::string class_name, Entity * new_entity)
{




    std::string component_extension = boost::filesystem::extension(iterator->path());
    std::string component_path = iterator->path().string();




    if (new_component->isValid(component_extension))
    {


        //Process component loading


        new_component->Init();
        new_component->Load(component_path, component_extension);




        //Special case for data component


        if (dynamic_cast<DataComponent*>(new_component))
        {
            DataComponent * dc = dynamic_cast<DataComponent*>(new_component);
            class_name += ("_" + dc->GetComponentName());
        }



        //Add component to entity
        class_name = new_entity->GetAvailableName(class_name);
        new_entity->AddComponent(class_name, new_component);



    }
    else if (new_component)
        delete new_component;





}






AVoid EntityCollection::AddComponentsToEntity(std::string path, Entity * new_entity)
{






    boost::filesystem::directory_iterator iterator(path);
    for (; iterator != boost::filesystem::directory_iterator(); ++iterator)
    {




        if (boost::filesystem::is_regular_file(iterator->path()))
        {




            CreateComponentInstance(iterator, new InfoComponent(), "InfoComponent", new_entity);
            CreateComponentInstance(iterator, new DataComponent(), "DataComponent", new_entity);





        }



    }


}





AVoid EntityCollection::AddEntity(Entity * new_entity)
{



    if (new_entity)
        if (!new_entity->GetComponentsSize())
            delete new_entity;
        else
        {


            //Handle non-empty entity


            if (new_entity->GetComponent("InfoComponent"))
            {


                //Valid entity case


                InfoComponent * ic = static_cast<InfoComponent*>(new_entity->GetComponent("InfoComponent"));
                ic->GetInfo()->entity_name = GetAvailableName(ic->GetInfo()->entity_name);
                entity_map[ic->GetInfo()->entity_name].reset(new_entity);





            }
            else
            {
                const std::string &ex("No info component found");
                std::cerr<<ex<<std::endl;
            }



        }


}





AVoid EntityCollection::Init()
{


    boost::filesystem::directory_iterator iterator(std::string(OBJECT_FOLDER));
    for (; iterator != boost::filesystem::directory_iterator(); ++iterator)
    {



        Entity * new_entity = new Entity();
        AddComponentsToEntity(iterator->path().string(), new_entity);
        AddEntity(new_entity);



    }





}







AVoid EntityCollection::Clean()
{

    ClearEntities();
    CleanModule();


}













