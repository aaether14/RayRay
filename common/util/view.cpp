#include <stdafx.h>





AVoid View::Create3rd(AFloat FoV, AFloat ratio, AFloat z_near, AFloat z_far, AFloat distance, glm::vec3 position, glm::vec3 direction, glm::vec3 up)
{

    ProjectionMatrix = glm::perspective(FoV, ratio, z_near, z_far);
    ViewMatrix = glm::lookAt(position-direction*distance, position, up);


}



AVoid View::Create3rd(ViewInfo*info)
{

    this->Create3rd(info->getFoV(),
                    info->getRatio(),
                    info->getNear(),
                    info->getRenderDistance(),
                    info->getDistance(),
                    info->getCameraPos(),
                    info->getDirection(),
                    info->getUpVec()
                    );


}

AVoid View::Create1st(AFloat FoV, AFloat ratio, AFloat z_near, AFloat z_far, glm::vec3 position, glm::vec3 direction, glm::vec3 up)
{


    ProjectionMatrix = glm::perspective(FoV, ratio, z_near, z_far);
    ViewMatrix = glm::lookAt(position, position + direction, up);


}


AVoid View::Create1st(ViewInfo * info)
{


    this->Create1st(info->getFoV(),
                    info->getRatio(),
                    info->getNear(),
                    info->getRenderDistance(),
                    info->getCameraPos(),
                    info->getDirection(),
                    info->getUpVec()
                    );


}


AVoid ViewInfo::Init()
{


    FoV = 60.0f;
    direction = glm::vec3(0.0f);
    distance = 50.0f;
    render_distance = 200.0f;
    position = glm::vec3(0.0f);


}






AVoid Frustum::Create(glm::mat4 MVP)
{


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




}






