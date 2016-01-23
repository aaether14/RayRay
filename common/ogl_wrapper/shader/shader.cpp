#include <stdafx.h>





AVoid Shader::Add(std::string path, GLenum type)
{



	AUInt ShaderID = glCreateShader(type);
    std::string ShaderCode = AString::LoadFileToString(path).get();
	ShaderCode = AString::ManageDirective(path, ShaderCode, "#include", "\"");





	std::cout<<"Compiling shader: "<<path<<std::endl;
	AChar const * SourcePointer = ShaderCode.c_str();
	glShaderSource(ShaderID, 1, &SourcePointer, NULL);
	glCompileShader(ShaderID);



	AInt Result = GL_FALSE;
	AInt InfoLogLength;
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0){
		std::vector<AChar> ShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(ShaderID, InfoLogLength, NULL, &ShaderErrorMessage[0]);
		printf("%s\n", &ShaderErrorMessage[0]);
	}



	glAttachShader(this->program, ShaderID);
	glDeleteShader(ShaderID);




}



AVoid Shader::Link()
{


	std::cout<<"Linking program!"<<std::endl;
	glLinkProgram(this->program);




	AInt Result = GL_FALSE;
	AInt InfoLogLength;
	glGetProgramiv(this->program, GL_LINK_STATUS, &Result);
	glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &InfoLogLength);



	if (InfoLogLength > 0)
	{


		std::vector<AChar> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(this->program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);



	}


}
