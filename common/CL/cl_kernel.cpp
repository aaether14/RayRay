#include <stdafx.h>







AVoid CLKernel::Init()
{


    global_work_size = local_work_size = 0;


}




AVoid CLKernel::Clean()
{


    AInt err = CL_SUCCESS;




    //---------------------------------------//



    //Cleaning AFloat buffers

    std::pair<std::string, cl_mem> data_mem_buffer_it;
    BOOST_FOREACH(data_mem_buffer_it, kernel_data_mem_buffers)
    {
        err = clReleaseMemObject(data_mem_buffer_it.second);
        SAMPLE_CHECK_ERRORS(err);
    }
    kernel_data_mem_buffers.clear();
    kernel_data_buffers.clear();



    //---------------------------------------//


    //Cleaning gl texture buffers



    std::pair<std::string, cl_mem> gl_texture_mem_buffer_it;
    BOOST_FOREACH(gl_texture_mem_buffer_it, kernel_gl_texture_mem_buffers)
    {
        glDeleteTextures(1, &kernel_gl_texture_buffers[gl_texture_mem_buffer_it.first]);
        err = clReleaseMemObject(gl_texture_mem_buffer_it.second);
        SAMPLE_CHECK_ERRORS(err);
    }
    kernel_gl_texture_mem_buffers.clear();
    kernel_gl_texture_buffers.clear();




    //---------------------------------------//



    try
    {
        if (kernel)
        {
            clReleaseKernel(kernel);
        }
    }
    catch (...)
    {
        destructorException();
    }


    //---------------------------------------//



    CLProgram::Clean();


}




AVoid CLKernel::Enable()
{


    AInt err = CL_SUCCESS;
    std::vector<cl_mem> gl_mem_textures;
    boost::copy(kernel_gl_texture_mem_buffers | boost::adaptors::map_values, std::back_inserter(gl_mem_textures));



    glFlush();
    err = clEnqueueAcquireGLObjects(cl_cw_ptr->GetCLQueue(), gl_mem_textures.size(), &gl_mem_textures[0], 0, NULL, NULL);
    err = clEnqueueNDRangeKernel(cl_cw_ptr->GetCLQueue(), kernel, 1, NULL, &global_work_size, &local_work_size, 0, NULL, NULL);
    err = clEnqueueReleaseGLObjects(cl_cw_ptr->GetCLQueue(), gl_mem_textures.size(), &gl_mem_textures[0], 0, NULL, NULL);
    err = clFlush(cl_cw_ptr->GetCLQueue());
    SAMPLE_CHECK_ERRORS(err);




    gl_mem_textures.clear();




}




AVoid CLKernel::Create(
        CLContextWrapper * cl_cw,
        const std::wstring& program_file_name,
        const std::string& program_text,
        const std::string& kernel_name,
        const std::string& build_options
        )
{


    cl_cw_ptr = cl_cw;
    CLProgram::Create(cl_cw, program_file_name, program_text, build_options);


    AInt err = CL_SUCCESS;
    kernel = clCreateKernel(GetCLProgram(), kernel_name.c_str(), &err);
    SAMPLE_CHECK_ERRORS(err);



}



template <class T>
AVoid CLKernel::AddDataBuffer(std::string buffer_name, size_t size, cl_mem_flags mem_flags)
{


    T buffer = (T)aligned_malloc(size, cl_cw_ptr->GetDeviceCopyAlignment());
    kernel_data_buffers.insert(std::pair<std::string, dtype>(buffer_name, buffer));


    //-------------------------------------------//


    cl_mem buffer_mem = (cl_mem)0;
    AInt err = CL_SUCCESS;


    //------------------------------------------//


    if (mem_flags == CL_MEM_WRITE_ONLY)
        buffer_mem = clCreateBuffer(cl_cw_ptr->GetCLContext(), CL_MEM_WRITE_ONLY, size, NULL, &err);
    else if (mem_flags == CL_MEM_READ_ONLY)
        buffer_mem = clCreateBuffer
                (
                    cl_cw_ptr->GetCLContext(),
                    CL_MEM_READ_ONLY,
                    cl_cw_ptr->GetCopyAlignment(size),
                    buffer,
                    &err
                    );


    //----------------------------------------------//


    SAMPLE_CHECK_ERRORS(err);
    if (buffer_mem == (cl_mem)0)
        throw AError("Failed to create " + buffer_name + "!");
    else
        kernel_data_mem_buffers.insert(std::pair<std::string, cl_mem>(buffer_name, buffer_mem));




}
template AVoid CLKernel::AddDataBuffer<AFloat*>(std::string buffer_name, size_t size, cl_mem_flags mem_flags);
template AVoid CLKernel::AddDataBuffer<AInt*>(std::string buffer_name, size_t size, cl_mem_flags mem_flags);







