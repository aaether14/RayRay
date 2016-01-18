#ifndef CL_PROGRAM_HPP
#define CL_PROGRAM_HPP




#include <stdafx.h>







/**
Provides functionality for OpenCL programs
*/
class CLProgram : public AModule
{



	cl_program program;




public:



	/**
	Create OpenCL program
	*/
    AVoid Create(
		CLContextWrapper *cl_cw,
		const std::wstring& program_file_name,
        const std::string& program_text,
        const std::string& build_options = ""
		);



	//-----------------------------------------//




	/**
	Initializes data
	*/
    AVoid Init();


	/**
	Cleans data
	*/
    AVoid Clean();


	/**
	Runs OpenCL program
	*/
    AVoid Enable();



	//--------------------------------------//



	inline cl_program GetCLProgram(){ return program; }





};




#endif
