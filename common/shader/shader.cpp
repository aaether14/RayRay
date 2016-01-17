#include <stdafx.h>





void Shader::Add(std::string path, GLenum type)
{



	GLuint ShaderID = glCreateShader(type);
    std::string ShaderCode = AString::LoadFileToString(path).get();
	ShaderCode = AString::ManageDirective(path, ShaderCode, "#include", "\"");





	std::cout<<"Compiling shader: "<<path<<std::endl;
	char const * SourcePointer = ShaderCode.c_str();
	glShaderSource(ShaderID, 1, &SourcePointer, NULL);
	glCompileShader(ShaderID);



	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0){
		std::vector<char> ShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(ShaderID, InfoLogLength, NULL, &ShaderErrorMessage[0]);
		printf("%s\n", &ShaderErrorMessage[0]);
	}



	glAttachShader(this->program, ShaderID);
	glDeleteShader(ShaderID);




}



void Shader::Link()
{


	std::cout<<"Linking program!"<<std::endl;
	glLinkProgram(this->program);




	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetProgramiv(this->program, GL_LINK_STATUS, &Result);
	glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &InfoLogLength);



	if (InfoLogLength > 0)
	{


		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(this->program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);



	}


}
