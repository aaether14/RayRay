//------------------------------------------Ray tracing functions------------------------------------------//





int findintersection(__global float* data, struct Ray *r, struct IntersectionResult *intersection)
{



	int result = 0;
	float dist = MAXFLOAT;
	int sphere = -1;
	int plane  = -1;





//Check for sphere intersection
	for(int i = data[SPHERE_POINTER]; i < data[SPHERE_POINTER + 1]; i += SPHERE_DATA)
	{
		int res = sphereintersect((float3)(data[i], data[i + 1], data[i + 2]), data[i + 3], r, &dist);
		if(res) result = res, sphere = i;
		if(res && !intersection) return res;
	}




//Check for plane intersection
	for(int i = data[PLANE_POINTER]; i < data[PLANE_POINTER + 1]; i += PLANE_DATA)
	{
		int res = planeintersect((float3)(data[i], data[i + 1], data[i + 2]), data[i + 3], r, &dist);
		if(res) result = res, plane = i;
		if(res && !intersection) return res;
	}








//Handle intersection result
	if(intersection)
	{


		intersection->result = result;
		intersection->distance = dist;
		intersection->position = r->origin + r->dir * dist;



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


		float3 refl = reflect(intersection.normal, r->dir);
		struct Ray R;
		R.origin = intersection.position + refl * EPSILON;
		R.dir = refl;
		push(stack, &R, refr, depth + 1);



	}




	//Handle refraction
	if(intersection_material.refr > 0)
	{



		float3 refractionNormal = intersection.normal * (float)result;
		float n = refr / intersection_material.refr;
		float cos_i = -dot(refractionNormal, r->dir);
		float cos_t2 = 1.0f - n * n * (1 - cos_i * cos_i);



		if(cos_t2 > 0)
		{
			float3 T = n * r->dir + (n * cos_i - sqrt(cos_t2)) * refractionNormal;
			struct Ray R;
			R.origin = intersection.position + T * EPSILON;
			R.dir = T;
			push(stack, &R, intersection_material.refr, depth + 1);
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

