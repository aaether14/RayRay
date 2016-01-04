//--------------------------------------------------Aaether Engine Raytracing kernel-------------------------------------------//


#define STACK_DEPTH 20
#define TRACE_DEPTH 10
#define EPSILON 0.001f






#include "Math_helper.cl"
#include "Raytracer_types.cl"
#include "Raytracer_utility.cl"



//---------------------------------Main body----------------------------------------------------------//



__kernel void GodRays(__global float4* output, __global float* view_matrix, const int width, const int height, const float tan_half_fov, __global float* scene_data)
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





	float4 pixel = recursivetrace(scene_data, &ray);





	//----------------------------------------//



	pixel = clamp(pixel, (float4)(0.0), (float4)(1.0));
	output[get_global_id(0)] = pixel;





}
