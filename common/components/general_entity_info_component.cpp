#include <stdafx.h>





bool InfoComponent::isValid(std::string extension)
{


	//See if valid extension


	if (!extension.compare(".ainfo"))
		return true;
	return false;


}




void InfoComponent::Load(std::string path, std::string extension)
{

	//Read if valid file

	info->Read(path);



}




void InfoComponent::Init()
{


	info = new GeneralEntityInfo();


}



void InfoComponent::Clean()
{


	delete info;


}




void InfoComponent::GeneralEntityInfo::Read(std::string path)
{


	//read xml using boost


	using boost::property_tree::ptree;
	ptree pt;
	read_xml(path, pt);




	BOOST_FOREACH(ptree::value_type const& v, pt.get_child("GeneralInfo"))
	{


		if (v.first == "BaseInfo")
		{



			entity_name = v.second.get<std::string>("EntityName");



		}


		break;

	}

}




boost::property_tree::ptree InfoComponent::GeneralEntityInfo::GetPtree()
{

	using boost::property_tree::ptree;
	ptree pt;
	ptree rootNode;




			ptree new_info;
			new_info.push_back(ptree::value_type("EntityName", ptree(entity_name)));
			rootNode.add_child("BaseInfo", new_info);



	pt.add_child("GeneralInfo", rootNode);
	

	return pt;

}