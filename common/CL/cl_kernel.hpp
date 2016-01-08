#ifndef CL_KERNEL_HPP
#define CL_KERNEL_HPP




#include <stdafx.h>




/**
Provides functionality for OpenCL kernels. Derives CLProgram
*/




class CLKernel : public CLProgram
{


    size_t global_work_size, local_work_size;
    CLContextWrapper *cl_cw_ptr;
    cl_kernel kernel;



    std::map<std::string, cl_float*> kernel_float_buffers;
    std::map<std::string, cl_mem> kernel_float_mem_buffers;
    std::map<std::string, GLuint> kernel_gl_texture_buffers;
    std::map<std::string, cl_mem> kernel_gl_texture_mem_buffers;




public:



    /**
    Create OpenCL kernel
    */
    void Create(
            CLContextWrapper * cl_cw,
            const std::wstring& program_file_name,
            const string& program_text,
            const string& kernel_name,
            const string& build_options = ""
            );



    //--------------------------------------------//


    /**
    Initializes data
    */
    void Init();


    /**
    Cleans data
    */
    void Clean();


    /**
    Runs OpenCL kernel
    */
    void Enable();



    //--------------------------------------------//



    /**
    Get OpenCL kernel pointer
    */
    inline cl_kernel GetCLKernel(){ return kernel; }



    //---------------------------------------------//



    /**
    Set kernel work size
    */
    void SetWorkSize(size_t global, size_t local);
    /**
    Add kernel buffer memory
    */
    void AddFloatBuffer(std::string buffer_name, size_t size, cl_mem_flags mem_flags);
    /**
    Release float buffer
    */
    void ReleaseFloatBuffer(std::string buffer_name);
    /**
    Add float data to buffer
    */
    void WriteToFloatBuffer(std::string buffer_name, size_t size, cl_float * data);
    /**
    Read float buffer
    */
    void ReadFloatBuffer(std::string buffer_name, size_t size);
    /**
    Set kernel arg from float buffer
    */
    void SetFloatBufferArg(std::string buffer_name, cl_uint arg);
    /**
    Set kernel arg from value
    */
    void SetArgValue(boost::any value, cl_uint arg);
    /**
    Add opengl texture
    */
    void AddGLTexture(std::string texture_name, size_t width, size_t height, GLint internal_format, GLenum format, GLenum type, cl_mem_flags mem_flags);
    /**
    Set kernel arg from gl texture
    */
    void SetGLTextureArg(std::string texture_name, cl_uint arg);
    /**
    Release gl texture
    */
    void ReleaseGLTexture(std::string texture_name);


    //-----------------------------------------------//



    /**
    Get float buffer
    */
    inline cl_float* GetFloatBuffer(std::string buffer_name){ return kernel_float_buffers[buffer_name]; }
    /**
    Get gl texture id
    */
    inline GLuint GetGLTextureID(std::string texture_name){return kernel_gl_texture_buffers[texture_name];}





};






#endif
