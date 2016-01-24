#include <stdafx.h>




AVoid AData::LoadInterface(boost::property_tree::ptree base_index)
{




    BOOST_FOREACH(auto v, base_index)
    {


        if (v.first == "GeneralInfo")
            Set("__name__", v.second.get<std::string>("Name"));



        if (v.first == "Float")
            Set(v.second.get<std::string>("V"), boost::lexical_cast<AFloat>(v.second.get<std::string>("D")));
        if (v.first == "Int")
            Set(v.second.get<std::string>("V"), boost::lexical_cast<AInt>(v.second.get<std::string>("D")));
        if (v.first == "String")
            Set(v.second.get<std::string>("V"), v.second.get<std::string>("D"));
        if (v.first == "Vec2")
            Set(v.second.get<std::string>("V"), AString::GetFloatArrayFromString<glm::vec2>(v.second.get<std::string>("D")));
        if (v.first == "Vec3")
            Set(v.second.get<std::string>("V"), AString::GetFloatArrayFromString<glm::vec3>(v.second.get<std::string>("D")));
        if (v.first == "Vec4")
            Set(v.second.get<std::string>("V"), AString::GetFloatArrayFromString<glm::vec4>(v.second.get<std::string>("D")));



    }




    Debug();



}




AVoid AData::Debug()
{




    std::cout << "\n\nPrinting debug for: " << Get<std::string>("__name__") << std::endl;
    std::string debug_info = boost::python::extract<std::string>(boost::python::str(data_dictionary));
    std::cout << debug_info << std::endl;



}








boost::property_tree::ptree AData::Save()
{


    boost::property_tree::ptree ptree_data;
    return ptree_data;


}






template <class T>
T AData::Get(std::string key)
{

    return boost::python::extract<T>(data_dictionary[key]);

}
template AFloat AData::Get(std::string key);
template ADouble AData::Get(std::string key);
template AInt AData::Get(std::string key);
template AUInt AData::Get(std::string key);
template ABoolean AData::Get(std::string key);
template AUChar AData::Get(std::string key);
template std::string AData::Get(std::string key);
template glm::vec2 AData::Get(std::string key);
template glm::vec3 AData::Get(std::string key);
template glm::vec4 AData::Get(std::string key);
template glm::mat4 AData::Get(std::string key);





template <class T>
AVoid AData::Set(std::string key, T value)
{


    data_dictionary[key] = value;


}
template AVoid AData::Set(std::string key, AFloat value);
template AVoid AData::Set(std::string key, ADouble value);
template AVoid AData::Set(std::string key, AInt value);
template AVoid AData::Set(std::string key, AUInt value);
template AVoid AData::Set(std::string key, ABoolean value);
template AVoid AData::Set(std::string key, AUChar value);
template AVoid AData::Set(std::string key, std::string value);
template AVoid AData::Set(std::string key, glm::vec2 value);
template AVoid AData::Set(std::string key, glm::vec3 value);
template AVoid AData::Set(std::string key, glm::vec4 value);
template AVoid AData::Set(std::string key, glm::mat4 value);















