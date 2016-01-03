#include <stdafx.h>




namespace AString
{


	std::string LoadFileToString(std::string path)
	{

		std::string result;
		std::ifstream FileStream(path, std::ios::in);

		if (FileStream.is_open()){


			std::string Line = "";
			while (getline(FileStream, Line))
				result += "\n" + Line;
			FileStream.close();


			return result;


		}
		else
		{
			std::cerr<<"Imposible to open:" << path << std::endl;
			return "ERROR";
		}


	}








}