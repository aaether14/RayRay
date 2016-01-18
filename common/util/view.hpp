#ifndef VIEW_HPP
#define VIEW_HPP




#include <stdafx.h>





/**
Storing info that can ve used by View to create view projection matrix
*/
class ViewInfo
{




    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 up;
    AFloat distance;
    AFloat render_distance;
    AFloat z_near;
    AFloat FoV;
    AFloat ratio;


public:

    inline ViewInfo() { this->Init(); }
    AVoid Init();





    /**
    Gets values of another ViewInfo
    */
    inline AVoid SetFromOther(ViewInfo * other)
    {
        this->position = other->getCameraPos();
        this->direction = other->getDirection();
        this->up = other->getUpVec();
        this->distance = other->getDistance();
        this->render_distance = other->getRenderDistance();
        this->z_near = other->getNear();
        this->FoV = other->getFoV();
        this->ratio = other->getRatio();

    }





    inline glm::vec3 getCameraPos() { return position; }
    inline AVoid setUpVec(glm::vec3 t_vec) { this->up = t_vec; }
    inline glm::vec3 getDirection() { return direction; }
    inline AFloat getRatio(){ return this->ratio; }
    inline AVoid setRatio(AFloat ratio) { this->ratio = ratio; }
    inline glm::vec3 getUpVec() { return this->up; }
    inline AFloat getNear() { return this->z_near; }
    inline AVoid setNear(AFloat _near) { this->z_near = _near; }
    inline AVoid SetRenderDistance(AFloat r_d) { this->render_distance = r_d; }
    inline AVoid SetCameraPos(glm::vec3 pos) { this->position = pos; }
    inline AVoid SetCameraY(AFloat y) { this->position.y = y; }
    inline AVoid SetDistance(AFloat new_distance) { this->distance = new_distance; }
    inline AVoid setDirection(glm::vec3 dir) { this->direction = dir; }
    inline AFloat getFoV() { return this->FoV; }
    inline AFloat getTanHalfFov(){ return tanf((FoV / 2.0f) * M_PI / 180.0); }
    inline AVoid setFov(AFloat FoV) { this->FoV = FoV; }
    inline AFloat getRenderDistance() { return this->render_distance; }
    inline AFloat getDistance() { return this->distance; }




};





/**
Using information from ViewInfo, this class creates a view projection matrix for world to camera to clipspace transformation
*/
class View
{


    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;



    /**
    Creates a 3rd person view from parameters
    */
    AVoid Create3rd(AFloat FoV, AFloat ratio, AFloat z_near, AFloat z_far, AFloat distance, glm::vec3 position, glm::vec3 direction, glm::vec3 up);
    /**
    Creates a 1st person view from parameters
    */
    AVoid Create1st(AFloat FoV, AFloat ratio, AFloat z_near, AFloat z_far, glm::vec3 position, glm::vec3 direction, glm::vec3 up);



public:



    /**
    Creates a 3rd person view from a ViewInfo
    */
    AVoid Create3rd(ViewInfo *info);
    /**
    Creates a 1st person view from a ViewInfo
    */
    AVoid Create1st(ViewInfo *info);
    /**
    Returns view matrix aka world matrix
    */
    inline glm::mat4 getViewMatrix() { return ViewMatrix; }
    /**
    Returns projection matrix aka camera matrix
    */
    inline glm::mat4 getProjectionMatrix() { return ProjectionMatrix; }
    /**
    Returns view projection matrix
    */
    inline glm::mat4 getCamera(){ return ProjectionMatrix*ViewMatrix; }
    /**
    Set projection
    */
    inline AVoid SetProjection(glm::mat4 ProjectionMatrix){ this->ProjectionMatrix = ProjectionMatrix; }
    /**
    Set view matrix
    */
    inline AVoid SetView(glm::mat4 ViewMatrix){ this->ViewMatrix = ViewMatrix; }



};







#endif
