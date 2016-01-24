#include <stdafx.h>





ABoolean DataComponent::isValid(std::string extension)
{


	//See if valid extension


	if (!extension.compare(".adata"))
		return true;
	return false;


}




AVoid DataComponent::Load(std::string path, std::string extension)
{




	LoadInterface(AFile::GetPtree(path).get_child("Component"));





}




AVoid DataComponent::Init()
{





}



AVoid DataComponent::Clean()
{




}
