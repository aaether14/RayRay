//--------------------------------------------------Aaether Engine Raytracing kernel-------------------------------------------//






#include "Raytracer_defines.cl"
#include "Math_helper.cl"
#include "Raytracer_types.cl"
#include "Raytracer_utility.cl"





//---------------------------------Main body----------------------------------------------------------//



__kernel void GodRays(__global float3* output, __global float* view_matrix, const int width, const int height, const float tan_half_fov, __global float* scene_data)
{




	//-----------------------------------------//


	float x = (float)(get_global_id(0) % width) / (float)(width) * 2.0 - 1.0;
	float y = (float)(get_global_id(0) / width) / (float)(height) * 2.0 - 1.0;


	float aspect_ratio = (float)(width) / (float)(height);


	//-----------------------------------------//



	float4 dir_vector = matrixVectorMultiply(view_matrix, (float4)(x * aspect_ratio * tan_half_fov, y * tan_half_fov, -1.0, 0.0));
	dir_vector = normalize(dir_vector);




	struct Ray ray;
	ray.origin = (float3)(view_matrix[12], view_matrix[13], view_matrix[14]);
    ray.dir = (float3)(dir_vector.x,dir_vector.y, dir_vector.z);


	//-----------------------------------------//





	float3 pixel = recursivetrace(scene_data, &ray);





	//----------------------------------------//



	pixel = clamp(pixel, (float3)(0.0), (float3)(1.0));
	output[get_global_id(0)] = pixel;





}
