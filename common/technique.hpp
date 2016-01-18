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
    ABoolean Create(glm::ivec2 screen_size);






	/**
	Cleans data used by techniques
	*/
	AVoid Clean();
	/**
	Initializes data
	*/
	AVoid Init();
	/**
	Enables module to affect scene
	*/
	AVoid Enable();



	/**
	Bind a certain texture object to be written to using the 'prog_target' shader
	*/
	AVoid Bind(AUInt prog_target, TextureObject * tex_target, AUInt width, AUInt height);
	/**
	Apply certian filter and transform 'tex_source' into 'tex_target'
	*/
	AVoid ApplyFilter(AUInt prog_target, AUInt tex_source, TextureObject * tex_target, AUInt width, AUInt height);
	/**
	Unbind any binding done by the class
	*/
	AVoid Unbind();
	/**
	Run a certain shader program
	*/
	AVoid RunProgram(AUInt prog_target);





	inline BasicFilterImplementation * GetBasic(){ return basic_filter_implementation; }
	inline GBuffer * GetGBuffer(){ return g_buffer; }








	

};




#endif
