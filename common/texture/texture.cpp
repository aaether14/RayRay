#include <stdafx.h>






FIBITMAP * TextureObject::get_dib(std::string file)
{



	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP *dib(0);
	fif = FreeImage_GetFileType(file.c_str(), 0);
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(file.c_str());
	if (fif == FIF_UNKNOWN)
		return NULL;
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, file.c_str());
	if (!dib)
		return NULL;
	FreeImage_FlipVertical(dib);
	return dib;



}







AUInt TextureObject::load_texture(std::string file, AInt param_min, AInt param_max)
{



	BYTE* bits(0);
    AUInt width(0), height(0);
	AUInt gl_texID;
	FIBITMAP *dib = get_dib(file);
	if (!dib)
		return -1;
	bits = FreeImage_GetBits(dib);
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	if ((bits == 0) || (width == 0) || (height == 0))
		return -1;
	glGenTextures(1, &gl_texID);
	glBindTexture(GL_TEXTURE_2D, gl_texID);
	if (FreeImage_GetBPP(dib) == 24){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, bits);
	}
	else if (FreeImage_GetBPP(dib) == 32){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param_min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param_max);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, ANISO);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,0);
	FreeImage_Unload(dib);
	return gl_texID;




}






AUInt TextureObject::create_texture_from_color(glm::vec4 color)
{


	AUInt gl_texID;
	BYTE * bits = new BYTE[4];
	bits[0] = (color.r * 255);
	bits[1] = (color.g * 255);
	bits[2] = (color.b * 255);
	bits[3] = (color.a * 255);
	glGenTextures(1, &gl_texID);
	glBindTexture(GL_TEXTURE_2D, gl_texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8_ALPHA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, bits);
	glBindTexture(GL_TEXTURE, 0);
	delete bits;
	return gl_texID;




}





AUInt TextureObject::load_cube_texture(std::string Directory,
	std::string PosXFilename,
	std::string NegXFilename,
	std::string PosYFilename,
	std::string NegYFilename,
	std::string PosZFilename,
	std::string NegZFilename)
{



	std::string files[6];
	files[0] += Directory;
	files[0] += PosXFilename;
	files[1] += Directory;
	files[1] += NegXFilename;
	files[2] += Directory;
	files[2] += PosYFilename;
	files[3] += Directory;
	files[3] += NegYFilename;
	files[4] += Directory;
	files[4] += PosZFilename;
	files[5] += Directory;
	files[5] += NegZFilename;




	FIBITMAP * dib(0);
	BYTE* bits(0);
    AUInt width(0), height(0);
	AUInt gl_texID;




	glGenTextures(1, &gl_texID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, gl_texID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (AInt i = 0; i<6; i++) 
	{


		dib = get_dib(files[i]);
		bits = FreeImage_GetBits(dib);
		width = FreeImage_GetWidth(dib);
		height = FreeImage_GetHeight(dib);





		if ((bits == 0) || (width == 0) || (height == 0))
			return -1;
		if (FreeImage_GetBPP(dib) == 24)
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT + i, 0, GL_SRGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, bits);
		else if (FreeImage_GetBPP(dib) == 32)
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT + i, 0, GL_SRGB_ALPHA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits);



		FreeImage_Unload(dib);
	}




	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	return gl_texID;



}







AUInt TextureObject::create_texture_array(std::string Directory, std::vector<std::string> textures, AFloat aniso)
{



	AUInt gl_texID(0), width(0), height(0);
	FIBITMAP ** dibs = 0;
	BYTE ** bits = 0;
	dibs = new FIBITMAP*[textures.size()];
	bits = new BYTE*[textures.size()];
	for (AUInt i = 0; i < textures.size(); i++)
	{


		dibs[i] = get_dib(Directory + textures[i]);
		assert(dibs[i]);
		bits[i] = FreeImage_GetBits(dibs[i]);


	}

	width = FreeImage_GetWidth(dibs[0]);
	height = FreeImage_GetHeight(dibs[0]);


	glGenTextures(1, &gl_texID);
	glBindTexture(GL_TEXTURE_2D_ARRAY, gl_texID);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);




	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, width, height, textures.size(), 0, GL_BGRA, GL_UNSIGNED_BYTE, 0);
	for (AUInt i = 0; i < textures.size(); i++)
			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, GL_BGRA, GL_UNSIGNED_BYTE, bits[i]);





	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);



	for (AUInt i = 0; i < textures.size(); i++)
		FreeImage_Unload(dibs[i]);



	return gl_texID;





}


