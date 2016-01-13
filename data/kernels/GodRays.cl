//--------------------------------------------------Aaether Engine Raytracing kernel-------------------------------------------//






#include "Raytracer_defines.cl"
#include "Math_helper.cl"
#include "Raytracer_types.cl"
#include "Raytracer_utility.cl"





//---------------------------------Main body----------------------------------------------------------//



__kernel void GodRays(__write_only image2d_t output, __global float* view_matrix, const int width, const int height, const float tan_half_fov, __global float* scene_data)
{




	//-----------------------------------------//


	int2 current_pixel = (int2)(get_global_id(0) % width, get_global_id(0) / width);
	float2 current_ray_pixel = 2.0f * (float2)(current_pixel.x, current_pixel.y) / (float2)(width, height) - (float2)(1.0f);


	//-----------------------------------------//



	struct Ray ray;
	ray.origin = (float3)(view_matrix[12], view_matrix[13], view_matrix[14]);
  ray.dir = normalize(cameraTransform(view_matrix,
		 (float3)(current_ray_pixel.x * ((float)(width) / (float)(height)) * tan_half_fov,
			 current_ray_pixel.y * tan_half_fov,
			 -1.0)));



	//-----------------------------------------//





	float3 pixel = clamp(recursivetrace(scene_data, &ray), (float3)(0.0f), (float3)(1.0f));
	write_imagef(output, current_pixel, (float4)(pixel, 1.0f));





}
