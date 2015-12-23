#include <stdafx.h>






void ResourceLoader::LoadResourcePaths(char *path)
{


	int i = 0;


	std::ifstream fin(path);
	std::string temp_str;




	std::string files[1];


	while (std::getline(fin,temp_str))
	{
		if (temp_str == "")continue;
		files[i] = temp_str;
		i++;
	}



	scene_file = files[0];



	fin.close();

}



void ResourceLoader::Init()
{


	Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));


	LoadResourcePaths(AString::char_to_str(ctrl->GetProjectName()));
	Add("Entities", new SceneInfo(AString::char_to_str(GetSceneFile())));
	LoadChanges();


}




void ResourceLoader::Clean()
{


	CleanModule();


}