ABoolean TextureObject::readRawFile(std::string path, BYTE*bits)
{



	std::ifstream inputFile(path, std::ios::binary);
	AInt size = getRawSize(path);




	for (AInt j = size - 1; j >= 0; j--)
	{

		for (AInt i = 0; i < size; i++)

		{

			AInt current_index = j*size + i;
			AInt current_index2 = (size - 1 - j)*size + i;

			inputFile.seekg(current_index * 2 + 0, std::ios::beg);
			bits[current_index2 * 2 + 0] = inputFile.get();
			inputFile.seekg(current_index*2 + 1, std::ios::beg);
			bits[current_index2*2 + 1] = inputFile.get();

		}

	}


	inputFile.close();
	return true;


}





AInt TextureObject::getRawSize(std::string path)
{

	std::ifstream inputFile(path, std::ios::binary);
	AInt size;
	inputFile.seekg(0, std::ios::end);



	if (!POWER_OF_TWO(AInt(sqrt((ALong)inputFile.tellg()))-1))
		size = sqrt((ALong)inputFile.tellg() / 2);
	else
		size = sqrt((ALong)inputFile.tellg());




	inputFile.close();
	return size;



}


AUInt TextureObject::create_texture(GLenum target, GLsizei width, GLsizei height,
	AInt internalFormat, AInt format, GLenum type, AVoid * pixels,
	AInt f_param, AInt c_param, glm::vec4 b_color)
{


	AUInt tex_id;

	glGenTextures(1, &tex_id);
	glBindTexture(target, tex_id);
	glTexImage2D(target, 0, internalFormat, width, height, 0, format, type, pixels);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, f_param);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, f_param);
	glTexParameteri(target, GL_TEXTURE_WRAP_S, c_param);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, c_param);
	glTexParameterf(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, ANISO);
	if (c_param == GL_CLAMP_TO_BORDER)
		glTexParameterfv(target, GL_TEXTURE_BORDER_COLOR, &b_color[0]);
	glBindTexture(target, 0);


	return tex_id;



}




ABoolean TextureObject::CheckStatus(AUInt fbo)
{


	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
	GLenum status = (GLenum)glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);

	switch (status)
	{

	case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
		DebugMsg("OpenGL framebuffer format not supported.\n");
		return false;
	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
		DebugMsg("OpenGL framebuffer missing attachment.\n");
		return false;
	case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
		DebugMsg("OpenGL framebuffer attached images must have same dimensions.\n");
		return false;
	case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
		DebugMsg("OpenGL framebuffer attached images must have same format.\n");
		return false;
	case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
		DebugMsg("OpenGL framebuffer missing draw buffer.\n");
		return false;
	case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
		DebugMsg("OpenGL framebuffer missing read buffer.\n");
		return false;
	case GL_FRAMEBUFFER_COMPLETE_EXT:
		DebugMsg("FBO created successfully!\n");
	default:
		return true;
	}

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);



}






AVoid TextureObject::CreateTexture(AUInt tex_type,
	GLenum target,
	GLsizei width, GLsizei height,
	AInt internalFormat, AInt format,
	GLenum type, AVoid
	* pixels,
	AInt f_param,
	AInt c_param,
	glm::vec4 b_color)
{



	this->width = width;
	this->height = height;




	if (this->m_FBO)
	{



		glBindFramebuffer(GL_FRAMEBUFFER, this->m_FBO);



		if (tex_type == COLOR_TYPE)
		{

			this->texture = new AUInt[this->num_tex];
			this->texture[0] = create_texture(target, width, height, internalFormat,
				format,
				type,
				pixels, f_param, c_param, b_color);


			glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->texture[0], 0);
			GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0 };
			glDrawBuffers(1, DrawBuffers);



		}
		else if (tex_type == DEPTH_TYPE)
		{

			this->depth = create_texture(target, width, height, internalFormat,
				format,
				type,
				pixels, f_param, c_param, b_color);



			glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth, 0);


		}
		else if (tex_type == G_TYPE)
		{

			
			this->texture = new AUInt[this->num_tex];
			for (AUInt i = 0; i < this->num_tex; i++)
			{

				this->texture[i] = create_texture(target, width, height, internalFormat,
					format,
					type,
					pixels, f_param, c_param, b_color);


				glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, this->texture[i], 0);
			}



			GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(this->num_tex, DrawBuffers);


		}



		CheckStatus(this->m_FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

}

AVoid TextureObject::WriteTexture(AUInt width, AUInt height)
{


	glViewport(0, 0, width, height);
	glBindFramebuffer(GL_FRAMEBUFFER, this->m_FBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}
