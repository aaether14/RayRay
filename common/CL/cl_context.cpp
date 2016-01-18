#include <stdafx.h>




AVoid CLContextWrapper::Init()
{




    Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));


    if (ctrl->GetAppInfo()->GetInt("IsOpenCLEnabled"))
    {


        if (!ctrl->GetAppInfo()->GetInt("LinkOpenGLContext"))
            Create(ctrl->GetAppInfo()->GetString("OpenCLPlatform"),
                   "CL_DEVICE_TYPE_ALL",
                   ctrl->GetAppInfo()->GetString("OpenCLDevice"));
        else
        {


#ifdef __linux__
            cl_context_properties properties[] = {
                CL_GL_CONTEXT_KHR, (cl_context_properties)  glfwGetGLXContext(ctrl->GetWindow()),
                CL_GLX_DISPLAY_KHR, (cl_context_properties) glfwGetX11Display(),
                0};
#elif defined _WIN32
            cl_context_properties properties[] = {
                CL_GL_CONTEXT_KHR, (cl_context_properties) glfwGetWGLContext(ctrl->GetWindow()),
                CL_WGL_HDC_KHR, (cl_context_properties) glfwGetWin32Window(ctrl->GetWindow()),
                0};
#endif


            Create(ctrl->GetAppInfo()->GetString("OpenCLPlatform"),
                   "CL_DEVICE_TYPE_ALL",
                   ctrl->GetAppInfo()->GetString("OpenCLDevice"),
                   0,
                   properties);
        }



    }




}




AVoid CLContextWrapper::Clean()
{


    try
    {


        if (queue)
        {
            AInt err = clReleaseCommandQueue(queue);
            SAMPLE_CHECK_ERRORS(err);
        }

        if (context)
        {
            AInt err = clReleaseContext(context);
            SAMPLE_CHECK_ERRORS(err);
        }
    }
    catch (...)
    {
        destructorException();
    }



    CleanModule();


}




AVoid CLContextWrapper::Enable()
{




}





AVoid CLContextWrapper::selectPlatform(const std::string& platform_name_or_index)
{



    AUInt num_of_platforms = 0;
    AInt err = clGetPlatformIDs(0, 0, &num_of_platforms);
    SAMPLE_CHECK_ERRORS(err);
    std::vector<cl_platform_id> platforms(num_of_platforms);
    err = clGetPlatformIDs(num_of_platforms, &platforms[0], 0);
    SAMPLE_CHECK_ERRORS(err);



    AUInt selected_platform_index = num_of_platforms;
    ABoolean by_index = false;





    if (is_number(platform_name_or_index))
    {
        by_index = true;
        selected_platform_index = str_to<AInt>(platform_name_or_index);
    }

    std::string required_platform_subname = platform_name_or_index;
    std::cout << "Platforms (" << num_of_platforms << "):\n";








    for (AUInt i = 0; i < num_of_platforms; ++i)
    {
        size_t platform_name_length = 0;
        err = clGetPlatformInfo(
                    platforms[i],
                    CL_PLATFORM_NAME,
                    0,
                    0,
                    &platform_name_length
                    );
        SAMPLE_CHECK_ERRORS(err);


        std::vector<AChar> platform_name(platform_name_length);
        err = clGetPlatformInfo(
                    platforms[i],
                    CL_PLATFORM_NAME,
                    platform_name_length,
                    &platform_name[0],
                0
                );
        SAMPLE_CHECK_ERRORS(err);

        std::cout << "    [" << i << "] " << &platform_name[0];




        if (
                selected_platform_index == i ||
                std::string(&platform_name[0]).find(required_platform_subname) != std::string::npos &&
                selected_platform_index == num_of_platforms
                )
        {
            std::cout << " [Selected]";
            selected_platform_index = i;
        }


        std::cout << std::endl;
    }

    if (by_index && selected_platform_index >= num_of_platforms)
    {
        throw AError(
                    "Given index of platform (" + platform_name_or_index + ") "
                    "is out of range of available platforms"
                    );
    }

    if (!by_index && selected_platform_index >= num_of_platforms)
    {
        throw AError(
                    "There is no found platform with name containing \"" +
                    required_platform_subname + "\" as a substring\n"
                    );
    }

    platform = platforms[selected_platform_index];


}




