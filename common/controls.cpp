#include <stdafx.h>







AVoid Controller::Init()
{




    ControllerSource::Init();
    boost::property_tree::ptree pt = AFile::GetPtree(AAETHER_SYSTEM_FOLDER"settings.xml");





	BOOST_FOREACH(boost::property_tree::ptree::value_type const& v, pt.get_child("GeneralInfo"))
	{




		if (v.first == "BaseInfo")
		{


			AUInt window_width = v.second.get<GLuint>("WindowWidth");
			AUInt window_height = v.second.get<GLuint>("WindowHeight");
			std::string window_title = v.second.get<std::string>("WindowTitle");
			ABoolean fullscreen = v.second.get<GLboolean>("Fullscreen");
			AUInt opengl_major_version = v.second.get<GLuint>("OpenGLMajorVersion");
			AUInt opengl_minor_version = v.second.get<GLuint>("OpenGLMinorVersion");
            GetControllerData()->Set("ProjectName", v.second.get<std::string>("ProjectName"));




			CreateWindowContext(window_width, window_height, fullscreen, window_title, opengl_major_version, opengl_minor_version);
			Add("Camera", new Camera());






		}
        else if (v.first == "OpenCLInfo")
        {
            GetControllerData()->Set("OpenCLPlatform", v.second.get<std::string>("OpenCLPlatform"));
            GetControllerData()->Set("OpenCLDevice", v.second.get<std::string>("OpenCLDevice"));
            GetControllerData()->Set("IsOpenCLEnabled", v.second.get<GLboolean>("Enable"));
            GetControllerData()->Set("LinkOpenGLContext", v.second.get<GLboolean>("LinkOpenGLContext"));
        }
		



	}





	

}





AVoid Controller::Clean()
{

	
	CleanModule();
	ControllerSource::Clean();


}






AVoid Controller::Enable()
{



	ControllerSource::Enable();
    Get("Camera")->Enable();




}
