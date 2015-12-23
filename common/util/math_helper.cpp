#include <stdafx.h>




namespace Math
{



	glm::mat4 Translation(glm::vec3 t_vec)
	{


		glm::mat4 tr_matrix(1.0f);
		tr_matrix[3] = glm::vec4(t_vec, 1.0);
		return tr_matrix;


	}


	//------------------------------------------------------------//



	glm::mat4 Scale(glm::vec3 t_vec)
	{



		glm::mat4 tr_matrix(1.0f);
		tr_matrix[0][0] = t_vec.x;
		tr_matrix[1][1] = t_vec.y;
		tr_matrix[2][2] = t_vec.z;
		return tr_matrix;



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




	//----------------------------------------------------------------------//


	GLuint CylinderInFrustum(Frustum *frustum, glm::vec3 pos, GLfloat radius)
	{


		GLuint p;
		GLuint c = 0;
		GLfloat d;


		for (p = 0; p < 4; p++)
		{


			d = glm::dot(frustum->getPlanes()[p].normal, pos) + frustum->getPlanes()[p].distance;
			if (d <= -radius)
				return 0;
			if (d > radius)
				c++;

		}


		return (c == 4) ? 2 : 1;



	}





	//----------------------------------------------------------------------//




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


