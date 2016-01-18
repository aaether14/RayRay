#ifndef BASIC_FILTER_HPP
#define BASIC_FILTER_HPP




#include <stdafx.h>






/**


Storing basic filters like null filter,
gamma correction, additive and multiplicative blending


*/
class BasicFilterImplementation
{


	Shader * null_filter;
	Shader * gamma_filter;


	Shader * add_shader;
	Shader * mult_shader;


	Quad * m_quad;



public:


	/**
	Calls Init()
	*/
	inline BasicFilterImplementation(){ this->Init(); }
	/**
	Initializes data
	*/
	AVoid Init();


	/**
	Calls Clean()
	*/
	inline ~BasicFilterImplementation(){ this->Clean(); }
	/**
	Cleans data
	*/
	AVoid Clean();


	/**
	Get pointer to null shader
	*/
	inline Shader * GetNullFilter(){ return this->null_filter; }
	/**
	Get pointer to gamma shader
	*/
	inline Shader * GetGammaFilter(){ return this->gamma_filter; }


	/**
	Bind texture for null shader
	*/
	inline AVoid BindNullTexture(){ this->null_filter->Set("texture", 0); }
	/**
	Bind texture for gamma shader
	*/
	inline AVoid BindGammaTexture(){ this->gamma_filter->Set("texture", 0); }


	/**
	Mult 'tex1' by 'tex2.x' and store in 'target'
	*/
	AVoid MultTextures(TextureObject * target, AUInt tex1, AUInt tex2, glm::ivec2 window_size);
	/**
	Add 'tex1' to 'tex2' and store in 'target'
	*/
	AVoid AddTextures(TextureObject * target, AUInt tex1, AUInt tex2, glm::ivec2 window_size);

	/**
	Get pointer to quad
	*/
	inline Quad * GetQuad(){ return m_quad; }


};





#endif