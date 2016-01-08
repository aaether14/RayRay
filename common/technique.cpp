#include <stdafx.h>







bool Techniques::Create(glm::ivec2 screen_size)
{




	basic_filter_implementation = new BasicFilterImplementation();
	fxaa_implementation = new FXAAImplementation();
    g_buffer = new GBuffer(screen_size.x, screen_size.y);





	return true;
	
}







void Techniques::Bind(GLuint prog_target, TextureObject * tex_target, GLuint width, GLuint height)
{


	if (tex_target)
	tex_target->WriteTexture(width, height);
	RunProgram(prog_target);


}



void Techniques::Unbind()
{



	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glUseProgram(0);


	g_buffer->GetBuffer()->SetViewport();


}





void Techniques::ApplyFilter(GLuint prog_target, GLuint tex_source, TextureObject * tex_target, GLuint width, GLuint height)
{



	Bind(prog_target, tex_target, width, height);



	switch (prog_target)
	{
	case NULL_FILTER:
		basic_filter_implementation->BindNullTexture();
		break;
	case FXAA_FILTER :
	    fxaa_implementation->BindFxaaTexture();
		break;
	}



		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_source);
		GetBasic()->GetQuad()->Render();




}





void Techniques::RunProgram(GLuint prog_target)
{


	switch (prog_target)
	{


	case NULL_FILTER :
			basic_filter_implementation->GetNullFilter()->Enable();
			break;
	case FXAA_FILTER :
			fxaa_implementation->GetFxaaFilter()->Enable();
			break;


	}


}





void Techniques::Clean()
{



	delete basic_filter_implementation;
	delete fxaa_implementation;
	delete g_buffer;




}




void Techniques::Init()
{





}




void Techniques::Enable()
{




}
