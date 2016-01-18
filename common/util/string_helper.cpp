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





//----------------------------------------------------------------------//




glm::vec2 GetVec2FromString(std::string str)
{


    AFloat * values = new AFloat[2];
    AInt number_of_floats;
    FloatArrayFromString(values, number_of_floats, str);


    glm::vec2 v;
    memcpy(&v[0], &values[0], number_of_floats * sizeof(AFloat));


    return v;


}


//-------------------------------------------------//


std::string GetStringFromVec2(glm::vec2 v)
{

    std::ostringstream stream;
    stream << v.x << ", " << v.y;
    return stream.str();

}



//------------------------------------------------//



glm::vec3 GetVec3FromString(std::string str)
{


    AFloat * values = new AFloat[3];
    AInt number_of_floats;
    FloatArrayFromString(values, number_of_floats, str);



    glm::vec3 v;
    memcpy(&v[0], &values[0], number_of_floats * sizeof(AFloat));


    return v;


}


//-------------------------------------------------//


std::string GetStringFromVec3(glm::vec3 v)
{

    std::ostringstream stream;
    stream << v.x << ", " << v.y << ", " << v.z;
    return stream.str();

}



//------------------------------------------------//



glm::vec4 GetVec4FromString(std::string str)
{


    AFloat * values = new AFloat[4];
    AInt number_of_floats;
    FloatArrayFromString(values, number_of_floats, str);


    glm::vec4 v;
    memcpy(&v[0], &values[0], number_of_floats * sizeof(AFloat));


    return v;


}



//--------------------------------------------------//



std::string GetStringFromVec4(glm::vec4 v)
{

    std::ostringstream stream;
    stream << v.x << ", " << v.y << ", " << v.z << ", " << v.w;
    return stream.str();

}




//-------------------------------------------------//



glm::mat4 GetMat4FromString(std::string str)
{

    AFloat * values = new AFloat[16];
    AInt number_of_floats;
    FloatArrayFromString(values, number_of_floats, str);


    glm::mat4 v;
    memcpy(&v[0], &values[0], number_of_floats * sizeof(AFloat));


    return v;

}


//-------------------------------------------------//



std::string GetStringFromMat4(glm::mat4 v)
{

    std::ostringstream stream;
    stream << v[0][0] << ", " << v[0][1] << ", " << v[0][2] << ", " << v[0][3] << std::endl;
    stream << v[1][0] << ", " << v[1][1] << ", " << v[1][2] << ", " << v[1][3] << std::endl;
    stream << v[2][0] << ", " << v[2][1] << ", " << v[2][2] << ", " << v[2][3] << std::endl;
    stream << v[3][0] << ", " << v[3][1] << ", " << v[3][2] << ", " << v[3][3] << std::endl;
    return stream.str();

}




//-------------------------------------------------//








}
