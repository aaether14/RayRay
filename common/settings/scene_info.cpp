#include <stdafx.h>






void SceneInfo::CreateComponentInstance(boost::filesystem::directory_iterator iterator, AComponent * new_component, std::string class_name, Entity * new_entity)
{





	if (new_component->isValid(AString::char_to_str(boost::filesystem::extension(iterator->path()))))
	{


		//Process component loading


		new_component->Init();
		new_component->Load(AString::char_to_str(iterator->path().string()),
			AString::char_to_str(boost::filesystem::extension(iterator->path())));




		//Special case for data component


		if (static_cast<DataComponent*>(new_component))
		{
			DataComponent * dc = static_cast<DataComponent*>(new_component);
			class_name += ("_" + dc->GetComponentName());
		}



		//Add component to entity

		new_entity->AddComponent(class_name, new_component);



	}
	else if (new_component)
		delete new_component;





}






void SceneInfo::AddComponentsToEntity(char * path, Entity * new_entity)
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





void SceneInfo::AddEntity(Entity * new_entity)
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
				if (!entity_map.count(ic->GetInfo()->entity_name))
					entity_map[ic->GetInfo()->entity_name].reset(new_entity);
				else
				{
					GLuint number_sufix = 2;
					while (entity_map.count(ic->GetInfo()->entity_name + std::to_string(number_sufix)))
						number_sufix++;
					ic->GetInfo()->entity_name = ic->GetInfo()->entity_name + std::to_string(number_sufix);
					entity_map[ic->GetInfo()->entity_name].reset(new_entity);

				}




			}
			else
			{
				const std::string &ex("No info component found");
				std::cerr<<ex<<std::endl;
			}



		}


}





void SceneInfo::Load()
{



	//reading components



	Reset();



		boost::filesystem::directory_iterator iterator(std::string(OBJECT_FOLDER));
		for (; iterator != boost::filesystem::directory_iterator(); ++iterator)
		{



			Entity * new_entity = new Entity();
			AddComponentsToEntity(AString::char_to_str(iterator->path().string()), new_entity);
			AddEntity(new_entity);



		}





	//Reading infos






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



			if (entity_map.count(new_instance->GetEntityName()))
				AddInstance(instance_name, new_instance);





		}



	}



	SetShouldReset(true);


}




void SceneInfo::Save()
{





	using boost::property_tree::ptree;
	ptree pt;
	ptree rootNode;





	std::map<std::string, boost::shared_ptr<EntityInstance>>::iterator it;



	for (it = instance_map.begin(); it != instance_map.end(); it++)
	{


		EntityInstance * instance = it->second.get();




		//Signature


			ptree new_info;
			new_info.push_back(ptree::value_type("EntityName", ptree(instance->GetEntityName())));
			new_info.push_back(ptree::value_type("Name", ptree(it->first)));


			//Components

			//Adding Adatas
			{
				std::map<std::string, boost::shared_ptr<AData>>::iterator it;
			}
			rootNode.add_child("EntityInstance", new_info);


	}



	//Saving to xml


	pt.add_child("Scene", rootNode);
	AFile::SavePtree(GetPath(), pt);




}




void SceneInfo::Reset()
{


	ClearInstances();
	ClearEntities();


}






