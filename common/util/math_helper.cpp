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




	//----------------------------------------------------------------------//


	AUInt CylinderInFrustum(Frustum *frustum, glm::vec3 pos, AFloat radius)
	{


		AUInt p;
		AUInt c = 0;
		AFloat d;


		for (p = 0; p < 4; p++)
		{


            d = glm::dot(glm::vec3(frustum->getPlanes()[p]) , pos) + frustum->getPlanes()[p].w;
			if (d <= -radius)
				return 0;
			if (d > radius)
				c++;

		}


		return (c == 4) ? 2 : 1;



	}





	//----------------------------------------------------------------------//







}