AVoid CLKernel::ReleaseDataBuffer(std::string buffer_name)
{

    AInt err = clReleaseMemObject(kernel_data_mem_buffers[buffer_name]);
    SAMPLE_CHECK_ERRORS(err);
    kernel_data_mem_buffers.erase(buffer_name);
    kernel_data_buffers.erase(buffer_name);


}






template <class T>
AVoid CLKernel::WriteToDataBuffer(std::string buffer_name, size_t size, dtype data)
{



    AInt err = clEnqueueWriteBuffer(cl_cw_ptr->GetCLQueue(), kernel_data_mem_buffers[buffer_name], CL_TRUE,
                                   0, size, boost::get<T>(data), 0, NULL, NULL);
    SAMPLE_CHECK_ERRORS(err);



}
template AVoid CLKernel::WriteToDataBuffer<AFloat*>(std::string buffer_name, size_t size, dtype data);
template AVoid CLKernel::WriteToDataBuffer<AInt*>(std::string buffer_name, size_t size, dtype data);







AVoid CLKernel::ReadDataBuffer(std::string buffer_name, size_t size)
{


    AInt err = CL_SUCCESS;


    err = clEnqueueReadBuffer(cl_cw_ptr->GetCLQueue(), kernel_data_mem_buffers[buffer_name], CL_TRUE, 0, size, &kernel_data_buffers[buffer_name], 0, NULL, NULL);
    SAMPLE_CHECK_ERRORS(err);
    err = clFinish(cl_cw_ptr->GetCLQueue());
    SAMPLE_CHECK_ERRORS(err);


}




AVoid CLKernel::SetDataBufferArg(std::string buffer_name, AUInt arg)
{


    AInt err = CL_SUCCESS;
    err = clSetKernelArg(kernel, arg, sizeof(cl_mem), (AVoid *)&kernel_data_mem_buffers[buffer_name]);
    SAMPLE_CHECK_ERRORS(err);




}





template <class T>
AVoid CLKernel::SetArgValue(T value, AUInt arg)
{


    AInt err = CL_SUCCESS;
    err = clSetKernelArg(kernel, arg, sizeof(T), &value);
    SAMPLE_CHECK_ERRORS(err);


}
template AVoid CLKernel::SetArgValue<AFloat>(AFloat value, AUInt arg);
template AVoid CLKernel::SetArgValue<AInt>(AInt value, AUInt arg);








AVoid CLKernel::SetWorkSize(size_t global, size_t local)
{


    global_work_size = (global + (local - 1)) & ~(local - 1);
    local_work_size = local;


}







AVoid CLKernel::AddGLTexture(std::string texture_name, size_t width, size_t height, AInt internal_format, GLenum format, GLenum type, cl_mem_flags mem_flags)
{


    AUInt new_texture_id;
    glGenTextures(1, &new_texture_id);
    glBindTexture(GL_TEXTURE_2D, new_texture_id);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, type, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);




    AInt err = CL_SUCCESS;
    cl_mem new_texture_mem = clCreateFromGLTexture(cl_cw_ptr->GetCLContext(),
                                                   mem_flags,
                                                   GL_TEXTURE_2D,
                                                   0,
                                                   new_texture_id,
                                                   &err);




    SAMPLE_CHECK_ERRORS(err);
    kernel_gl_texture_buffers.insert(std::pair<std::string, AUInt>(texture_name, new_texture_id));
    kernel_gl_texture_mem_buffers.insert(std::pair<std::string, cl_mem>(texture_name, new_texture_mem));




}





AVoid CLKernel::SetGLTextureArg(std::string texture_name, AUInt arg)
{


    AInt err = CL_SUCCESS;
    err = clSetKernelArg(kernel, arg, sizeof(cl_mem), (AVoid *)&kernel_gl_texture_mem_buffers[texture_name]);
    SAMPLE_CHECK_ERRORS(err);


}





AVoid CLKernel::ReleaseGLTexture(std::string texture_name)
{


    glDeleteTextures(1, &kernel_gl_texture_buffers[texture_name]);
    AInt err = clReleaseMemObject(kernel_gl_texture_mem_buffers[texture_name]);
    SAMPLE_CHECK_ERRORS(err);



    kernel_gl_texture_mem_buffers.erase(texture_name);
    kernel_gl_texture_buffers.erase(texture_name);



}







