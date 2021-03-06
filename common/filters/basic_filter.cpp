#include <stdafx.h>





AVoid BasicFilterImplementation::Init()
{



	this->null_filter = new Shader();
	this->null_filter->Add("data/shaders/filter-null_vert.glsl", GL_VERTEX_SHADER);
	this->null_filter->Add("data/shaders/filter-null_frag.glsl", GL_FRAGMENT_SHADER);
	this->null_filter->Link();


	this->null_filter->AddVariable("texture");


	this->gamma_filter = new Shader();
	this->gamma_filter->Add("data/shaders/gamma_correction_vert.glsl", GL_VERTEX_SHADER);
	this->gamma_filter->Add("data/shaders/gamma_correction_frag.glsl", GL_FRAGMENT_SHADER);
	this->gamma_filter->Link();


	this->gamma_filter->AddVariable("texture");




	
	this->mult_shader = new Shader();
	this->mult_shader->Add("data/shaders/mult_vert.glsl", GL_VERTEX_SHADER);
	this->mult_shader->Add("data/shaders/mult_frag.glsl", GL_FRAGMENT_SHADER);
	this->mult_shader->Link();

	this->mult_shader->AddVariable("mult_tex1");
	this->mult_shader->AddVariable("mult_tex2");



	this->add_shader = new Shader();
	this->add_shader->Add("data/shaders/add_vert.glsl", GL_VERTEX_SHADER);
	this->add_shader->Add("data/shaders/add_frag.glsl", GL_FRAGMENT_SHADER);
	this->add_shader->Link();

	this->add_shader->AddVariable("add_tex1");
	this->add_shader->AddVariable("add_tex2");



	this->m_quad = new Quad();



}





AVoid BasicFilterImplementation::Clean()
{


	if (null_filter)
	delete null_filter;

	if (gamma_filter)
	delete gamma_filter;


	if (mult_shader)
	delete mult_shader;


	if (add_shader)
	delete add_shader;


	if (m_quad)
	delete m_quad;


}





AVoid BasicFilterImplementation::MultTextures(TextureObject * target, AUInt tex1, AUInt tex2, glm::ivec2 window_size)
{


	target->WriteTexture(window_size.x, window_size.y);
	this->mult_shader->Enable();


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex1);
	this->mult_shader->Set("mult_tex1", 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex2);
	this->mult_shader->Set("mult_tex2", 1);

	GetQuad()->Render();
	this->mult_shader->Stop();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);



}


AVoid BasicFilterImplementation::AddTextures(TextureObject * target, AUInt tex1, AUInt tex2, glm::ivec2 window_size)
{


	target->WriteTexture(window_size.x, window_size.y);
	this->add_shader->Enable();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex1);
	this->add_shader->Set("add_tex1", 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex2);
	this->add_shader->Set("add_tex2", 1);

	GetQuad()->Render();
	this->add_shader->Stop();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);



}


