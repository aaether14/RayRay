#include <stdafx.h>





#ifdef __linux__
#include <sys/time.h>
#include <unistd.h>
#include <libgen.h>
#elif defined(_WIN32) || defined(WIN32)
#include <Windows.h>
#else
#include <ctime>
#endif




std::string opencl_error_to_str(AInt error)
{
#define CASE_CL_CONSTANT(NAME) case NAME: return #NAME;




	switch (error)
	{
		CASE_CL_CONSTANT(CL_SUCCESS)
			CASE_CL_CONSTANT(CL_DEVICE_NOT_FOUND)
			CASE_CL_CONSTANT(CL_DEVICE_NOT_AVAILABLE)
			CASE_CL_CONSTANT(CL_COMPILER_NOT_AVAILABLE)
			CASE_CL_CONSTANT(CL_MEM_OBJECT_ALLOCATION_FAILURE)
			CASE_CL_CONSTANT(CL_OUT_OF_RESOURCES)
			CASE_CL_CONSTANT(CL_OUT_OF_HOST_MEMORY)
			CASE_CL_CONSTANT(CL_PROFILING_INFO_NOT_AVAILABLE)
			CASE_CL_CONSTANT(CL_MEM_COPY_OVERLAP)
			CASE_CL_CONSTANT(CL_IMAGE_FORMAT_MISMATCH)
			CASE_CL_CONSTANT(CL_IMAGE_FORMAT_NOT_SUPPORTED)
			CASE_CL_CONSTANT(CL_BUILD_PROGRAM_FAILURE)
			CASE_CL_CONSTANT(CL_MAP_FAILURE)
			CASE_CL_CONSTANT(CL_MISALIGNED_SUB_BUFFER_OFFSET)
			CASE_CL_CONSTANT(CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST)
			CASE_CL_CONSTANT(CL_INVALID_VALUE)
			CASE_CL_CONSTANT(CL_INVALID_DEVICE_TYPE)
			CASE_CL_CONSTANT(CL_INVALID_PLATFORM)
			CASE_CL_CONSTANT(CL_INVALID_DEVICE)
			CASE_CL_CONSTANT(CL_INVALID_CONTEXT)
			CASE_CL_CONSTANT(CL_INVALID_QUEUE_PROPERTIES)
			CASE_CL_CONSTANT(CL_INVALID_COMMAND_QUEUE)
			CASE_CL_CONSTANT(CL_INVALID_HOST_PTR)
			CASE_CL_CONSTANT(CL_INVALID_MEM_OBJECT)
			CASE_CL_CONSTANT(CL_INVALID_IMAGE_FORMAT_DESCRIPTOR)
			CASE_CL_CONSTANT(CL_INVALID_IMAGE_SIZE)
			CASE_CL_CONSTANT(CL_INVALID_SAMPLER)
			CASE_CL_CONSTANT(CL_INVALID_BINARY)
			CASE_CL_CONSTANT(CL_INVALID_BUILD_OPTIONS)
			CASE_CL_CONSTANT(CL_INVALID_PROGRAM)
			CASE_CL_CONSTANT(CL_INVALID_PROGRAM_EXECUTABLE)
			CASE_CL_CONSTANT(CL_INVALID_KERNEL_NAME)
			CASE_CL_CONSTANT(CL_INVALID_KERNEL_DEFINITION)
			CASE_CL_CONSTANT(CL_INVALID_KERNEL)
			CASE_CL_CONSTANT(CL_INVALID_ARG_INDEX)
			CASE_CL_CONSTANT(CL_INVALID_ARG_VALUE)
			CASE_CL_CONSTANT(CL_INVALID_ARG_SIZE)
			CASE_CL_CONSTANT(CL_INVALID_KERNEL_ARGS)
			CASE_CL_CONSTANT(CL_INVALID_WORK_DIMENSION)
			CASE_CL_CONSTANT(CL_INVALID_WORK_GROUP_SIZE)
			CASE_CL_CONSTANT(CL_INVALID_WORK_ITEM_SIZE)
			CASE_CL_CONSTANT(CL_INVALID_GLOBAL_OFFSET)
			CASE_CL_CONSTANT(CL_INVALID_EVENT_WAIT_LIST)
			CASE_CL_CONSTANT(CL_INVALID_EVENT)
			CASE_CL_CONSTANT(CL_INVALID_OPERATION)
			CASE_CL_CONSTANT(CL_INVALID_GL_OBJECT)
			CASE_CL_CONSTANT(CL_INVALID_BUFFER_SIZE)
			CASE_CL_CONSTANT(CL_INVALID_MIP_LEVEL)
			CASE_CL_CONSTANT(CL_INVALID_GLOBAL_WORK_SIZE)
			CASE_CL_CONSTANT(CL_INVALID_PROPERTY)
			CASE_CL_CONSTANT(CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR)
	default:
		return "UNKNOWN ERROR CODE " + to_str(error);
	}

#undef CASE_CL_CONSTANT
}






