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





