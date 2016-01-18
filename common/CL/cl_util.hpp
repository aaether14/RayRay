#ifndef CL_UTIL_HPP
#define CL_UTIL_HPP


#include <stdafx.h>






std::string opencl_error_to_str(AInt error);
AVoid* aligned_malloc(size_t size, size_t alignment);
AVoid aligned_free(AVoid *aligned);
ABoolean is_number(const std::string& x);





template <typename T>
std::string inquotes(const T& x, const AChar* q = "\"")
{
	std::ostringstream ostr;
	ostr << q << x << q;
	return ostr.str();
}




template <typename T>
std::wstring inquotes_w(const T& x, const wchar_t* q = L"\"")
{
	std::wostringstream ostr;
	ostr << q << x << q;
	return ostr.str();
}





template <typename T>
T str_to(const std::string& s)
{
	std::istringstream ss(s);
	T res;
	ss >> res;

	if (!ss || (ss.get(), ss))
	{
        throw AError(
			"Cannot interpret string " + inquotes(s) +
			" as object of type " + inquotes(typeid(T).name())
			);
	}

	return res;
}







template <typename T>
std::string to_str(const T x, std::streamsize width = 0, AChar fill = ' ')
{

    std::ostringstream os;
    os << std::setw(width) << std::setfill(fill) << x;
	if (!os)
	{
        throw AError("Cannot represent object as a string");
	}
	return os.str();
}






#define SAMPLE_CHECK_ERRORS(ERR)                        \
    if(ERR != CL_SUCCESS)                               \
	    {                                                   \
        throw AError(                                    \
            "OpenCL error " +                           \
            opencl_error_to_str(ERR) +                  \
            " happened in file " + to_str(__FILE__) +   \
            " at line " + to_str(__LINE__) + "."        \
        );                                              \
	    }






template <typename T>
T rand_uniform_01()
{
	return T(std::rand()) / RAND_MAX;
}





template <typename T>
AVoid fill_rand_uniform_01(T* buffer, size_t size)
{
	std::generate_n(buffer, size, rand_uniform_01<T>);
}





inline size_t rand_index(size_t n)
{
    return static_cast<size_t>(std::rand() / ((ADouble)RAND_MAX + 1)*n);
}



ADouble time_stamp();
AVoid destructorException();
AUInt zeroCopyPtrAlignment(cl_device_id device = 0);
size_t zeroCopySizeAlignment(size_t requiredSize, cl_device_id device = 0);
ABoolean verifyZeroCopyPtr(AVoid* ptr, size_t sizeOfContentsOfPtr);
AUInt requiredOpenCLAlignment(cl_device_id device);
size_t deviceMaxWorkGroupSize(cl_device_id device);
AVoid deviceMaxWorkItemSizes(cl_device_id device, size_t* sizes);
size_t kernelMaxWorkGroupSize(cl_kernel kernel, cl_device_id device);



std::string exe_dir();
std::wstring exe_dir_w();
std::wstring stringToWstring(const std::string s);
std::string wstringToString(const std::wstring s);




#define FULL_PATH_A(name) (::exe_dir()+std::string(name)).c_str()
#define FULL_PATH_W(name) (::exe_dir_w()+std::wstring(L##name)).c_str()



#ifdef UNICODE
#define FULL_PATH FULL_PATH_W
#else
#define FULL_PATH FULL_PATH_A
#endif




ADouble eventExecutionTime(cl_event event);
struct CTYPELocaleHelper
{
	CTYPELocaleHelper()
	{
        const AChar* tmp_locale = setlocale(LC_CTYPE, NULL);
		if (tmp_locale == NULL)
		{
            std::cerr
				<< "[ WARNING ] Cannot retrieve current CTYPE locale. Non-ASCII file paths will not work.\n";
			return;
		}

		old_locale.append(tmp_locale);

		tmp_locale = setlocale(LC_CTYPE, "");
		if (tmp_locale == NULL)
		{
            std::cerr
				<< "[ WARNING ] Cannot set system default CTYPE locale. Non-ASCII file paths will not work.\n";
		}
	}


	~CTYPELocaleHelper()
	{

        const AChar* tmp_locale = setlocale(LC_CTYPE, old_locale.c_str());
		if (tmp_locale == NULL)
		{
            std::cerr
				<< "[ WARNING ] Cannot restore CTYPE locale.\n";
		}
	}

private:
	std::string old_locale;
};




size_t round_up_aligned(size_t x, size_t alignment);
cl_device_type parseDeviceType(const std::string& device_type_name);
static ABoolean device_comp(cl_device_id id1, cl_device_id id2)
{
    AInt err;
	size_t len1, len2;
	err = clGetDeviceInfo(id1, CL_DEVICE_NAME, 0, NULL, &len1);
	SAMPLE_CHECK_ERRORS(err);
	err = clGetDeviceInfo(id2, CL_DEVICE_NAME, 0, NULL, &len2);
	SAMPLE_CHECK_ERRORS(err);
    std::vector<AChar>    name1(len1);
    std::vector<AChar>    name2(len2);
	err = clGetDeviceInfo(id1, CL_DEVICE_NAME, len1, &name1[0], NULL);
	SAMPLE_CHECK_ERRORS(err);
	err = clGetDeviceInfo(id2, CL_DEVICE_NAME, len2, &name2[0], NULL);
	SAMPLE_CHECK_ERRORS(err);
	return strcmp(&name1[0], &name2[0])>0;
}





AVoid readFile(const std::wstring& file_name, std::vector<AChar>& data);
AVoid readProgramFile(const std::wstring& program_file_name, std::vector<AChar>& program_text_prepared);





cl_program createAndBuildProgram(
    const std::vector<AChar>& program_text_prepared,
	cl_context context,
	size_t num_of_devices,
	const cl_device_id* devices,
    const std::string& build_options
	);





#endif
