#include <stdafx.h>




namespace AString
{


	std::string LoadFileToString(std::string path)
	{

		std::string result;
		std::ifstream FileStream(path, std::ios::in);

		if (FileStream.is_open())
		{


			std::string Line = "";
			while (getline(FileStream, Line))
				result += "\n" + Line;
			FileStream.close();


			return result;


		}
		else
		{
			std::cerr<<"Imposible to open:" << path << std::endl;
			return "ERROR";
		}


	}





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
			code.insert(f_pos, AString::LoadFileToString(t_file));
			pos = code.find(first_delimiter, f_pos + 1);


		}


		
		return code;


	}




    //--------------------------------------------------------//



    void print_matrix(glm::mat4 m)
    {


        printf("%1.2f, %1.2f, %1.2f, %1.2f,\n%1.2f, %1.2f, %1.2f, %1.2f,\n%1.2f, %1.2f, %1.2f, %1.2f,\n%1.2f, %1.2f, %1.2f, %1.2f\n\n",
            m[0][0], m[0][1], m[0][2], m[0][3],
            m[1][0], m[1][1], m[1][2], m[1][3],
            m[2][0], m[2][1], m[2][2], m[2][3],
            m[3][0], m[3][1], m[3][2], m[3][3]
            );

    }



    //----------------------------------------------------------//



    void print_vec2(glm::vec2 v)
    {



        std::cout << v.x << ", " << v.y << std::endl;



    }



    //----------------------------------------------------------//




    void print_vec3(glm::vec3 v)
    {


        std::cout << v.x << ", " << v.y << ", " << v.z << std::endl;


    }



    //--------------------------------------------------------//



    void print_vec4(glm::vec4 v)
    {


        std::cout << v.x << ", " << v.y << ", " << v.z << ", " << v.w << std::endl;


    }




    void FloatArrayFromString(GLfloat * _array, GLint &number_of_floats, std::string str)
    {



        std::string delimeter = ", ";
        GLint k = 0;



        size_t pos = 0;
        std::string token;
        while ((pos = str.find(delimeter)) != std::string::npos) {
            token = str.substr(0, pos);
            _array[k++] = boost::lexical_cast<float>(token);
            str.erase(0, pos + delimeter.length());
        }


        _array[k++] = boost::lexical_cast<float>(str);
        number_of_floats = k;



    }





    //----------------------------------------------------------------------//




    glm::vec2 GetVec2FromString(std::string str)
    {


        GLfloat * values = new GLfloat[2];
        GLint number_of_floats;
        FloatArrayFromString(values, number_of_floats, str);


        glm::vec2 v;
        memcpy(&v[0], &values[0], number_of_floats * sizeof(GLfloat));


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


        GLfloat * values = new GLfloat[3];
        GLint number_of_floats;
        FloatArrayFromString(values, number_of_floats, str);



        glm::vec3 v;
        memcpy(&v[0], &values[0], number_of_floats * sizeof(GLfloat));


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


        GLfloat * values = new GLfloat[4];
        GLint number_of_floats;
        FloatArrayFromString(values, number_of_floats, str);


        glm::vec4 v;
        memcpy(&v[0], &values[0], number_of_floats * sizeof(GLfloat));


        return v;


    }



    //--------------------------------------------------//



    std::string GetStringFromVec4(glm::vec4 v)
    {

        std::ostringstream stream;
        stream << v.x << ", " << v.y << ", " << v.z << ", " << v.w;
        return stream.str();

    }






}
