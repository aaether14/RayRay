#ifndef RAY_TRACER_SCENE_BUILDER_HPP
#define RAY_TRACER_SCENE_BUILDER_HPP



#include <stdafx.h>





#define MATERIAL_DATA 7
#define SPHERE_DATA 5
#define BOX_DATA 7
#define PLANE_DATA 5
#define LIGHT_DATA 4






/**
Provdies functionality for building scene float array from scene manager
*/
class RayTracerSceneBuilder : public AModule
{



    std::vector<cl_float> scene_data;




    /**
    Add sphere to scene
    */
    void AddSphere(glm::vec3 pos, cl_float sq_dist, cl_uint mat);
    /**
    Add box to scene
    */
    void AddBox(glm::vec3 near_point, glm::vec3 far_point, cl_uint mat);
    /**
    Add plane to scene
    */
    void AddPlane(glm::vec3 normal, cl_float dist, cl_uint mat);
    /**
    Add material to scene
    */
    void AddMaterial(glm::vec3 amb, cl_float refl, cl_float refr, cl_float spec, cl_float diff);
    /**
    Add light to scene
    */
    void AddLight(glm::vec3 center, cl_uint mat);



public:




    /**
    Initailizes data
    */
    void Init();
    /**
    Cleans data
    */
    void Clean();
    /**
    Updates scene data
    */
    void Enable();






    /**
    Clean scene data
    */
    inline void CleanSceneData(){scene_data.clear();}
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
