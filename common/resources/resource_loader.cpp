#include <stdafx.h>







AVoid ResourceLoader::Init()
{



    Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
    LoadProject(ctrl->GetControllerData()->Get<std::string>("ProjectName"));




}




AVoid ResourceLoader::Clean()
{


    CleanModule();


}






AVoid ResourceLoader::LoadProject(std::string path)
{


    CleanModule();



    std::string project_path = PROJECT_FOLDER + path + "/";
    boost::filesystem::directory_iterator iterator(project_path);




    for (; iterator != boost::filesystem::directory_iterator(); ++iterator)
    {



        if (boost::filesystem::is_regular_file(iterator->path()))
        {


            std::string project_component_extension = boost::filesystem::extension(iterator->path());
            std::string project_component_path = iterator->path().string();



            if (project_component_extension == ".scene")
            {
                Add("Instances", new InstanceCollection());
                AStateSaver * new_saver = static_cast<AStateSaver*>(Get("Instances"));
                new_saver->SetPath(project_component_path);
            }




        }

    }
    LoadChanges();





    Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
    std::string new_window_title = ctrl->GetWindowTitle() + " - " + path;
    ctrl->SetWindowTitle(new_window_title);




}








