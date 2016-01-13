//------------------------------------------Ray tracing functions------------------------------------------//





int findintersection(__global float* data, struct Ray *ray, struct IntersectionResult *intersection)
{



	int result = 0;
	float min_distance = MAXFLOAT, current_distance = 0.0f;
	int object = NO_TYPE;
	int type = NO_TYPE;






//Check for sphere intersection
	for(int i = data[SPHERE_POINTER]; i < data[SPHERE_POINTER + 1]; i += SPHERE_DATA)
	{
		current_distance = sphereintersect((float3)(data[i], data[i + 1], data[i + 2]), data[i + 3], ray);
		if (current_distance > 0.0f)
		{
			if (!intersection)
			return true;

      if (current_distance < min_distance)
			{
			min_distance = current_distance;
			object = i;
			type = SPHERE_TYPE;
			result = true;
		  }

		}
	}




	//Check for plane intersection
		for(int i = data[PLANE_POINTER]; i < data[PLANE_POINTER + 1]; i += PLANE_DATA)
		{
			current_distance = planeintersect((float3)(data[i], data[i + 1], data[i + 2]), data[i + 3], ray);
			if (current_distance > 0.0f)
			{
				if (!intersection)
				return true;

				if (current_distance < min_distance)
				{
				min_distance = current_distance;
				object = i;
				type = PLANE_TYPE;
				result = true;
				}

			}
		}




		//Check for box intersection
			for(int i = data[BOX_POINTER]; i < data[BOX_POINTER + 1]; i += BOX_DATA)
			{
				current_distance = cubeintersect((float3)(data[i], data[i + 1], data[i + 2]), (float3)(data[i + 3], data[i + 4], data[i + 5]), ray);
				if (current_distance > 0.0f)
				{
					if (!intersection)
					return true;

					if (current_distance < min_distance)
					{
					min_distance = current_distance;
					object = i;
					type = BOX_TYPE;
					result = true;
					}

				}
			}








//Handle intersection result
	if(intersection)
	{


		intersection->position = ray->origin + ray->dir * min_distance;



		if(type == PLANE_TYPE)
		{
			intersection->normal = (float3)(data[object], data[object + 1], data[object + 2]);
			intersection->material_index = data[object + 4] * MATERIAL_DATA + data[MATERIAL_POINTER];

		}
		else if(type == SPHERE_TYPE)
		{
			intersection->normal = normalize(intersection->position - (float3)(data[object], data[object + 1], data[object + 2]));
			intersection->material_index = data[object + 4] * MATERIAL_DATA + data[MATERIAL_POINTER];
		}
		else if(type == BOX_TYPE)
		{
			intersection->normal = cube_normal(intersection->position, (float3)(data[object], data[object + 1], data[object + 2]), (float3)(data[object + 3], data[object + 4], data[object + 5]));
			intersection->material_index = data[object + 6] * MATERIAL_DATA + data[MATERIAL_POINTER];
		}



	}




	return result;
}



//-----------------------------------------------------------------------//




float shadowray(__global float* data, float3 intersection_to_light, float3 intersection_position)
{



	struct Ray to_light;
	to_light.origin = intersection_position + intersection_to_light * EPSILON;
	to_light.dir = intersection_to_light;


	return findintersection(data, &to_light, 0) ? 0.0f : 1.0f;
}




//-------------------------------------------------------//



float3 raytrace(__global float* data, struct RayStack *stack, struct Ray *ray, float refr, int depth)
{




	float3 color = (float3)(0.0f);
	if(depth > TRACE_DEPTH) return color;




	struct IntersectionResult intersection;
	int result = findintersection(data, ray, &intersection);
	if(result == 0) return color;
	struct Material intersection_material = GetMaterialFromIndex(data, intersection.material_index);





	//Handle scene lights
	for(int i = data[LIGHT_POINTER]; i < data[LIGHT_POINTER + 1]; i += LIGHT_DATA)
	{



    int light_material_index = data[i + 3] * MATERIAL_DATA + data[MATERIAL_POINTER];
		struct Material light_material = GetMaterialFromIndex(data, light_material_index);
		float3 intersection_to_light = fast_normalize((float3)(data[i], data[i + 1], data[i + 2]) - intersection.position);



		float shade = shadowray(data, intersection_to_light, intersection.position);
		float cos_theta = fmax(0.0f, dot(intersection.normal, intersection_to_light)) * shade;
		float specularity = dot(ray->dir, reflect(intersection.normal, intersection_to_light)) * shade;



		color += cos_theta * intersection_material.diff * intersection_material.amb * light_material.amb
			+ powr(fmax(0.0f, specularity), intersection_material.spec) * light_material.amb;
	}





	//Handle reflection
	if(intersection_material.refl > 0)
	{


		float3 reflected_dir = reflect(intersection.normal, ray->dir);
		struct Ray reflected_ray;
	  reflected_ray.origin = intersection.position + reflected_dir * EPSILON;
		reflected_ray.dir = reflected_dir;
		push(stack, &reflected_ray, refr, depth + 1);



	}




	//Handle refraction
	if(intersection_material.refr > 0)
	{


    if (refr == intersection_material.refr)
    intersection.normal = dot(intersection.normal, ray->dir) < 0 ? intersection.normal : intersection.normal * (-1.0f);


		float n = refr / intersection_material.refr;
		float cos_i = -dot(intersection.normal, ray->dir);
		float cos_t2 = 1.f - n * n * (1 - cos_i * cos_i);

							if(cos_t2 > 0)
							{
											float3 refracted_dir = n * ray->dir + (n * cos_i - sqrt(cos_t2)) * intersection.normal;
											struct Ray refracted_ray;
											refracted_ray.origin = intersection.position + refracted_dir * EPSILON;
											refracted_ray.dir = refracted_dir;
											push(stack, &refracted_ray, intersection_material.refr, depth + 1);
							}


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
