#include <stdafx.h>





namespace AFile
{




    ABoolean CopyDirectory(boost::filesystem::path const & source, boost::filesystem::path const & destination)
	{

		try
		{



            if (!boost::filesystem::exists(source) || !boost::filesystem::is_directory(source))
			{
				std::cerr << "Source directory " << source.string()
                    << " does not exist or is not a directory." << std::endl;
				return false;
			}
            if (boost::filesystem::exists(destination))
			{
				std::cerr << "Destination directory " << destination.string()
                    << " already exists." << std::endl;
				return false;
			}




            if (!boost::filesystem::create_directory(destination))
			{
				std::cerr << "Unable to create destination directory"
                    << destination.string() << std::endl;
				return false;
			}





		}
        catch (boost::filesystem::filesystem_error const & e)
		{
            std::cerr << e.what() << std::endl;
			return false;
		}



        for (boost::filesystem::directory_iterator file(source); file != boost::filesystem::directory_iterator(); ++file)
		{


			try
			{


                boost::filesystem::path current(file->path());
                if (boost::filesystem::is_directory(current))
				{


                    if (!CopyDirectory(current, destination / current.filename()))
					{
						return false;
					}



				}
				else
				{
                    boost::filesystem::copy_file(current, destination / current.filename());
				}
			}
            catch (boost::filesystem::filesystem_error const & e)
			{
                std::cerr << e.what() << std::endl;
			}



		}
		return true;




	}






    boost::optional<std::string> GetFileWithExtension(std::string path, std::string extension)
	{


		boost::filesystem::directory_iterator iterator(path);
		for (; iterator != boost::filesystem::directory_iterator(); ++iterator)
			if (boost::filesystem::is_regular_file(iterator->path()))
			{
			std::string file_extension = boost::filesystem::extension(iterator->path());
			std::transform(file_extension.begin(), file_extension.end(), file_extension.begin(), ::tolower);
			if (!extension.compare(file_extension))
                return boost::optional<std::string>(iterator->path().string());
			}

        return boost::optional<std::string>();


	}





    boost::optional<std::string> GetFileWithExtensionList(std::string path, std::vector<std::string>extensions)
	{

		for (AUInt i = 0; i < extensions.size(); i++)
            if (GetFileWithExtension(path, extensions[i]))
			return GetFileWithExtension(path, extensions[i]);


        return boost::optional<std::string>();

	}









	boost::property_tree::ptree GetPtree(std::string path)
	{


		using boost::property_tree::ptree;
		ptree pt;
		read_xml(path, pt);

		
		return pt;


	}






	AVoid SavePtree(std::string path, boost::property_tree::ptree ptree)
	{


		boost::property_tree::xml_writer_settings<AChar> settings(' ', 4);
		write_xml(path, ptree, std::locale(), settings);


	}





}


