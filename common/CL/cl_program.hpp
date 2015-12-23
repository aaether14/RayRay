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
	void Create(
		CLContextWrapper *cl_cw,
		const std::wstring& program_file_name,
		const string& program_text,
		const string& build_options = ""
		);



	//-----------------------------------------//




	/**
	Initializes data
	*/
	void Init();


	/**
	Cleans data
	*/
	void Clean();


	/**
	Runs OpenCL program
	*/
	void Enable();



	//--------------------------------------//



	inline cl_program GetCLProgram(){ return program; }





};




#endif