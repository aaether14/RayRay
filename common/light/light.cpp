#include <stdafx.h>




void Light::InitDirectionalLight()
{

	shader->AddVariable("InternalDirectionalLight.Base.color");
	shader->AddVariable("InternalDirectionalLight.Base.ambient_intensity");
	shader->AddVariable("InternalDirectionalLight.direction");
	shader->AddVariable("InternalDirectionalLight.Base.diffuse_intensity");

}




void Light::InitPointLights()
{



	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		char name[128];
		sprintf(name, "InternalPointLights[%d].Base.color", i);
		shader->AddVariable(name);
		sprintf(name, "InternalPointLights[%d].Base.ambient_intensity", i);
		shader->AddVariable(name);
		sprintf(name, "InternalPointLights[%d].Base.diffuse_intensity", i);
		shader->AddVariable(name);
		sprintf(name, "InternalPointLights[%d].position", i);
		shader->AddVariable(name);
		sprintf(name, "InternalPointLights[%d].Atten.Constant", i);
		shader->AddVariable(name);
		sprintf(name, "InternalPointLights[%d].Atten.Linear", i);
		shader->AddVariable(name);
		sprintf(name, "InternalPointLights[%d].Atten.Exp", i);
		shader->AddVariable(name);


	}



}




void Light::InitSpotLights()
{

	for (int i = 0; i < MAX_SPOT_LIGHTS; i++)
	{
		char name[128];
		sprintf(name, "InternalSpotLights[%d].Base_point_light.Base.color", i);
		shader->AddVariable(name);
		sprintf(name, "InternalSpotLights[%d].Base_point_light.Base.ambient_intensity", i);
		shader->AddVariable(name);
		sprintf(name, "InternalSpotLights[%d].Base_point_light.Base.diffuse_intensity", i);
		shader->AddVariable(name);
		sprintf(name, "InternalSpotLights[%d].Base_point_light.position", i);
		shader->AddVariable(name);
		sprintf(name, "InternalSpotLights[%d].Base_point_light.Atten.Constant", i);
		shader->AddVariable(name);
		sprintf(name, "InternalSpotLights[%d].Base_point_light.Atten.Linear", i);
		shader->AddVariable(name);
		sprintf(name, "InternalSpotLights[%d].Base_point_light.Atten.Exp", i);
		shader->AddVariable(name);
		sprintf(name, "InternalSpotLights[%d].direction", i);
		shader->AddVariable(name);
		sprintf(name, "InternalSpotLights[%d].Cutoff", i);
		shader->AddVariable(name);


	}




}



void Light::InitFog()
{

	
	shader->AddVariable("fog.color");
	shader->AddVariable("fog.density");



}



void Light::Init(Shader * shader)
{

	shader = shader;

	InitDirectionalLight();
	InitPointLights();
	InitSpotLights();
	InitFog();


}



void Light::Clean()
{


	

}



Light::Light(Shader * shader)
{


	Init(shader);


}



void Light::SetDirectionalLight(glm::vec3 color, glm::vec3 direction, float a_intensity, float d_intensity)
{


	shader->Set("InternalDirectionalLight.Base.color", color);
	shader->Set("InternalDirectionalLight.Base.ambient_intensity", a_intensity);
	shader->Set("InternalDirectionalLight.direction", direction);
	shader->Set("InternalDirectionalLight.Base.diffuse_intensity", d_intensity);



}

void Light::SetPointLights(int Index,glm::vec3 color,glm::vec3 position,float a_intensity,float d_intensity,float constant,float linear,float exp)
{

	    char name[128];
		sprintf(name, "InternalPointLights[%d].Base.color", Index);
		shader->Set(name, color);
		sprintf(name, "InternalPointLights[%d].Base.ambient_intensity", Index);
		shader->Set(name, a_intensity);
		sprintf(name, "InternalPointLights[%d].Base.diffuse_intensity", Index);
		shader->Set(name, d_intensity);
		sprintf(name, "InternalPointLights[%d].position", Index);
		shader->Set(name, position);
		sprintf(name, "InternalPointLights[%d].Atten.Constant", Index);
		shader->Set(name, constant);
		sprintf(name, "InternalPointLights[%d].Atten.Linear", Index);
		shader->Set(name, linear);
		sprintf(name, "InternalPointLights[%d].Atten.Exp", Index);
		shader->Set(name, exp);




}


void Light::SetSpotLights(int Index, glm::vec3 color, glm::vec3 position, float a_intensity, float d_intensity, float constant, float linear, float exp, glm::vec3 direction, float Cutoff)
{


	char name[128];
	sprintf(name, "InternalSpotLights[%d].Base_point_light.Base.color", Index);
	shader->Set(name, color);
	sprintf(name, "InternalSpotLights[%d].Base_point_light.Base.ambient_intensity", Index);
	shader->Set(name, a_intensity);
	sprintf(name, "InternalSpotLights[%d].Base_point_light.Base.diffuse_intensity", Index);
	shader->Set(name, d_intensity);
	sprintf(name, "InternalSpotLights[%d].Base_point_light.position", Index);
	shader->Set(name, position);
	sprintf(name, "InternalSpotLights[%d].Base_point_light.Atten.Constant", Index);
	shader->Set(name, constant);
	sprintf(name, "InternalSpotLights[%d].Base_point_light.Atten.Linear", Index);
	shader->Set(name, linear);
	sprintf(name, "InternalSpotLights[%d].Base_point_light.Atten.Exp", Index);
	shader->Set(name, exp);
	sprintf(name, "InternalSpotLights[%d].direction", Index);
	shader->Set(name, direction);
	sprintf(name, "InternalSpotLights[%d].Cutoff", Index);
	shader->Set(name, Cutoff);


}




void Light::SetFog(glm::vec3 color, GLfloat density)
{


	shader->Set("fog.color", color);
	shader->Set("fog.density", density);


}

