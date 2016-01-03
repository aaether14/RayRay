//------------------------------------------Ray tracing functions------------------------------------------//








int findintersection(__global float* data, struct Ray *r, struct IntersectionResult *intersection)
{



	int result = 0;
	float dist = MAXFLOAT;
	int sphere = -1;
	int plane  = -1;





//Check for sphere intersection
	for(int i = data[0]; i < data[1]; i += 6)
	{
		int res = sphereintersect((float4)(data[i], data[i + 1], data[i + 2], data[i + 3]), data[i + 4], r, &dist);
		if(res) result = res, sphere = i;
		if(res && !intersection) return res;
	}




//Check for plane intersection
	for(int i = data[1]; i < data[2]; i += 6)
	{
		int res = planeintersect((float4)(data[i], data[i + 1], data[i + 2], data[i + 3]), data[i + 4], r, &dist);
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
			intersection->normal = (float4)(data[plane], data[plane + 1], data[plane + 2], data[plane + 3]);
			intersection->material_index = data[plane + 5] * 8 + data[2];

		}
		else if(sphere != -1)
		{
			intersection->normal = normalize(intersection->position - (float4)(data[sphere], data[sphere + 1], data[sphere + 2], data[sphere + 3]));
			intersection->material_index = data[sphere + 5] * 8 + data[2];
		}



	}




	return result;
}



//-----------------------------------------------------------------------//




float shadowray(__global float* data, float4 L, float4 P)
{

	float t = length(L);
	L *= 1.f / t;


	struct Ray light;
	light.origin = P + L * EPSILON;
	light.dir = L;


	return findintersection(data, &light, 0) ? 0.0f : 1.0f;
}




//-------------------------------------------------------//



float4 raytrace(__global float* data, struct RayStack *stack, struct Ray *r, float refr, int depth)
{




	float4 color = (float4)(0, 0, 0, 0);
	if(depth > TRACE_DEPTH) return color;




	struct IntersectionResult intersection;
	int result = findintersection(data, r, &intersection);
	if(result == 0) return color;
	struct Material intersection_material = GetMaterialFromIndex(data, intersection.material_index);





	//Handle scene lights
	for(int i = data[3]; i < data[4]; i += 5)
	{



        int light_material_index = data[i + 4] * 8 + data[2];
		struct Material light_material = GetMaterialFromIndex(data, light_material_index);
		float4 light_vector = (float4)(data[i], data[i + 1], data[i + 2],data[i + 3]) - intersection.position;



		float shade = shadowray(data, light_vector, intersection.position);
		light_vector = normalize(light_vector);
		float cos_theta = fmax(0.f, dot(intersection.normal, light_vector)) * shade;
		float specularity = dot(r->dir, reflect(intersection.normal, light_vector)) * shade;



		color += cos_theta * intersection_material.diff * intersection_material.amb * light_material.amb 
			+ powr(fmax(0.f, specularity), intersection_material.spec) * light_material.amb;
	}




	//Handle reflection
	if(intersection_material.refl > 0)
	{


		float4 refl = reflect(intersection.normal, r->dir);
		struct Ray R;
		R.origin = intersection.position + refl * EPSILON;
		R.dir = refl;
		push(stack, &R, refr, depth + 1);



	}



	//Handle refraction
	if(intersection_material.refr > 0)
	{
		float4 refrN = intersection.normal * (float)result;
		float n = refr / intersection_material.refr;
		float cos_i = -dot(refrN, r->dir);
		float cos_t2 = 1.f - n * n * (1 - cos_i * cos_i);

		if(cos_t2 > 0)
		{
			float4 T = n * r->dir + (n * cos_i - sqrt(cos_t2)) * refrN;

			struct Ray R;
			R.origin = intersection.position + T * EPSILON;
			R.dir = T;

			push(stack, &R, intersection_material.refr, depth + 1);
		}
	}


	return color;




}





float4 recursivetrace(__global float* data, struct Ray *ray)
{


	struct RayStack stack;
	stack.top = 0;
	push(&stack, ray, 1.f, 0);
	float4 c = (float4)(0, 0, 0, 0);

	while(stack.top > 0)
	{
		stack.top--;
		c += raytrace(data, &stack, &stack.rays[stack.top], stack.refr[stack.top], stack.depth[stack.top]);
	}

	return c;



}