AVoid CLContextWrapper::selectDevice(const std::string& device_name_or_index, const std::string& device_type_name)
{



    if (!platform)
    {
        throw AError("Platform is not selected");
    }


    cl_device_type device_type = parseDeviceType(device_type_name);

    AUInt num_of_devices = 0;
    AInt err = clGetDeviceIDs(
                platform,
                device_type,
                0,
                0,
                &num_of_devices
                );

    SAMPLE_CHECK_ERRORS(err);

    std::vector<cl_device_id> devices(num_of_devices);

    err = clGetDeviceIDs(
                platform,
                device_type,
                num_of_devices,
                &devices[0],
            0
            );
    SAMPLE_CHECK_ERRORS(err);

    if (num_of_devices>1)
    {
        sort(devices.begin(), devices.end(), device_comp);
    }

    AUInt selected_device_index = num_of_devices;
    ABoolean by_index = false;

    if (is_number(device_name_or_index))
    {
        by_index = true;
        selected_device_index = str_to<AInt>(device_name_or_index);
    }

    std::string required_device_subname = device_name_or_index;

    std::cout << "Devices (" << num_of_devices;
    if (device_type != CL_DEVICE_TYPE_ALL)
    {
        std::cout << "; filtered by type " << device_type_name;
    }
    std::cout << "):\n";

    for (AUInt i = 0; i < num_of_devices; ++i)
    {

        size_t device_name_length = 0;
        err = clGetDeviceInfo(
                    devices[i],
                    CL_DEVICE_NAME,
                    0,
                    0,
                    &device_name_length
                    );
        SAMPLE_CHECK_ERRORS(err);


        std::vector<AChar> device_name(device_name_length);
        err = clGetDeviceInfo(
                    devices[i],
                    CL_DEVICE_NAME,
                    device_name_length,
                    &device_name[0],
                0
                );
        SAMPLE_CHECK_ERRORS(err);

        std::cout << "    [" << i << "] " << &device_name[0];


        if (
                (
                    by_index &&
                    selected_device_index == i
                    ) ||
                (
                    !by_index &&
                    std::string(&device_name[0]).find(required_device_subname) != std::string::npos &&
                    selected_device_index == num_of_devices
                    )
                )
        {
            std::cout << " [Selected]";
            selected_device_index = i;
        }


        std::cout << std::endl;
    }

    if (by_index && selected_device_index >= num_of_devices)
    {
        throw AError(
                    "Given index of device (" + device_name_or_index + ") "
                    "is out of range of available devices" +
                    (device_type != CL_DEVICE_TYPE_ALL ?
                    " (among devices of type " + device_type_name + ")" :
                    std::string("")
                    )
                    );
    }

    if (!by_index && selected_device_index >= num_of_devices)
    {
        throw AError(
                    "There is no found device with name containing \"" +
                    required_device_subname + "\" as a substring\n"
                    );
    }

    device = devices[selected_device_index];



}




AVoid CLContextWrapper::createContext(const cl_context_properties* additional_context_props)
{


    if (!platform)
    {
        throw AError("Platform is not selected");
    }

    if (!device)
    {
        throw AError("Device is not selected");
    }

    size_t number_of_additional_props = 0;
    if (additional_context_props)
    {
        while (additional_context_props[number_of_additional_props++]);
        number_of_additional_props--;   // now exclude terminating 0
    }

    std::vector<cl_context_properties> context_props(
                2 +
                number_of_additional_props +
                1
                );

    context_props[0] = CL_CONTEXT_PLATFORM;
    context_props[1] = cl_context_properties(platform);

    std::copy(
                additional_context_props,
                additional_context_props + number_of_additional_props,
                context_props.begin() + 2
                );

    context_props.back() = 0;

    AInt err = 0;
    context = clCreateContext(&context_props[0], 1, &device, 0, 0, &err);
    SAMPLE_CHECK_ERRORS(err);



}









AVoid CLContextWrapper::createQueue(cl_command_queue_properties queue_properties)
{



    if (!device)
    {
        throw AError("Device is not selected");
    }

    AInt err = 0;
    queue = clCreateCommandQueue(context, device, queue_properties, &err);
    SAMPLE_CHECK_ERRORS(err);




}





AVoid CLContextWrapper::Create(const std::string& platform_name_or_index,
                              const std::string& device_type,
                              const std::string& device_name_or_index,
                              cl_command_queue_properties queue_properties,
                              const cl_context_properties* additional_context_props)
{


    selectPlatform(platform_name_or_index);
    selectDevice(device_name_or_index, device_type);
    createContext(additional_context_props);
    createQueue(queue_properties);


}
