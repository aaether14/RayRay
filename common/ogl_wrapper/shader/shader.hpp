#ifndef SHADER_HPP
#define SHADER_HPP





#include <stdafx.h>





/**


Shader class for which makes for easy uniform management using std::map


*/
class Shader : public AModule
{


	AUInt program;
	std::map<std::string, AUInt> uniforms;


public:



	/**
	Calls Init()
	*/
	inline Shader(){ this->Init(); }
	/**
	Calls Clean()
	*/
	inline ~Shader(){ this->Clean(); }
	/**
	Creates a shader program in OpenGL memory
	*/
	inline AVoid Init(){this->program = glCreateProgram(); }
	/**
	Deletes shader program from OpenGL memory and clears uniforms
	*/
	AVoid Clean(){ glDeleteProgram(this->program); this->uniforms.clear(); }


	/**
	Adds a certain shader type from provided path
	*/
	AVoid Add(std::string path, GLenum type);
	/**
	Links current shaders in program
	*/
	AVoid Link();
	/**
	OpenGL context is bound to using this program
	*/
	inline AVoid Enable(){ glUseProgram(program); }
	/**
	OpenGL context is no longer bound to a shader program
	*/
	inline AVoid Stop(){ glUseProgram(0); }


	/**
	Link a certain variable to an uniform from the shader source
	*/
	inline AVoid AddVariable(std::string name)	{ this->uniforms[name] = glGetUniformLocation(this->program, name.c_str()); }
	/**
	Set an integer to uniform unit
	*/
	inline AVoid Set(std::string name, AInt v){ glUniform1i(this->uniforms[name], v); }
	/**
	Set a AFloat to uniform unit
	*/
	inline AVoid Set(std::string name, AFloat v){ glUniform1f(this->uniforms[name], v); }
	/**
	Set a ADouble to uniform unit
	*/
	inline AVoid Set(std::string name, ADouble v){ glUniform1d(this->uniforms[name], v); }
	/**
	Set a 3D vector to uniform unit
	*/
	inline AVoid Set(std::string name, glm::vec3 v){ glUniform3f(this->uniforms[name], v.x, v.y, v.z); }
	/**
	Set a 3D vector to uniform unit
	*/
	inline AVoid Set(std::string name, AFloat x, AFloat y, AFloat z){ glUniform3f(this->uniforms[name], x, y, z); }
	/**
	Set a number ('n') of 3D vectors to uniform unit
	*/
	inline AVoid Set(std::string name, glm::vec3 * v, AUInt n){ glUniform3fv(this->uniforms[name], n, (const AFloat*)&v[0]); }
	/**
	Set a 4D vector to uniform unit
	*/
	inline AVoid Set(std::string name, glm::vec4 v){ glUniform4f(this->uniforms[name], v.x, v.y, v.z, v.w); }
	/**
	Set a 4D vector to uniform unit
	*/
	inline AVoid Set(std::string name, AFloat x, AFloat y, AFloat z, AFloat w){ glUniform4f(this->uniforms[name], x, y, z, w); }
	/**
	Set a 4x4 matrix to uniform unit
	*/
	inline AVoid Set(std::string name, glm::mat4 v){ glUniformMatrix4fv(this->uniforms[name], 1, GL_FALSE, &v[0][0]); }



	//Debug stuff


	/**
	Print uniform location - will be 0 if something went wrong
	*/
	inline AVoid Print(std::string name){ printf("%i\n", this->uniforms[name]); }


};





#endif