AVoid* aligned_malloc(size_t size, size_t alignment)
{
	assert(alignment > 0);
    assert((alignment & (alignment - 1)) == 0);

    if (alignment < sizeof(AVoid*))
	{
        alignment = sizeof(AVoid*);
	}

    assert(size >= sizeof(AVoid*));
    assert(size / sizeof(AVoid*)*sizeof(AVoid*) == size);

    AChar* orig = new AChar[size + alignment + sizeof(AVoid*)];
    AChar* aligned =
		orig + (
        (((size_t)orig + alignment + sizeof(AVoid*)) & ~(alignment - 1)) -
		(size_t)orig
		);
    *((AChar**)aligned - 1) = orig;
	return aligned;
}











AVoid aligned_free(AVoid *aligned)
{
	if (!aligned)return; // behaves as delete: calling with 0 is NOP
    delete[] * ((AChar**)aligned - 1);
}














ABoolean is_number(const std::string& x)
{

	try
	{

        str_to<AInt>(x);

		return true;
	}
    catch (const AError&)
	{
		return false;
	}
}
















ADouble time_stamp()
{
#ifdef __linux__
	{
		struct timeval t;
		if (gettimeofday(&t, 0) != 0)
		{
            throw AError(
				"Linux-specific time measurement counter (gettimeofday) "
				"is not available."
				);
		}
		return t.tv_sec + t.tv_usec / 1e6;
	}
#elif defined(_WIN32) || defined(WIN32)
	{
		LARGE_INTEGER curclock;
		LARGE_INTEGER freq;
		if (
			!QueryPerformanceCounter(&curclock) ||
			!QueryPerformanceFrequency(&freq)
			)
		{
            throw AError(
				"Windows-specific time measurement counter (QueryPerformanceCounter, "
				"QueryPerformanceFrequency) is not available."
				);
		}

        return ADouble(curclock.QuadPart) / freq.QuadPart;
	}
#else
	{
        return ADouble(time(0));
	}
#endif
}






AVoid destructorException()
{
	if (std::uncaught_exception())
	{
		std::cerr
			<< "[ ERROR ] Catastrophic: another exception "
			<< "was thrown and suppressed during handling of "
			<< "previously started exception raising process.\n";
	}
	else
	{
		// that's OK, go up!
		throw;
	}
}











AUInt zeroCopyPtrAlignment(cl_device_id device)
{
	return 4096;
}















size_t zeroCopySizeAlignment(size_t requiredSize, cl_device_id device)
{

    return requiredSize + (~requiredSize + 1) % 64;
}











ABoolean verifyZeroCopyPtr(AVoid* ptr, size_t sizeOfContentsOfPtr)
{
    return
        (std::uintptr_t)ptr % 4096 == 0
        &&
        sizeOfContentsOfPtr % 64 == 0;
}
















AUInt requiredOpenCLAlignment(cl_device_id device)
{
    AUInt result = 0;
    AInt err = clGetDeviceInfo(
		device,
		CL_DEVICE_MEM_BASE_ADDR_ALIGN,
		sizeof(result),
		&result,
		0
		);
	SAMPLE_CHECK_ERRORS(err);
	assert(result % 8 == 0);
    return result / 8;
}











size_t deviceMaxWorkGroupSize(cl_device_id device)
{
	size_t result = 0;
    AInt err = clGetDeviceInfo(
		device,
		CL_DEVICE_MAX_WORK_GROUP_SIZE,
		sizeof(result),
		&result,
		0
		);
	SAMPLE_CHECK_ERRORS(err);
	return result;
}















