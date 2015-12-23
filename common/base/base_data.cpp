#include <stdafx.h>




void AData::LoadInterface(boost::property_tree::ptree base_index)
{


    using boost::property_tree::ptree;



	BOOST_FOREACH(ptree::value_type const& v, base_index)
	{


		if (v.first == "GeneralInfo")
			SetComponentName(v.second.get<std::string>("Name"));



		if (v.first == "Float")
			SetFloat(v.second.get<std::string>("V"),boost::lexical_cast<float>(v.second.get<std::string>("D")));
		if (v.first == "Int")
			SetInt(v.second.get<std::string>("V"), boost::lexical_cast<int>(v.second.get<std::string>("D")));
		if (v.first == "Vec2")
			SetVec2(v.second.get<std::string>("V"), Math::GetVec2FromString(v.second.get<std::string>("D")));
		if (v.first == "Vec3")
			SetVec3(v.second.get<std::string>("V"), Math::GetVec3FromString(v.second.get<std::string>("D")));
		if (v.first == "Vec4")
			SetVec4(v.second.get<std::string>("V"), Math::GetVec4FromString(v.second.get<std::string>("D")));



	}




	Debug();



}




void AData::Debug()
{




	std::cout << "\n\nPrinting debug for: " << GetComponentName() << std::endl;




		//Float debug
	if (float_map.size() > 0)
	{
		std::cout << std::endl;
		std::cout << "Floats:" << std::endl;
		std::map<std::string, GLfloat>::iterator it;


		for (it = float_map.begin(); it != float_map.end(); it++)
			std::cout << it->first << ": " << it->second;
	}





		//Int debug
	if (int_map.size() > 0)
	{
		std::cout << std::endl;
		std::cout << "Integers:" << std::endl;
		std::map<std::string, GLint>::iterator it;


		for (it = int_map.begin(); it != int_map.end(); it++)
			std::cout << it->first << ": " << it->second;
	}




	//Vec2 debug
	if (vec2_map.size() > 0)
	{
		std::cout << std::endl;
		std::cout << "Vec2:" << std::endl;
		std::map<std::string, glm::vec2>::iterator it;


		for (it = vec2_map.begin(); it != vec2_map.end(); it++)
		{
			std::cout << it->first << ": ";
			Math::print_vec2(it->second);
		}


	}



	//Vec3 debug
	if (vec3_map.size() > 0)
	{
		std::cout << std::endl;
		std::cout << "Vec3:" << std::endl;
		std::map<std::string, glm::vec3>::iterator it;


		for (it = vec3_map.begin(); it != vec3_map.end(); it++)
		{
			std::cout << it->first << ": ";
			Math::print_vec3(it->second);
		}


	}



	//Vec4 debug
	if (vec4_map.size() > 0)
	{
		std::cout << std::endl;
		std::cout << "Vec4:" << std::endl;
		std::map<std::string, glm::vec4>::iterator it;


		for (it = vec4_map.begin(); it != vec4_map.end(); it++)
		{
			std::cout << it->first << ": ";
			Math::print_vec4(it->second);
		}


	}


	


}





void AData::Clean()
{


	int_map.clear();
	float_map.clear();
	vec2_map.clear();
	vec3_map.clear();
	vec4_map.clear();



}





boost::property_tree::ptree AData::Save()
{


	boost::property_tree::ptree ptree_data;




	//Float saving
	if (float_map.size() > 0)
	{

		std::map<std::string, GLfloat>::iterator it;

		for (it = float_map.begin(); it != float_map.end(); it++)
		{
			boost::property_tree::ptree ptree_float_data;
			ptree_float_data.push_back(boost::property_tree::ptree::value_type("V", boost::property_tree::ptree(it->first)));
			ptree_float_data.push_back(boost::property_tree::ptree::value_type("D", boost::property_tree::ptree(boost::lexical_cast<std::string>(it->second))));
			ptree_data.push_back(boost::property_tree::ptree::value_type("Float", ptree_float_data));

		}

	}





	//Int saving
	if (int_map.size() > 0)
	{

		std::map<std::string, GLint>::iterator it;

		for (it = int_map.begin(); it != int_map.end(); it++)
		{
			boost::property_tree::ptree ptree_float_data;
			ptree_float_data.push_back(boost::property_tree::ptree::value_type("V", boost::property_tree::ptree(it->first)));
			ptree_float_data.push_back(boost::property_tree::ptree::value_type("D", boost::property_tree::ptree(boost::lexical_cast<std::string>(it->second))));
			ptree_data.push_back(boost::property_tree::ptree::value_type("Int", ptree_float_data));

		}

	}




	//Vec2 saving
	if (vec2_map.size() > 0)
	{

		std::map<std::string, glm::vec2>::iterator it;

		for (it = vec2_map.begin(); it != vec2_map.end(); it++)
		{
			boost::property_tree::ptree ptree_float_data;
			ptree_float_data.push_back(boost::property_tree::ptree::value_type("V", boost::property_tree::ptree(it->first)));
			ptree_float_data.push_back(boost::property_tree::ptree::value_type("D", boost::property_tree::ptree(Math::GetStringFromVec2(it->second))));
			ptree_data.push_back(boost::property_tree::ptree::value_type("Vec2", ptree_float_data));

		}

	}





	//Vec3 saving
	if (vec3_map.size() > 0)
	{

		std::map<std::string, glm::vec3>::iterator it;

		for (it = vec3_map.begin(); it != vec3_map.end(); it++)
		{
			boost::property_tree::ptree ptree_float_data;
			ptree_float_data.push_back(boost::property_tree::ptree::value_type("V", boost::property_tree::ptree(it->first)));
			ptree_float_data.push_back(boost::property_tree::ptree::value_type("D", boost::property_tree::ptree(Math::GetStringFromVec3(it->second))));
			ptree_data.push_back(boost::property_tree::ptree::value_type("Vec3", ptree_float_data));

		}

	}



	//Vec4 saving
	if (vec4_map.size() > 0)
	{

		std::map<std::string, glm::vec4>::iterator it;

		for (it = vec4_map.begin(); it != vec4_map.end(); it++)
		{
			boost::property_tree::ptree ptree_float_data;
			ptree_float_data.push_back(boost::property_tree::ptree::value_type("V", boost::property_tree::ptree(it->first)));
			ptree_float_data.push_back(boost::property_tree::ptree::value_type("D", boost::property_tree::ptree(Math::GetStringFromVec4(it->second))));
			ptree_data.push_back(boost::property_tree::ptree::value_type("Vec4", ptree_float_data));

		}

	}




	return ptree_data;


}