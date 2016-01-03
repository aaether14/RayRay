#include <stdafx.h>






void ResourceLoader::LoadResourcePaths(std::string path)
{


	int counter = 0;



	std::ifstream fin(path);
	std::string temp_str;
	std::string files[1];




	while (std::getline(fin,temp_str))
	{
		if (temp_str == "")continue;
		files[counter++] = temp_str;
	}





	scene_file = files[0];
	fin.close();

}



void ResourceLoader::Init()
{



	Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));


	LoadResourcePaths(ctrl->GetProjectName());
	Add("Entities", new SceneInfo(GetSceneFile()));
	LoadChanges();



}




void ResourceLoader::Clean()
{


	CleanModule();


}