AVoid deviceMaxWorkItemSizes(cl_device_id device, size_t* sizes)
{
    AInt err = clGetDeviceInfo(
		device,
		CL_DEVICE_MAX_WORK_ITEM_SIZES,
		sizeof(size_t[3]),
		sizes,
		0
		);
	SAMPLE_CHECK_ERRORS(err);
}

















size_t kernelMaxWorkGroupSize(cl_kernel kernel, cl_device_id device)
{
	size_t result = 0;
    AInt err = clGetKernelWorkGroupInfo(
		kernel,
		device,
		CL_KERNEL_WORK_GROUP_SIZE,
		sizeof(result),
		&result,
		0
		);
	SAMPLE_CHECK_ERRORS(err);
	return result;
}









ADouble eventExecutionTime(cl_event event)
{
    AULong end = 0, start = 0;

    AInt err = clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(start), &start, 0);
	SAMPLE_CHECK_ERRORS(err);

	err = clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(end), &end, 0);
	SAMPLE_CHECK_ERRORS(err);

    return ADouble(end - start) / 1e9;
}










std::string exe_dir()
{
    using namespace std;
    const AInt start_size = 1000;
    const AInt max_try_count = 8;

#ifdef __linux__
    {
        static std::string const exe = "/proc/self/exe";

        std::vector<AChar> path(start_size);
        AInt          count = max_try_count;

        for (;;)
        {
            ssize_t len = readlink(exe.c_str(), &path[0], path.size());

            if (len < 0)
            {
                throw AError(
                    "Cannot retrieve path to the executable: "
                    "readlink returned error code " +
                    to_str(errno) + "."
                    );
            }

            if (len < path.size())
            {
                path.resize(len);
                break;
            }

            if (count > 0)
            {
                --count;
                path.resize(path.size() * 2);
            }
            else
            {
                throw AError("Cannot retrieve path to the executable: path is too long.");
            }
        }

        return std::string(dirname(&path[0])) + "/";
    }
#elif defined(_WIN32) || defined(WIN32)
    {


        std::vector<AChar> path(start_size);
        AInt count = max_try_count;

        for (;;)
        {
            DWORD len = GetModuleFileNameA(NULL, &path[0], (DWORD)path.size());

            if (len == 0)
            {
                AInt err = GetLastError();
                throw AError(
                    "Getting executable path failed with error " +
                    to_str(err)
                    );
            }

            if (len < path.size())
            {
                path.resize(len);
                break;
            }

            if (count > 0)
            {
                --count;
                path.resize(path.size() * 2);
            }
            else
            {
                throw AError(
                    "Cannot retrieve path to the executable: "
                    "path is too long."
                    );
            }
        }

        std::string exe(&path[0], path.size());


        std::vector<AChar> drv(_MAX_DRIVE);
        std::vector<AChar> dir(_MAX_DIR);
        count = max_try_count;

        for (;;)
        {
            AInt rc =
                _splitpath_s(
                exe.c_str(),
                &drv[0], drv.size(),
                &dir[0], dir.size(),
                NULL, 0,
                NULL, 0
                );
            if (rc == 0)
            {
                break;
            }
            else if (rc == ERANGE)
            {
                if (count > 0)
                {
                    --count;
                    drv.resize(drv.size() * 2);
                    dir.resize(dir.size() * 2);
                }
                else
                {
                    throw AError(
                        "Getting executable path failed: "
                        "Splitting path " + exe + " to components failed: "
                        "Buffers of " + to_str(drv.size()) + " and " +
                        to_str(dir.size()) + " bytes are still too small."
                        );
                }
            }
            else
            {
                throw AError(
                    "Getting executable path failed: "
                    "Splitting path " + exe +
                    " to components failed with code " + to_str(rc)
                    );
            }
        }

        return std::string(&drv[0]) + string(&dir[0]);
    }
#else
    {
        throw AError(
            "There is no method to retrieve the directory path "
            "where executable is placed: unsupported platform."
            );
    }
#endif
}









