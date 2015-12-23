#include <stdafx.h>




void CLProgram::Init()
{




}




void CLProgram::Clean()
{



	try
	{
		if (program)
		{
			clReleaseProgram(program);
		}
	}
	catch (...)
	{
		destructorException();
	}



	CleanModule();


}




void CLProgram::Enable()
{






}





void CLProgram::Create(
	CLContextWrapper *cl_cw,
	const std::wstring& program_file_name,
	const string& program_text,
	const string& build_options
	)
{


	program = NULL;


	if (!program_file_name.empty() && !program_text.empty())
	{
		throw Error(
			"Both program file name and program text are specified. "
			"Should be one of them only."
			);
	}

	if (program_file_name.empty() && program_text.empty())
	{
		throw Error(
			"Neither of program file name or program text are specified. "
			"One of them is required."
			);
	}

	assert(program_file_name.empty() + program_text.empty() == 1);

	// use vector for automatic memory management
	std::vector<char> program_text_prepared;

	if (!program_file_name.empty())
	{
		readProgramFile(program_file_name, program_text_prepared);
	}
	else
	{
		program_text_prepared.resize(program_text.length() + 1);  // +1 for terminating zero
		copy(program_text.begin(), program_text.end(), program_text_prepared.begin());
	}


	cl_device_id device = cl_cw->GetCLDevice();
	program = createAndBuildProgram(program_text_prepared, cl_cw->GetCLContext(), 1, &device, build_options);



}