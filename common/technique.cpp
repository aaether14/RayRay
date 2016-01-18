#include <stdafx.h>







ABoolean Techniques::Create(glm::ivec2 screen_size)
{




	basic_filter_implementation = new BasicFilterImplementation();
    g_buffer = new GBuffer(screen_size.x, screen_size.y);



	return true;


}







AVoid Techniques::Bind(AUInt prog_target, TextureObject * tex_target, AUInt width, AUInt height)
{


	if (tex_target)
	tex_target->WriteTexture(width, height);
	RunProgram(prog_target);


}



AVoid Techniques::Unbind()
{



	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glUseProgram(0);


	g_buffer->GetBuffer()->SetViewport();


}





AVoid Techniques::ApplyFilter(AUInt prog_target, AUInt tex_source, TextureObject * tex_target, AUInt width, AUInt height)
{



	Bind(prog_target, tex_target, width, height);




	switch (prog_target)
	{
	case NULL_FILTER:
		basic_filter_implementation->BindNullTexture();
		break;
    }


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_source);
		GetBasic()->GetQuad()->Render();




}





AVoid Techniques::RunProgram(AUInt prog_target)
{


	switch (prog_target)
	{


	case NULL_FILTER :
			basic_filter_implementation->GetNullFilter()->Enable();
			break;


	}


}





AVoid Techniques::Clean()
{



	delete basic_filter_implementation;
	delete g_buffer;




}




AVoid Techniques::Init()
{





}




AVoid Techniques::Enable()
{




}
