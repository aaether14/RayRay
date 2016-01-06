//------------------------------------------Ray tracing functions------------------------------------------//





int findintersection(__global float* data, struct Ray *ray, struct IntersectionResult *intersection)
{



	int result = 0;
	float dist = MAXFLOAT;
	int sphere = -1;
	int plane  = -1;





//Check for sphere intersection
	for(int i = data[SPHERE_POINTER]; i < data[SPHERE_POINTER + 1]; i += SPHERE_DATA)
	{
		int res = sphereintersect((float3)(data[i], data[i + 1], data[i + 2]), data[i + 3], ray, &dist);
		if(res) result = res, sphere = i;
		if(res && !intersection) return res;
	}




//Check for plane intersection
	for(int i = data[PLANE_POINTER]; i < data[PLANE_POINTER + 1]; i += PLANE_DATA)
	{
		int res = planeintersect((float3)(data[i], data[i + 1], data[i + 2]), data[i + 3], ray, &dist);
		if(res) result = res, plane = i;
		if(res && !intersection) return res;
	}








//Handle intersection result
	if(intersection)
	{


		intersection->result = result;
		intersection->distance = dist;
		intersection->position = ray->origin + ray->dir * dist;



		if(plane != -1)
		{
			intersection->normal = (float3)(data[plane], data[plane + 1], data[plane + 2]);
			intersection->material_index = data[plane + 4] * MATERIAL_DATA + data[MATERIAL_POINTER];

		}
		else if(sphere != -1)
		{
			intersection->normal = normalize(intersection->position - (float3)(data[sphere], data[sphere + 1], data[sphere + 2]));
			intersection->material_index = data[sphere + 4] * MATERIAL_DATA + data[MATERIAL_POINTER];
		}



	}




	return result;
}



//-----------------------------------------------------------------------//




float shadowray(__global float* data, float3 light_vector, float3 intersection_position)
{



	struct Ray light;
	light.origin = intersection_position + light_vector * EPSILON;
	light.dir = light_vector;


	return findintersection(data, &light, 0) ? 0.0f : 1.0f;
}




//-------------------------------------------------------//



float3 raytrace(__global float* data, struct RayStack *stack, struct Ray *r, float refr, int depth)
{




	float3 color = (float3)(0.0f);
	if(depth > TRACE_DEPTH) return color;




	struct IntersectionResult intersection;
	int result = findintersection(data, r, &intersection);
	if(result == 0) return color;
	struct Material intersection_material = GetMaterialFromIndex(data, intersection.material_index);





	//Handle scene lights
	for(int i = data[LIGHT_POINTER]; i < data[LIGHT_POINTER + 1]; i += LIGHT_DATA)
	{



    int light_material_index = data[i + 3] * MATERIAL_DATA + data[MATERIAL_POINTER];
		struct Material light_material = GetMaterialFromIndex(data, light_material_index);
		float3 light_vector = (float3)(data[i], data[i + 1], data[i + 2]) - intersection.position;



		light_vector = normalize(light_vector);
		float shade = shadowray(data, light_vector, intersection.position);
		float cos_theta = fmax(0.0f, dot(intersection.normal, light_vector)) * shade;
		float specularity = dot(r->dir, reflect(intersection.normal, light_vector)) * shade;



		color += cos_theta * intersection_material.diff * intersection_material.amb * light_material.amb
			+ powr(fmax(0.0f, specularity), intersection_material.spec) * light_material.amb;
	}





	//Handle reflection
	if(intersection_material.refl > 0)
	{


		float3 reflected_dir = reflect(intersection.normal, r->dir);
		struct Ray reflected_ray;
	  reflected_ray.origin = intersection.position + reflected_dir * EPSILON;
		reflected_ray.dir = reflected_dir;
		push(stack, &reflected_ray, refr, depth + 1);



	}




	//Handle refraction
	if(intersection_material.refr > 0)
	{



		float3 refractionNormal = intersection.normal * (float)result;
		float n = refr / intersection_material.refr;
    float3 refracted_dir = refract(refractionNormal, r->dir, n);
		struct Ray refracted_ray;
		refracted_ray.origin = intersection.position + refracted_dir * EPSILON;
		refracted_ray.dir = refracted_dir;
		push(stack, &refracted_ray, intersection_material.refr, depth + 1);





	}


	return color;




}





float3 recursivetrace(__global float* data, struct Ray *ray)
{


	struct RayStack stack;
	stack.top = 0;
	push(&stack, ray, 1.0f, 0);
	float3 c = (float3)(0.0);

	while(stack.top > 0)
	{
		stack.top--;
		c += raytrace(data, &stack, &stack.rays[stack.top], stack.refr[stack.top], stack.depth[stack.top]);
	}

	return c;



}
