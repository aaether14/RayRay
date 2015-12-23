#include <stdafx.h>





bool DataComponent::isValid(std::string extension)
{


	//See if valid extension


	if (!extension.compare(".adata"))
		return true;
	return false;


}




void DataComponent::Load(std::string path, std::string extension)
{




	LoadInterface(AFile::GetPtree(path).get_child("Component"));





}




void DataComponent::Init()
{





}



void DataComponent::Clean()
{


	AData::Clean();



}
