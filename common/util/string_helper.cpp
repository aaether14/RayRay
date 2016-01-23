#include <stdafx.h>




namespace AString
{






boost::optional<std::string> LoadFileToString(std::string path)
{

    std::string result;
    std::ifstream FileStream(path, std::ios::in);

    if (FileStream.is_open())
    {


        std::string Line = "";
        while (getline(FileStream, Line))
            result += "\n" + Line;
        FileStream.close();


        return boost::optional<std::string>(result);


    }
    else
    {
        std::cerr<<"Imposible to open:" << path << std::endl;
        return boost::optional<std::string>();
    }


}




//----------------------------------------------------//






std::string ManageDirective(std::string path, std::string code, std::string first_delimiter, std::string second_delimiter)
{



    size_t pos = code.find(first_delimiter, 0);


    while (pos != std::string::npos)
    {


        size_t f_pos = pos;
        size_t t_pos = code.find(second_delimiter, pos + 1);
        pos = code.find(second_delimiter, t_pos + 1);

        std::string t_file = path.substr(0, path.find_last_of("//") + 1) + code.substr(t_pos + 1, pos - (t_pos + 1));
        code.erase(f_pos, pos - f_pos + 1);
        code.insert(f_pos, AString::LoadFileToString(t_file).get());
        pos = code.find(first_delimiter, f_pos + 1);


    }



    return code;


}




//--------------------------------------------------------//





AVoid FloatArrayFromString(AFloat * _array, AInt &number_of_floats, std::string str)
{



    std::string delimeter = ", ";
    AInt k = 0;



    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimeter)) != std::string::npos) {
        token = str.substr(0, pos);
        _array[k++] = boost::lexical_cast<AFloat>(token);
        str.erase(0, pos + delimeter.length());
    }


    _array[k++] = boost::lexical_cast<AFloat>(str);
    number_of_floats = k;



}








//-------------------------------------------------//





template <class T>
T GetFloatArrayFromString(std::string str)
{

    AInt number_of_floats = sizeof(T) / sizeof(AFloat);
    AFloat * float_array = new AFloat[number_of_floats];
    FloatArrayFromString(float_array, number_of_floats, str);


    T array_to_return;
    memcpy(&array_to_return, &float_array[0], sizeof(T));
    delete [] float_array;



    return array_to_return;


}
template glm::vec2 GetFloatArrayFromString(std::string str);
template glm::vec3 GetFloatArrayFromString(std::string str);
template glm::vec4 GetFloatArrayFromString(std::string str);
template glm::mat4 GetFloatArrayFromString(std::string str);





//-------------------------------------------------//



template <class T>
std::string GetStringFromFloatArray(T float_array)
{


    AInt number_of_floats = sizeof(T) / sizeof(AFloat);
    AFloat * temporary_float_array = new AFloat[number_of_floats];
    memcpy(temporary_float_array, &float_array[0], sizeof(T));


    std::string string_to_return;
    for (AInt i = 0; i < number_of_floats - 1; i++)
    {
        string_to_return += boost::lexical_cast<std::string>(temporary_float_array[i]);
        string_to_return += ", ";
    }
    string_to_return += boost::lexical_cast<std::string>(temporary_float_array[number_of_floats - 1]);



    delete [] temporary_float_array;
    return string_to_return;




}
template std::string GetStringFromFloatArray(glm::vec2 float_array);
template std::string GetStringFromFloatArray(glm::vec3 float_array);
template std::string GetStringFromFloatArray(glm::vec4 float_array);
template std::string GetStringFromFloatArray(glm::mat4 float_array);





//--------------------------------------------------//




}
