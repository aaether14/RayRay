#include <stdafx.h>




void CLContextWrapper::Init()
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




void CLContextWrapper::Clean()
{


    try
    {


        if (queue)
        {
            cl_int err = clReleaseCommandQueue(queue);
            SAMPLE_CHECK_ERRORS(err);
        }

        if (context)
        {
            cl_int err = clReleaseContext(context);
            SAMPLE_CHECK_ERRORS(err);
        }
    }
    catch (...)
    {
        destructorException();
    }



    CleanModule();


}




void CLContextWrapper::Enable()
{




}





void CLContextWrapper::selectPlatform(const std::string& platform_name_or_index)
{



    cl_uint num_of_platforms = 0;
    // get total number of available platforms:
    cl_int err = clGetPlatformIDs(0, 0, &num_of_platforms);
    SAMPLE_CHECK_ERRORS(err);

    // use vector for automatic memory management
    std::vector<cl_platform_id> platforms(num_of_platforms);
    // get IDs for all platforms:
    err = clGetPlatformIDs(num_of_platforms, &platforms[0], 0);
    SAMPLE_CHECK_ERRORS(err);

    cl_uint selected_platform_index = num_of_platforms;
    bool by_index = false;

    if (is_number(platform_name_or_index))
    {
        // Select platform by index:
        by_index = true;
        selected_platform_index = str_to<int>(platform_name_or_index);
        // does not return here; need to look at the complete platfrom list
    }

    // this is ignored in case when we have platform already selected by index
    string required_platform_subname = platform_name_or_index;

    std::cout << "Platforms (" << num_of_platforms << "):\n";

    // TODO In case of empty platform name select the default platform or 0th platform?

    for (cl_uint i = 0; i < num_of_platforms; ++i)
    {
        // Get the length for the i-th platform name
        size_t platform_name_length = 0;
        err = clGetPlatformInfo(
                    platforms[i],
                    CL_PLATFORM_NAME,
                    0,
                    0,
                    &platform_name_length
                    );
        SAMPLE_CHECK_ERRORS(err);

        // Get the name itself for the i-th platform
        // use vector for automatic memory management
        std::vector<char> platform_name(platform_name_length);
        err = clGetPlatformInfo(
                    platforms[i],
                    CL_PLATFORM_NAME,
                    platform_name_length,
                    &platform_name[0],
                0
                );
        SAMPLE_CHECK_ERRORS(err);

        std::cout << "    [" << i << "] " << &platform_name[0];

        // decide if this i-th platform is what we are looking for
        // we select the first one matched skipping the next one if any
        //
        if (
                selected_platform_index == i || // we already selected the platform by index
                string(&platform_name[0]).find(required_platform_subname) != string::npos &&
                selected_platform_index == num_of_platforms // haven't selected yet
                )
        {
            std::cout << " [Selected]";
            selected_platform_index = i;
            // do not stop here, just want to see all available platforms
        }

        // TODO Something when more than one platform matches a given subname

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




void CLContextWrapper::selectDevice(const std::string& device_name_or_index, const std::string& device_type_name)
{



    if (!platform)
    {
        throw AError("Platform is not selected");
    }

    // List devices of a given type only
    cl_device_type device_type = parseDeviceType(device_type_name);

    cl_uint num_of_devices = 0;
    cl_int err = clGetDeviceIDs(
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
    {// sort devices by name to be sure that order is not changed from run to run
        // it is supposed that different devices have different names
        sort(devices.begin(), devices.end(), device_comp);
    }

    cl_uint selected_device_index = num_of_devices;
    bool by_index = false;

    if (is_number(device_name_or_index))
    {
        // Select device by index:
        by_index = true;
        selected_device_index = str_to<int>(device_name_or_index);
        // does not return here; need to look at the complete devices list
    }

    // this is ignored in case when we have device already selected by index
    string required_device_subname = device_name_or_index;

    std::cout << "Devices (" << num_of_devices;
    if (device_type != CL_DEVICE_TYPE_ALL)
    {
        std::cout << "; filtered by type " << device_type_name;
    }
    std::cout << "):\n";

    for (cl_uint i = 0; i < num_of_devices; ++i)
    {
        // Get the length for the i-th device name
        size_t device_name_length = 0;
        err = clGetDeviceInfo(
                    devices[i],
                    CL_DEVICE_NAME,
                    0,
                    0,
                    &device_name_length
                    );
        SAMPLE_CHECK_ERRORS(err);

        // Get the name itself for the i-th device
        // use vector for automatic memory management
        std::vector<char> device_name(device_name_length);
        err = clGetDeviceInfo(
                    devices[i],
                    CL_DEVICE_NAME,
                    device_name_length,
                    &device_name[0],
                0
                );
        SAMPLE_CHECK_ERRORS(err);

        std::cout << "    [" << i << "] " << &device_name[0];

        // decide if this i-th device is what you are looking for
        // select the first matched skipping the next one if any
        if (
                (
                    by_index &&
                    selected_device_index == i  // we already selected the device by index
                    ) ||
                (
                    !by_index &&
                    string(&device_name[0]).find(required_device_subname) != string::npos &&
                    selected_device_index == num_of_devices   // haven't selected yet
                    )
                )
        {
            std::cout << " [Selected]";
            selected_device_index = i;
            // do not stop here, just see all available devices
        }

        // TODO Something when more than one device matches a given subname

        std::cout << std::endl;
    }

    if (by_index && selected_device_index >= num_of_devices)
    {
        throw AError(
                    "Given index of device (" + device_name_or_index + ") "
                    "is out of range of available devices" +
                    (device_type != CL_DEVICE_TYPE_ALL ?
                    " (among devices of type " + device_type_name + ")" :
                    string("")
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




void CLContextWrapper::createContext(const cl_context_properties* additional_context_props)
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
        // count all additional props including terminating 0
        while (additional_context_props[number_of_additional_props++]);
        number_of_additional_props--;   // now exclude terminating 0
    }

    // allocate enough space for platform and all additional props if any
    std::vector<cl_context_properties> context_props(
                2 + // for CL_CONTEXT_PLATFORM and platform itself
                number_of_additional_props +
                1   // for terminating zero
                );

    context_props[0] = CL_CONTEXT_PLATFORM;
    context_props[1] = cl_context_properties(platform);

    std::copy(
                additional_context_props,
                additional_context_props + number_of_additional_props,
                context_props.begin() + 2   // +2 -- skipping already initialized platform entries
                );

    context_props.back() = 0;

    cl_int err = 0;
    context = clCreateContext(&context_props[0], 1, &device, 0, 0, &err);
    SAMPLE_CHECK_ERRORS(err);



}









void CLContextWrapper::createQueue(cl_command_queue_properties queue_properties)
{



    if (!device)
    {
        throw AError("Device is not selected");
    }

    cl_int err = 0;
    queue = clCreateCommandQueue(context, device, queue_properties, &err);
    SAMPLE_CHECK_ERRORS(err);




}





void CLContextWrapper::Create(const std::string& platform_name_or_index,
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
