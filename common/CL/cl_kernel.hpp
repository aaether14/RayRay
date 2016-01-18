#ifndef CL_KERNEL_HPP
#define CL_KERNEL_HPP




#include <stdafx.h>





typedef boost::variant<AFloat*, AInt*> dtype;




/**
Provides functionality for OpenCL kernels. Derives CLProgram
*/
class CLKernel : public CLProgram
{


    size_t global_work_size, local_work_size;
    CLContextWrapper *cl_cw_ptr;
    cl_kernel kernel;



    std::map<std::string, dtype> kernel_data_buffers;
    std::map<std::string, cl_mem> kernel_data_mem_buffers;
    std::map<std::string, AUInt> kernel_gl_texture_buffers;
    std::map<std::string, cl_mem> kernel_gl_texture_mem_buffers;




public:



    /**
    Create OpenCL kernel
    */
    AVoid Create(
            CLContextWrapper * cl_cw,
            const std::wstring& program_file_name,
            const std::string& program_text,
            const std::string& kernel_name,
            const std::string& build_options = ""
            );



    //--------------------------------------------//


    /**
    Initializes data
    */
    AVoid Init();


    /**
    Cleans data
    */
    AVoid Clean();


    /**
    Runs OpenCL kernel
    */
    AVoid Enable();



    //--------------------------------------------//



    /**
    Get OpenCL kernel pointer
    */
    inline cl_kernel GetCLKernel(){ return kernel; }



    //---------------------------------------------//



    /**
    Set kernel work size
    */
    AVoid SetWorkSize(size_t global, size_t local);
    /**
    Add kernel buffer memory
    */
    template <class T>
    AVoid AddDataBuffer(std::string buffer_name, size_t size, cl_mem_flags mem_flags);
    /**
    Release AFloat buffer
    */
    AVoid ReleaseDataBuffer(std::string buffer_name);
    /**
    Add AFloat data to buffer
    */
    template<class T>
    AVoid WriteToDataBuffer(std::string buffer_name, size_t size, dtype data);
    /**
    Read AFloat buffer
    */
    AVoid ReadDataBuffer(std::string buffer_name, size_t size);
    /**
    Set kernel arg from AFloat buffer
    */
    AVoid SetDataBufferArg(std::string buffer_name, AUInt arg);
    /**
    Set kernel arg from value
    */
    template <class T>
    AVoid SetArgValue(T value, AUInt arg);
    /**
    Add opengl texture
    */
    AVoid AddGLTexture(std::string texture_name, size_t width, size_t height, AInt internal_format, GLenum format, GLenum type, cl_mem_flags mem_flags);
    /**
    Set kernel arg from gl texture
    */
    AVoid SetGLTextureArg(std::string texture_name, AUInt arg);
    /**
    Release gl texture
    */
    AVoid ReleaseGLTexture(std::string texture_name);


    //-----------------------------------------------//



    /**
    Get AFloat buffer
    */
    inline dtype GetDataBuffer(std::string buffer_name){ return kernel_data_buffers[buffer_name]; }
    /**
    Get gl texture id
    */
    inline AUInt GetGLTextureID(std::string texture_name){return kernel_gl_texture_buffers[texture_name];}





};






#endif
