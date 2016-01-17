#ifndef TECHNIQUE_HPP
#define TECHNIQUE_HPP





#include <stdafx.h>






#define NULL_FILTER 11





class Techniques : public AModule
{




	BasicFilterImplementation * basic_filter_implementation;
	GBuffer * g_buffer;




public:





	/**
	Initialize all techniques
	*/
    bool Create(glm::ivec2 screen_size);






	/**
	Cleans data used by techniques
	*/
	void Clean();
	/**
	Initializes data
	*/
	void Init();
	/**
	Enables module to affect scene
	*/
	void Enable();



	/**
	Bind a certain texture object to be written to using the 'prog_target' shader
	*/
	void Bind(GLuint prog_target, TextureObject * tex_target, GLuint width, GLuint height);
	/**
	Apply certian filter and transform 'tex_source' into 'tex_target'
	*/
	void ApplyFilter(GLuint prog_target, GLuint tex_source, TextureObject * tex_target, GLuint width, GLuint height);
	/**
	Unbind any binding done by the class
	*/
	void Unbind();
	/**
	Run a certain shader program
	*/
	void RunProgram(GLuint prog_target);





	inline BasicFilterImplementation * GetBasic(){ return basic_filter_implementation; }
	inline GBuffer * GetGBuffer(){ return g_buffer; }








	

};




#endif
