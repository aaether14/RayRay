#ifndef FILE_HELPER_HPP
#define FILE_HELPER_HPP




#include <stdafx.h>







/**


Using Templates for easier binary data storing/loading
Also provides tools for directory copying


*/
namespace AFile
{




	template <class T>
	/**
	Writes anytype of data to binary file
	*/
	inline AVoid WriteToFile(std::ofstream& os, const T& obj){ os.write((const AChar*)&(obj), sizeof(T)); }
	template <class T>
	/**
	Reads anytype of data from binary file
	*/
	inline AVoid ReadFromFile(std::ifstream& is, const T& obj){ is.read((AChar*)&(obj), sizeof(T)); }


	/**
	Copy folder from a location to another. Returns true if succesful
	*/
    ABoolean CopyDirectory(
		boost::filesystem::path const & source,
		boost::filesystem::path const & destination
		);


	/**
    If in the folder specified by 'path' exists a file that has 'extension' return path of that file. Returns NULL otherwise
	*/
    boost::optional<std::string> GetFileWithExtension(std::string path, std::string extension);
	/**
	Same as GetFileWithExtension but for multiple extensions
	*/
    boost::optional<std::string> GetFileWithExtensionList(std::string path, std::vector<std::string>extensions);


	/**
	Return size of file
	*/
    ALong GetFileSize(const AChar* filePath);
	/**
	Read file content into memory and return pointer
	*/
	AUChar * ReadFile(const AChar * filePath);
	/**
	Encrypt file from 'path' using Blowfish algorithm
	*/
	AVoid BlowfishEncryptFile(const AChar * path);
	/**
	Get decrytpted file from 'path' to string using Blowfish algorithm
	*/
	std::string BlowfishDecryptFile(const AChar * path);
	/**
	Get ptree from xml
	*/
	boost::property_tree::ptree GetPtree(std::string path);
	/**
	Save ptree to xml
	*/
	AVoid SavePtree(std::string path, boost::property_tree::ptree ptree);


}




#endif
