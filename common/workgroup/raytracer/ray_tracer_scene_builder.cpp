#include <stdafx.h>




void RayTracerSceneBuilder::Init()
{






}





void RayTracerSceneBuilder::Clean()
{



    CleanSceneData();
    CleanModule();



}




void RayTracerSceneBuilder::Enable()
{




    //First clear what ever data scene has
    CleanSceneData();






    //Inspect objects in the scene

    std::vector<AData*> materials;
    std::vector<AData*> spheres;
    std::vector<AData*> planes;
    std::vector<AData*> lights;







    InstanceCollection * instances = static_cast<InstanceCollection*>(GetManager()->Get("DataManager")->Get("Resources")->Get("Instances"));
    std::pair<std::string, boost::shared_ptr<EntityInstance> > entity_instance_iterator;
    BOOST_FOREACH(entity_instance_iterator, *instances->GetInstanceMapPointer())
    {
        std::pair<std::string, boost::shared_ptr<AData> > instance_adata_iterator;
        BOOST_FOREACH(instance_adata_iterator, *entity_instance_iterator.second->GetADatasMapPointer())
        {


            if (!instance_adata_iterator.second->GetComponentName().compare("Material"))
                materials.push_back(instance_adata_iterator.second.get());
            if (!instance_adata_iterator.second->GetComponentName().compare("Sphere"))
            {
                spheres.push_back(instance_adata_iterator.second.get());
                spheres.push_back(entity_instance_iterator.second->GetAData("DataComponent_Transform"));
            }
            if (!instance_adata_iterator.second->GetComponentName().compare("Plane"))
                planes.push_back(instance_adata_iterator.second.get());
            if (!instance_adata_iterator.second->GetComponentName().compare("Light"))
                lights.push_back(instance_adata_iterator.second.get());


        }

    }



    




    //Compute some pseudo pointers holding scene data location of each object type

    size_t pseudo_pointer = 0;
    pseudo_pointer+=5;
    scene_data.push_back(pseudo_pointer);


    pseudo_pointer += materials.size() * MATERIAL_DATA;
    size_t material_pointer = pseudo_pointer;
    scene_data.push_back(material_pointer);


    pseudo_pointer += (spheres.size() / 2) * SPHERE_DATA;
    size_t sphere_pointer = pseudo_pointer;
    scene_data.push_back(sphere_pointer);


    
    pseudo_pointer += planes.size() * PLANE_DATA;
    size_t plane_pointer = pseudo_pointer;
    scene_data.push_back(plane_pointer);



    pseudo_pointer += lights.size() * LIGHT_DATA;
    size_t light_pointer = pseudo_pointer;
    scene_data.push_back(light_pointer);








    //Adding entities to scene pointer



    std::map<std::string, cl_uint> material_indices;



    for (int i = 0; i < materials.size(); i++)
    {
        AddMaterial(materials[i]->GetVec3("Ambient"), materials[i]->GetFloat("Reflectivity"),
                    materials[i]->GetFloat("Refractivity"), materials[i]->GetFloat("Specularity"),
                    materials[i]->GetFloat("Diffuse"));
        material_indices.insert(std::pair<std::string, cl_uint>(materials[i]->GetString("MaterialName"),i));
    }
    for (int i = 0; i < spheres.size(); i += 2)
    {
        AddSphere(spheres[i]->GetVec3("SpherePosition") + spheres[i + 1]->GetVec3("Position"),
                spheres[i]->GetFloat("SphereRadius"),
                  material_indices[spheres[i]->GetString("MaterialName")]);
    }
    for (int i = 0; i < planes.size(); i++)
    {
        AddPlane(planes[i]->GetVec3("PlaneNormal"), planes[i]->GetFloat("PlaneDistance"),
                 material_indices[planes[i]->GetString("MaterialName")]);
    }
    for (int i = 0; i < lights.size(); i++)
    {
        AddLight(lights[i]->GetVec3("LightPosition"), material_indices[lights[i]->GetString("MaterialName")]);
    }




}




void RayTracerSceneBuilder::AddSphere(glm::vec3 pos, cl_float sq_dist, cl_uint mat)
{



    scene_data.push_back(pos.x);
    scene_data.push_back(pos.y);
    scene_data.push_back(pos.z);
    scene_data.push_back(sq_dist);
    scene_data.push_back(mat);



}




void RayTracerSceneBuilder::AddPlane(glm::vec3 normal, cl_float dist, cl_uint mat)
{


    scene_data.push_back(normal.x);
    scene_data.push_back(normal.y);
    scene_data.push_back(normal.z);
    scene_data.push_back(dist);
    scene_data.push_back(mat);



}



void RayTracerSceneBuilder::AddMaterial(glm::vec3 amb, cl_float refl, cl_float refr, cl_float spec, cl_float diff)
{



    scene_data.push_back(amb.r);
    scene_data.push_back(amb.g);
    scene_data.push_back(amb.b);
    scene_data.push_back(refl);
    scene_data.push_back(refr);
    scene_data.push_back(spec);
    scene_data.push_back(diff);



}



void RayTracerSceneBuilder::AddLight(glm::vec3 center, cl_uint mat)
{


    scene_data.push_back(center.x);
    scene_data.push_back(center.y);
    scene_data.push_back(center.z);
    scene_data.push_back(mat);


}




















