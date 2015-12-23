#ifndef CL_CONTEXT_HPP
#define CL_CONTEXT_HPP



#include <stdafx.h>






/**
Provides functionallity for creating OpenCL context
*/
class CLContextWrapper : public AModule
{




	cl_platform_id platform;
	cl_device_id device;
	cl_context context;
	cl_command_queue queue;



	//--------------------------------------------//



	/**
	Create OpenCL context
	*/
	void Create(const std::string& platform_name_or_index,
		const std::string& device_type,
		const std::string& device_name_or_index = "0",
		cl_command_queue_properties queue_properties = 0,
		const cl_context_properties* additional_context_props = 0);



	//----------------------------------------------//



	/**
	Select OpenCL drivers platform
	*/
	void selectPlatform(const std::string& platform_name_or_index);
	/**
	Select device to run OpenCL programs
	*/
	void selectDevice(const std::string& device_name_or_index, const std::string& device_type_name);
	/**
	Create OpenCL context
	*/
	void createContext(const cl_context_properties* additional_context_props);
	/**
	Create OpenCL queue
	*/
	void createQueue(cl_command_queue_properties queue_properties = 0);






public:



	/**
	Initializes data
	*/
	void Init();


	/**
	Cleans data
	*/
	void Clean();


	/**
	Nothing for now
	*/
	void Enable();




	//-----------------------------------------------//



	/**
	Get OpenCL context
	*/
	inline cl_context GetCLContext(){ return context; }
	/**
	Get OpenCL device
	*/
	inline cl_device_id GetCLDevice(){return device;}
	/**
	Get OpenCL platform
	*/
	inline cl_platform_id GetCLPlatform(){ return platform; }
	/**
	Get queue
	*/
	inline cl_command_queue GetCLQueue(){ return queue; }



	//------------------------------------------------//



	/**
	Get device copy alignment
	*/
	inline cl_uint GetDeviceCopyAlignment(){ return zeroCopyPtrAlignment(device); }
	/**
	Get copy alignment
	*/
	inline size_t GetCopyAlignment(size_t required_size){ return zeroCopySizeAlignment(required_size, device); }





};



#endif