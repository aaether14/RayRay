#ifndef RAY_TRACER_SCENE_BUILDER_HPP
#define RAY_TRACER_SCENE_BUILDER_HPP



#include <stdafx.h>





#define MATERIAL_DATA 7
#define SPHERE_DATA 5
#define BOX_DATA 7
#define PLANE_DATA 5
#define LIGHT_DATA 4






/**
Provdies functionality for building scene AFloat array from scene manager
*/
class RayTracerSceneBuilder : public AModule
{



    std::vector<cl_float> scene_data;




    /**
    Add sphere to scene
    */
    AVoid AddSphere(glm::vec3 pos, cl_float sq_dist, AUInt mat);
    /**
    Add box to scene
    */
    AVoid AddBox(glm::vec3 near_point, glm::vec3 far_point, AUInt mat);
    /**
    Add plane to scene
    */
    AVoid AddPlane(glm::vec3 normal, cl_float dist, AUInt mat);
    /**
    Add material to scene
    */
    AVoid AddMaterial(glm::vec3 amb, cl_float refl, cl_float refr, cl_float spec, cl_float diff);
    /**
    Add light to scene
    */
    AVoid AddLight(glm::vec3 center, AUInt mat);



public:




    /**
    Initailizes data
    */
    AVoid Init();
    /**
    Cleans data
    */
    AVoid Clean();
    /**
    Updates scene data
    */
    AVoid Enable();






    /**
    Clean scene data
    */
    inline AVoid CleanSceneData(){scene_data.clear();}
    /**
    Give scene data pointer
    */
    cl_float * GetSceneDataPointer(){ return &scene_data[0]; }
    /**
    Get scene size
    */
    size_t GetSceneSize(){ return sizeof(cl_float) * scene_data.size(); }








};





#endif
