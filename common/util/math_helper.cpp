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


AUInt CylinderInFrustum(std::vector<glm::vec4> planes, glm::vec3 pos, AFloat radius)
{


    AUInt p;
    AUInt c = 0;
    AFloat d;


    for (p = 0; p < 4; p++)
    {


        d = glm::dot(glm::vec3(planes[p]) , pos) + planes[p].w;
        if (d <= -radius)
            return 0;
        if (d > radius)
            c++;

    }


    return (c == 4) ? 2 : 1;



}





//----------------------------------------------------------------------//




std::vector<glm::vec4> GetFrustumPlanes(glm::mat4 MVP)
{


    std::vector<glm::vec4> planes;
    planes.resize(6);


    //LEFT


    planes[0].x = MVP[0].w - MVP[0].x;
    planes[0].y = MVP[1].w - MVP[1].x;
    planes[0].z = MVP[2].w - MVP[2].x;
    planes[0].w = MVP[3].w - MVP[3].x;

    planes[0] = Math::NormalizePlane(planes[0]);


    //RIGHT

    planes[1].x = MVP[0].w + MVP[0].x;
    planes[1].y = MVP[1].w + MVP[1].x;
    planes[1].z = MVP[2].w + MVP[2].x;
    planes[1].w = MVP[3].w + MVP[3].x;



    planes[1] = Math::NormalizePlane(planes[1]);


    //TOP


    planes[4].x = MVP[0].w + MVP[0].y;
    planes[4].y = MVP[1].w + MVP[1].y;
    planes[4].z = MVP[2].w + MVP[2].y;
    planes[4].w = MVP[3].w + MVP[3].y;



    planes[4] = Math::NormalizePlane(planes[4]);



    //BOTTOM

    planes[5].x = MVP[0].w - MVP[0].y;
    planes[5].y = MVP[1].w - MVP[1].y;
    planes[5].z = MVP[2].w - MVP[2].y;
    planes[5].w = MVP[3].w - MVP[3].y;


    planes[5] = Math::NormalizePlane(planes[5]);


    //FAR

    planes[2].x = MVP[0].w - MVP[0].z;
    planes[2].y = MVP[1].w - MVP[1].z;
    planes[2].z = MVP[2].w - MVP[2].z;
    planes[2].w = MVP[3].w - MVP[3].z;



    planes[2] = Math::NormalizePlane(planes[2]);


    //NEAR


    planes[3].x = MVP[0].w + MVP[0].z;
    planes[3].y = MVP[1].w + MVP[1].z;
    planes[3].z = MVP[2].w + MVP[2].z;
    planes[3].w = MVP[3].w + MVP[3].z;



    planes[3] = Math::NormalizePlane(planes[3]);



    return planes;




}




//-------------------------------------------//




}