std::wstring exe_dir_w()
{
    using namespace std;
    const AInt start_size = 1000;
    const AInt max_try_count = 8;

#if defined(_WIN32) || defined(WIN32)
    {


        std::vector<wchar_t> path(start_size);
        AInt count = max_try_count;

        for (;;)
        {
            DWORD len = GetModuleFileNameW(NULL, &path[0], (DWORD)path.size());

            if (len == 0)
            {
                AInt err = GetLastError();
                throw AError(
                    "Getting executable path failed with error " +
                    to_str(err)
                    );
            }

            if (len < path.size())
            {
                path.resize(len);
                break;
            }

            if (count > 0)
            {
                --count;
                path.resize(path.size() * 2);
            }
            else
            {
                throw AError(
                    "Cannot retrieve path to the executable: "
                    "path is too long."
                    );
            }
        }

        std::wstring exe(&path[0], path.size());


        std::vector<wchar_t> drv(_MAX_DRIVE);
        std::vector<wchar_t> dir(_MAX_DIR);
        count = max_try_count;

        for (;;)
        {
            AInt rc =
                _wsplitpath_s(
                exe.c_str(),
                &drv[0], drv.size(),
                &dir[0], dir.size(),
                NULL, 0,
                NULL, 0
                );
            if (rc == 0)
            {
                break;
            }
            else if (rc == ERANGE)
            {
                if (count > 0)
                {
                    --count;

                    drv.resize(drv.size() * 2);
                    dir.resize(dir.size() * 2);
                }
                else
                {
                    throw AError(
                        "Getting executable path failed: "
                        "Splitting path " + wstringToString(exe) + " to components failed: "
                        "Buffers of " + to_str(drv.size()) + " and " +
                        to_str(dir.size()) + " bytes are still too small."
                        );
                }
            }
            else
            {
                throw AError(
                    "Getting executable path failed: "
                    "Splitting path " + wstringToString(exe) +
                    " to components failed with code " + to_str(rc)
                    );
            }
        }


        return wstring(&drv[0]) + wstring(&dir[0]);
    }
#else
    {
        throw AError(
            "There is no method to retrieve the directory path "
            "where executable is placed: unsupported platform."
            );
    }
#endif
}








std::wstring stringToWstring(const std::string s)
{
	return std::wstring(s.begin(), s.end());
}







#ifdef __linux__
std::string wstringToString(const std::wstring w)
{
    std::string tmp;
    const wchar_t* src = w.c_str();
	CTYPELocaleHelper locale_helper;


	size_t count = wcsrtombs(NULL, &src, 0, NULL);
	if (count == size_t(-1))
	{
        throw AError(
			"Cannot convert wstring to string"
			);
	}
	std::vector<AChar> dst(count + 1);


	size_t count_converted = wcsrtombs(&dst[0], &src, count + 1, NULL);
	dst[count_converted] = '\0';
	tmp.append(&dst[0]);
	return tmp;
}
#else
std::string wstringToString(const std::wstring w)
{
    std::string tmp;

    const AChar* question_mark = "?";

    for (AUint i = 0; i < w.length(); i++)
	{
		if (w[i]>255 || w[i]<0)
		{
			tmp.append(question_mark);
		}
		else
		{
            tmp += (AChar)w[i];
		}
	}
	return tmp;
}
#endif




size_t round_up_aligned(size_t x, size_t alignment)
{
	assert(alignment > 0);
    assert((alignment & (alignment - 1)) == 0);

	size_t result = (x + alignment - 1) & ~(alignment - 1);

	assert(result >= x);
	assert(result - x < alignment);
	assert((result & (alignment - 1)) == 0);

	return result;
}




cl_device_type parseDeviceType(const std::string& device_type_name)
{
	cl_device_type  device_type = 0;
    for (size_t pos = 0, next = 0; next != std::string::npos; pos = next + 1)
	{
		next = device_type_name.find_first_of("+|", pos);
        size_t substr_len = (next != std::string::npos) ? (next - pos) : (std::string::npos);
        std::string name = device_type_name.substr(pos, substr_len);
		if (
			name == "all" ||
			name == "ALL" ||
			name == "CL_DEVICE_TYPE_ALL"
			)
		{
			device_type |= CL_DEVICE_TYPE_ALL;
			continue;
		}

		if (
			name == "default" ||
			name == "DEFAULT" ||
			name == "CL_DEVICE_TYPE_DEFAULT"
			)
		{
			device_type |= CL_DEVICE_TYPE_DEFAULT;
			continue;
		}

		if (
			name == "cpu" ||
			name == "CPU" ||
			name == "CL_DEVICE_TYPE_CPU"
			)
		{
			device_type |= CL_DEVICE_TYPE_CPU;
			continue;
		}

		if (
			name == "gpu" ||
			name == "GPU" ||
			name == "CL_DEVICE_TYPE_GPU"
			)
		{
			device_type |= CL_DEVICE_TYPE_GPU;
			continue;
		}

		if (
			name == "acc" ||
			name == "ACC" ||
			name == "accelerator" ||
			name == "ACCELERATOR" ||
			name == "CL_DEVICE_TYPE_ACCELERATOR"
			)
		{
			device_type |= CL_DEVICE_TYPE_ACCELERATOR;
			continue;
		}

        throw AError(
			"Cannot recognize " + device_type_name + " as a device type"
			);
	}
	return device_type;
}





