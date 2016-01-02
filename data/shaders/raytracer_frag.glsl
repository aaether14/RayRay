#version 330





#include "ray_types.glsl"
#include "ray_intersection.glsl"
#include "util.glsl"




in vec2 TexCoord;
in vec3 ViewRay;




out vec3 color;




uniform vec3 camera_pos;
uniform sampler2D texture_adress1;
uniform sampler2D texture_adress2;
uniform float time;





void main()
{



    

    vec3 sun_direction = vec3(normalize(vec3(0.0,1.0,0)));
	float diffuse_intensity = 0.93;
	float ambient_intensity = 0.01;
	float specular_intensity = 0.8;
	float specular_hardness = 64;
    


	//------------------------------------------//


	Ray ray;
	ray.d = normalize(ViewRay);
	ray.o = camera_pos;



	vec3 center = vec3(0.0, 0.0, 0.0);

     
	//------------------------------------------//

     
	 int number_of_spheres = 5;
	 Sphere sphere[5];




	 sphere[0].pos = vec3(0.0, 0.0, -3.0);
	 sphere[0].rad = 0.5;
	 sphere[0].col = vec3(1.0,0.0,1.0);
	 sphere[0].pos = RotateAroundY(sphere[0].pos, center, 2.0 * time);
	 sphere[0].pos = RotateAroundX(sphere[0].pos, center, 2.0 * time);



	 sphere[1].pos = vec3(0.0, 0.0, -4.0);
	 sphere[1].rad = 1.0;
	 sphere[1].col = vec3(0.0,1.0,0.0);
	 sphere[1].pos = RotateAroundY(sphere[1].pos, center, 1.5 * time);
	 sphere[1].pos = RotateAroundX(sphere[1].pos, center, 3.0 * time);




	 sphere[2].pos = vec3(0.0, 2.0, -4.0);
	 sphere[2].rad = 0.75;
	 sphere[2].col = vec3(1.0,0.0,0.0);
	 sphere[2].pos = RotateAroundY(sphere[2].pos, center, 1.0 * time);





	 sphere[3].pos = vec3(3.0, 2.0, -4.0);
	 sphere[3].rad = 0.25;
	 sphere[3].col = vec3(0.0,0.0,1.0);
	 sphere[3].pos = RotateAroundY(sphere[3].pos, center, 4.0 * time);




	 sphere[4].pos = vec3(3.0, -2.0, 2.0);
	 sphere[4].rad = 2.0;
	 sphere[4].col = vec3(1.0);
	 sphere[4].pos = RotateAroundY(sphere[4].pos, center, (-0.5) * time);




	 //------------------------------------------//



	 float min_t = 9999.0;
	 int ti = -1;


	 for (int i = 0; i < number_of_spheres; i++)
	 {


	 float t = intersectSphere(ray, sphere[i]);


	 if (t > 0.0 && t < min_t)
	 {
	 min_t = t;
	 ti = i;
	 }




	 }


	 //--------------------------------------------------//


	 if (ti >= 0)
	 {



	 Ray ray_to_light;
	 ray_to_light.o = ray.o + ray.d * min_t + sun_direction * 0.001;
	 ray_to_light.d = sun_direction;




	 //---------------------------------------//




	 
	 vec3 sphere_normal = FindSphereNormal(sphere[ti], ray_to_light.o);
	 float diffuse_factor = clamp(dot(sun_direction, sphere_normal) * diffuse_intensity, 0.0, 1.0);



	 //----------------------------------------------//


	 vec3 half_vector = normalize(sun_direction - ray.d);
	 float specular_factor = pow(clamp(dot(sphere_normal, half_vector), 0.0, 1.0), specular_hardness) * specular_intensity;



	 //---------------------------------------------//




	 color = (sphere[ti].col * texture2D(texture_adress1, map_sphere(ray_to_light.o - sphere[ti].pos, sphere[ti].rad, 0.0)).rgb) * 
	 max(ambient_intensity, diffuse_factor) + specular_factor;




	 }
	 else
	 color = texture2D(texture_adress2, TexCoord + vec2(sin(time),cos(time))).rgb;




	 //Gamma correction
     color = pow(color, vec3(1 / 2.2));



} 