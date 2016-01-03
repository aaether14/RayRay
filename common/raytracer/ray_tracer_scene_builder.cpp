#include <stdafx.h>




void RayTracerSceneBuilder::Init()
{






}





void RayTracerSceneBuilder::Clean()
{



	CleanModule();



}




void RayTracerSceneBuilder::Enable()
{



	scene_data.clear();







    //Required data
    size_t number_of_spheres = 3;
    size_t number_of_planes = 1;
    size_t number_of_materials = 6;
    size_t number_of_lights = 2;
    


    size_t pseudo_pointer = 0;
    pseudo_pointer+=5;


	//Pseudo pointers
	size_t starting_pointer = pseudo_pointer;
	scene_data.push_back(pseudo_pointer);






//Getting the pseudo pointers

	pseudo_pointer += number_of_spheres * 6;
	size_t sphere_pointer = pseudo_pointer;
	scene_data.push_back(sphere_pointer);


    
	pseudo_pointer += number_of_planes * 6;
	size_t plane_pointer = pseudo_pointer;
	scene_data.push_back(plane_pointer);



	pseudo_pointer += number_of_materials * 8;
	size_t material_pointer = pseudo_pointer;
	scene_data.push_back(material_pointer);



	pseudo_pointer += number_of_lights * 5;
	size_t light_pointer = pseudo_pointer;
	scene_data.push_back(light_pointer);




//Computing material map
    std::map<std::string, cl_uint> material_map;
    size_t material_counter = 0;




//Adding entities to scene pointer



	AddSphere(glm::vec4(1, -0.8f, 3, 0), 6.25, 0);
	AddSphere(glm::vec4(1, -0.5f, 7, 0), 4.0, 5);
	AddSphere(glm::vec4(-5.5f, -0.5f, 7, 0), 4.0, 1);
	AddPlane(glm::vec4(0.0, 1.0, 0.0, 0.0), -4.4, 2);
	AddMaterial(0.0, 1.1, 127.0, 0.1, glm::vec4(0.7f, 0.7f, 0.7f, 0));
	AddMaterial(1.0, 0.0, 120.0, 0.1, glm::vec4(0.7f, 0.7f, 1.0f, 0));
	AddMaterial(0.0, 0.0, 120.0, 1.0, glm::vec4(0.4f, 0.3f, 0.3f, 0));
	AddMaterial(0.0, 0.0, 120.0, 1.0, glm::vec4(0.4f, 0.4f, 0.4f, 0));
	AddMaterial(0.0, 0.0, 120.0, 1.0, glm::vec4(0.6f, 0.6f, 0.8f, 0));
	AddMaterial(0.0, 0.0, 120.0, 1.0, glm::vec4(0.3f, 1.0f, 0.4f, 0));
	AddLight(3, glm::vec4(0, 5, 5, 0));
	AddLight(4, glm::vec4(2, 5, 1, 0));


}




void RayTracerSceneBuilder::AddSphere(glm::vec4 pos, cl_float sq_dist, cl_uint mat)
{



	scene_data.push_back(pos.x);
	scene_data.push_back(pos.y);
	scene_data.push_back(pos.z);
	scene_data.push_back(pos.w);
	scene_data.push_back(sq_dist);
	scene_data.push_back(mat);



}




void RayTracerSceneBuilder::AddPlane(glm::vec4 normal, cl_float dist, cl_uint mat)
{


	scene_data.push_back(normal.x);
	scene_data.push_back(normal.y);
	scene_data.push_back(normal.z);
	scene_data.push_back(normal.w);
	scene_data.push_back(dist);
	scene_data.push_back(mat);



}



void RayTracerSceneBuilder::AddMaterial(cl_float relf, cl_float refr, cl_float spec, cl_float diff, glm::vec4 amb)
{


	scene_data.push_back(relf);
	scene_data.push_back(refr);
	scene_data.push_back(spec);
	scene_data.push_back(amb.r);
	scene_data.push_back(amb.g);
	scene_data.push_back(amb.b);
	scene_data.push_back(amb.a);
	scene_data.push_back(diff);



}



void RayTracerSceneBuilder::AddLight(cl_uint mat, glm::vec4 center)
{


	scene_data.push_back(center.x);
	scene_data.push_back(center.y);
	scene_data.push_back(center.z);
	scene_data.push_back(center.w);
	scene_data.push_back(mat);


}