AVoid readFile(const std::wstring& file_name, std::vector<AChar>& data)
{




#ifdef __linux__
	CTYPELocaleHelper locale_helper;

    std::ifstream file(
		wstringToString(file_name).c_str(),
        std::ios_base::ate | std::ios_base::binary
		);
#else
    std::ifstream file(
		file_name.c_str(),
        std::ios_base::ate | std::ios_base::binary
		);
#endif

	if (!file)
	{

        std::cerr
			<< "[ WARNING ] Unable to load OpenCL source code file "
			<< inquotes(wstringToString(file_name)) << " at "
			<< "the default location.\nTrying to open the file "
			<< "from the directory with executable...";

		file.clear();

#ifdef __linux__
		std::string dir = exe_dir();
		file.open(
			(dir + wstringToString(file_name)).c_str(),
            std::ios_base::ate | std::ios_base::binary
			);

		if (!file)
		{
            std::cerr << " FAILED\n";
            throw AError(
				"Cannot open file " + inquotes(dir + wstringToString(file_name))
				);
		}
		else
		{
            std::cerr << " OK\n";
		}
        std::cerr << "Full file path is " << inquotes(dir + wstringToString(file_name)) << "\n";
#else
		std::wstring dir = exe_dir_w();
		file.open(
			(dir + file_name).c_str(),
            std::ios_base::ate | std::ios_base::binary
			);

		if (!file)
		{
            std::cerr << " FAILED\n";
            throw AError(
				"Cannot open file " + wstringToString(dir + file_name)
				);
		}
		else
		{
            std::cerr << " OK\n";
		}
        std::cerr << "Full file path is " << wstringToString(inquotes_w(dir + file_name)) << "\n";
#endif

	}


	std::streamoff file_length = file.tellg();

	if (file_length == -1)
	{
        throw AError(
			"Cannot determine the length of file " +
			wstringToString(inquotes_w(file_name))
			);
	}

    file.seekg(0, std::ios_base::beg);
	data.resize(static_cast<size_t>(file_length));
	file.read(&data[0], file_length);
}




AVoid readProgramFile(const std::wstring& program_file_name, std::vector<AChar>& program_text_prepared)
{
	readFile(program_file_name, program_text_prepared);
    program_text_prepared.push_back(0);

}





cl_program createAndBuildProgram(
    const std::vector<AChar>& program_text_prepared,
	cl_context context,
	size_t num_of_devices,
	const cl_device_id* devices,
    const std::string& build_options
	)
{

    const AChar* raw_text = &program_text_prepared[0];
    AInt err;
	cl_program program = clCreateProgramWithSource(context, 1, &raw_text, 0, &err);
	SAMPLE_CHECK_ERRORS(err);


    err = clBuildProgram(program, (AUInt)num_of_devices, devices, build_options.c_str(), 0, 0);



	if (err == CL_BUILD_PROGRAM_FAILURE)
	{
		for (size_t i = 0; i < num_of_devices; ++i)
		{
			size_t log_length = 0;
			err = clGetProgramBuildInfo(
				program,
				devices[i],
				CL_PROGRAM_BUILD_LOG,
				0,
				0,
				&log_length
				);
			SAMPLE_CHECK_ERRORS(err);

            std::vector<AChar> log(log_length);

			err = clGetProgramBuildInfo(
				program,
				devices[i],
				CL_PROGRAM_BUILD_LOG,
				log_length,
				&log[0],
				0
				);
			SAMPLE_CHECK_ERRORS(err);

            throw AError(
				"Error happened during the build of OpenCL program.\n"
				"Build log:\n" +
                std::string(&log[0])
				);
		}
	}

	SAMPLE_CHECK_ERRORS(err);

	return program;
}
