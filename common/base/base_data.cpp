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
        if (v.first == "String")
            SetString(v.second.get<std::string>("V"), v.second.get<std::string>("D"));
        if (v.first == "Vec2")
            SetVec2(v.second.get<std::string>("V"), AString::GetVec2FromString(v.second.get<std::string>("D")));
        if (v.first == "Vec3")
            SetVec3(v.second.get<std::string>("V"), AString::GetVec3FromString(v.second.get<std::string>("D")));
        if (v.first == "Vec4")
            SetVec4(v.second.get<std::string>("V"), AString::GetVec4FromString(v.second.get<std::string>("D")));



    }




    //Debug();



}




void AData::Debug()
{




    std::cout << "\n\nPrinting debug for: " << GetComponentName() << std::endl;




    //Float debug
    if (float_map.size() > 0)
    {
        std::cout << std::endl;
        std::cout << "Floats:" << std::endl;
        std::pair<std::string, GLfloat> it;


        BOOST_FOREACH(it, float_map)
                std::cout << it.first << ": " << it.second << std::endl;
    }





    //Int debug
    if (int_map.size() > 0)
    {
        std::cout << std::endl;
        std::cout << "Integers:" << std::endl;
        std::pair<std::string, GLint> it;


        BOOST_FOREACH(it, int_map)
                std::cout << it.first << ": " << it.second << std::endl;
    }



    //String debug
    if (string_map.size() > 0)
    {
        std::cout << std::endl;
        std::cout << "Strings:" << std::endl;
        std::pair<std::string, std::string> it;


        BOOST_FOREACH(it, string_map)
                std::cout << it.first << ": " << it.second << std::endl;
    }




    //Vec2 debug
    if (vec2_map.size() > 0)
    {
        std::cout << std::endl;
        std::cout << "Vec2:" << std::endl;
        std::pair<std::string, glm::vec2> it;


        BOOST_FOREACH(it, vec2_map)
        {
            std::cout << it.first << ": ";
            std::cout<<AString::GetStringFromVec2(it.second)<<std::endl;
        }


    }



    //Vec3 debug
    if (vec3_map.size() > 0)
    {
        std::cout << std::endl;
        std::cout << "Vec3:" << std::endl;
        std::pair<std::string, glm::vec3> it;


        BOOST_FOREACH(it, vec3_map)
        {
            std::cout << it.first << ": ";
            std::cout<<AString::GetStringFromVec3(it.second)<<std::endl;
        }


    }



    //Vec4 debug
    if (vec4_map.size() > 0)
    {
        std::cout << std::endl;
        std::cout << "Vec4:" << std::endl;
        std::pair<std::string, glm::vec4> it;


        BOOST_FOREACH(it, vec4_map)
        {
            std::cout << it.first << ": ";
            std::cout<<AString::GetStringFromVec4(it.second)<<std::endl;
        }


    }





}





void AData::Clean()
{


    int_map.clear();
    float_map.clear();
    string_map.clear();
    vec2_map.clear();
    vec3_map.clear();
    vec4_map.clear();



}





boost::property_tree::ptree AData::Save()
{


    boost::property_tree::ptree ptree_data;




    boost::property_tree::ptree ptree_general_info;
    ptree_general_info.push_back(boost::property_tree::ptree::value_type("Name", boost::property_tree::ptree(GetComponentName())));
    ptree_data.push_back(boost::property_tree::ptree::value_type("GeneralInfo", ptree_general_info));




    //Float saving
    if (float_map.size() > 0)
    {

        std::pair<std::string, GLfloat> it;

        BOOST_FOREACH(it, float_map)
        {
            boost::property_tree::ptree ptree_float_data;
            ptree_float_data.push_back(boost::property_tree::ptree::value_type("V", boost::property_tree::ptree(it.first)));
            ptree_float_data.push_back(boost::property_tree::ptree::value_type("D", boost::property_tree::ptree(boost::lexical_cast<std::string>(it.second))));
            ptree_data.push_back(boost::property_tree::ptree::value_type("Float", ptree_float_data));

        }

    }





    //Int saving
    if (int_map.size() > 0)
    {

        std::pair<std::string, GLint> it;

        BOOST_FOREACH(it, int_map)
        {
            boost::property_tree::ptree ptree_float_data;
            ptree_float_data.push_back(boost::property_tree::ptree::value_type("V", boost::property_tree::ptree(it.first)));
            ptree_float_data.push_back(boost::property_tree::ptree::value_type("D", boost::property_tree::ptree(boost::lexical_cast<std::string>(it.second))));
            ptree_data.push_back(boost::property_tree::ptree::value_type("Int", ptree_float_data));

        }

    }



    //String saving
    if (string_map.size() > 0)
    {

        std::pair<std::string, std::string> it;

        BOOST_FOREACH(it, string_map)
        {
            boost::property_tree::ptree ptree_float_data;
            ptree_float_data.push_back(boost::property_tree::ptree::value_type("V", boost::property_tree::ptree(it.first)));
            ptree_float_data.push_back(boost::property_tree::ptree::value_type("D", boost::property_tree::ptree(it.second)));
            ptree_data.push_back(boost::property_tree::ptree::value_type("String", ptree_float_data));

        }

    }



    //Vec2 saving
    if (vec2_map.size() > 0)
    {

        std::pair<std::string, glm::vec2> it;

        BOOST_FOREACH(it, vec2_map)
        {
            boost::property_tree::ptree ptree_float_data;
            ptree_float_data.push_back(boost::property_tree::ptree::value_type("V", boost::property_tree::ptree(it.first)));
            ptree_float_data.push_back(boost::property_tree::ptree::value_type("D", boost::property_tree::ptree(AString::GetStringFromVec2(it.second))));
            ptree_data.push_back(boost::property_tree::ptree::value_type("Vec2", ptree_float_data));

        }

    }





    //Vec3 saving
    if (vec3_map.size() > 0)
    {

        std::pair<std::string, glm::vec3> it;

        BOOST_FOREACH(it, vec3_map)
        {
            boost::property_tree::ptree ptree_float_data;
            ptree_float_data.push_back(boost::property_tree::ptree::value_type("V", boost::property_tree::ptree(it.first)));
            ptree_float_data.push_back(boost::property_tree::ptree::value_type("D", boost::property_tree::ptree(AString::GetStringFromVec3(it.second))));
            ptree_data.push_back(boost::property_tree::ptree::value_type("Vec3", ptree_float_data));

        }

    }



    //Vec4 saving
    if (vec4_map.size() > 0)
    {

        std::pair<std::string, glm::vec4> it;

        BOOST_FOREACH(it, vec4_map)
        {
            boost::property_tree::ptree ptree_float_data;
            ptree_float_data.push_back(boost::property_tree::ptree::value_type("V", boost::property_tree::ptree(it.first)));
            ptree_float_data.push_back(boost::property_tree::ptree::value_type("D", boost::property_tree::ptree(AString::GetStringFromVec4(it.second))));
            ptree_data.push_back(boost::property_tree::ptree::value_type("Vec4", ptree_float_data));

        }

    }




    return ptree_data;


}
