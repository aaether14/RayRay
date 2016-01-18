#ifndef G_BUFFER_HPP
#define G_BUFFER_HPP



#include <stdafx.h>






/**



GBuffer implementation for deffered rendering
Provides textures for simple WTT and ping pong techniques



*/
class GBuffer
{


	TextureObject * buffer;
	TextureObject * color_textures[2];


	AUInt texture_index;


public:


	/**
	Calls Init()
	*/
	inline GBuffer(AUInt window_width, AUInt window_height){ Init(window_width, window_height); }
	/**
	Initialize GBuffer with screen size
	*/
	AVoid Init(AUInt window_width, AUInt window_height);


	/**
	Calls Clean()
	*/
	inline ~GBuffer(){ Clean(); }
	/**
	Cleans data
	*/
	AVoid Clean();


	/**
	Get color texture array
	*/
	inline TextureObject ** GetColorTextures(){ return color_textures; }
	/**
	Get GBuffer pointer
	*/
    inline TextureObject * GetBuffer(){ return buffer; }
	/**
	Ping pong primary texture
	*/
	inline TextureObject * GetPrimaryTexture(){ return color_textures[texture_index]; }
	/**
	Ping pong secondary texture
	*/
	inline TextureObject * GetSecondaryTexture(){ return color_textures[!texture_index]; }


	/**
	Reset ping pong counter
	*/
	inline AVoid Reset(){ texture_index = 0; }
	/**
	Ping pong ( Switching active texture)
	*/
	inline AVoid Switch(){ texture_index = !texture_index; }




};



#endif
