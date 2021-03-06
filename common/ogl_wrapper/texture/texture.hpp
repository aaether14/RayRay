#ifndef TEXTURE_HPP
#define TEXTURE_HPP






#include <stdafx.h>







#define DebugMsg(str){printf("%s",str);}
#define POWER_OF_TWO(x) ( (x > 0) && ((x & (x - 1)) == 0) ) 
#define COLOR_TYPE 0x256
#define DEPTH_TYPE 0x257
#define G_TYPE 0x258
#define ANISO 16.0f






/**


Class for managing OpenGL textures and also WTT(write to texture) support
Using FreeImage for loading


*/
class TextureObject
{



	AUInt m_FBO;


	AUInt *texture;
	AUInt depth;


	AUInt num_tex;
	AUInt width;
	AUInt height;



public:


	/**
	Reserve a number of texture targets
	*/
	inline TextureObject(AUInt num_tex){ this->Init(num_tex); }
	/**
	Create a number - 'num_tex'
	*/
	inline AVoid Init(AUInt num_tex){ glGenFramebuffers(1, &this->m_FBO); this->num_tex = num_tex; }


	/**
	Calls Clean()
	*/
	inline ~TextureObject(){ this->Clean(); }
	/**
	Cleans textures
	*/
	inline AVoid Clean(){ glDeleteFramebuffers(1, &m_FBO); glDeleteTextures(num_tex, texture); glDeleteTextures(1, &depth); }



	/**
	Bind the texture with 'id' to a 'tex_unit'
	*/
	inline AVoid BindTexture(AUInt id, AUInt tex_unit){ glActiveTexture(tex_unit); glBindTexture(GL_TEXTURE_2D, this->texture[id]); }
	/**
	Reset active texture unit
	*/
	inline AVoid ResetTextureState(){ glActiveTexture(GL_TEXTURE0); }


	/**
	Get array of OpenGL texture references
	*/
	inline AUInt *GetTexture(){ return this->texture; }
	/**
	Get OpenGL texture reference of depth texture
	*/
	inline AUInt GetDepth(){ return this->depth; }


	/**
	Write to texture on given size
	*/
	AVoid WriteTexture(AUInt width, AUInt height);



	/**
	Create texture out of parameters
	*/
	AVoid CreateTexture(AUInt tex_type,
		GLenum target,
		GLsizei width, GLsizei height,
		AInt internalFormat, AInt format,
		GLenum type, AVoid
		* pixels,
		AInt f_param, 
		AInt c_param, 
		glm::vec4 b_color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));



	/**
	Get texture width
	*/
	inline AUInt GetWidth(){ return this->width; }
	/**
	Get texture height
	*/
	inline AUInt GetHeight(){ return this->height; }
	/**
	Set a certain viewport
	*/
	inline AVoid SetViewport(){ glViewport(0, 0, this->width, this->height); }



	/**
	Load texture from file to OpenGL memory
	*/
	static AUInt load_texture(std::string file, AInt param_min, AInt param_max);
	/**
	Load cube map from files to OpenGL memory
	*/
	static AUInt load_cube_texture(std::string Directory,
		std::string PosXFilename,
		std::string NegXFilename,
		std::string PosYFilename,
		std::string NegYFilename,
		std::string PosZFilename,
		std::string NegZFilename);
	/**
	Load textures to texture array in OpenGL memory
	*/
	static AUInt create_texture_array(std::string Directory, std::vector<std::string> textures, AFloat aniso);
	/**
	Create a texture from a given color
	*/
	static AUInt create_texture_from_color(glm::vec4 color);
	/**
	Fill FIBITMAP data from image file
	*/
	static FIBITMAP *get_dib(std::string file);
	/**
	read a .raw file
	*/
	static ABoolean readRawFile(std::string path, BYTE * bits);
	/**
	Get size of a .raw file
	*/
	static AInt getRawSize(std::string path);
	/**
	Create a texture in memory
	*/
	static AUInt create_texture(GLenum target, GLsizei width, GLsizei height, AInt internalFormat, AInt format, GLenum type, AVoid * pixels,
		AInt f_param, AInt c_param, glm::vec4 b_color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	/**
	Check if OpenGL is ok with what you're doing
	*/
	static ABoolean CheckStatus(AUInt fbo);





};






#endif