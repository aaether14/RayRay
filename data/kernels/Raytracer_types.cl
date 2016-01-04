//---------------------------------------Data structures------------------------------//



struct Ray
{
	float3 origin;
	float3 dir;
};



//--------------------------------------------------------//



struct RayStack
{
	struct Ray rays[STACK_DEPTH];
	int depth[STACK_DEPTH];
	float refr[STACK_DEPTH];
	int top;
};



//--------------------------------------------------------//




struct Material
{
	float refl;
	float refr;
	float diff;
	float spec;
	float3 amb;
};





//--------------------------------------------//




struct Material GetMaterialFromIndex(__global float * data, int material_index)
{


	struct Material material;
	material.amb = (float3)(data[material_index], data[material_index + 1], data[material_index + 2]);
	material.refl = data[material_index + 3];
	material.refr = data[material_index + 4];
	material.spec = data[material_index + 5];
	material.diff = data[material_index + 6];



    return material;

}




//--------------------------------------------------------//



struct IntersectionResult
{
	int result;
	float3 normal;
	float3 position;
	float distance;
	int material_index;
};





//----------------------------------------------------------//




int planeintersect(float3 plane_normal, float plane_distance, struct Ray *ray, float *dist)
{
	float d = (-dot(plane_normal, ray->origin) + plane_distance) / dot(plane_normal, ray->dir);

	if(d > 0 && d < *dist)
	{
		*dist = d; 
		return 1;
	}

	return 0;
}






//-------------------------------------------------------------------------//




int sphereintersect(float3 sphere_center, float sphere_radius, struct Ray *r, float *dist)
{


	float3 v = r->origin - sphere_center;
	float b = -dot(v, r->dir);
	float det = (b * b) - dot(v, v) + sphere_radius;



	if(det > 0)
	{
		det = sqrt(det);
		float i1 = b - det;
		float i2 = b + det;

		if(i2 > 0)
		{
			if(i1 < 0)
			{
				if(i2 < *dist) { *dist = i2; return -1; }
			}
			else
			{
				if(i1 < *dist) { *dist = i1; return 1; }
			}
		}
	}

	return 0;
}





//-----------------------------------------------------------------//





void push(struct RayStack *ray_stack, struct Ray *ray, float refr, int depth)
{
	if(ray_stack->top < STACK_DEPTH)
	{
		ray_stack->rays[ray_stack->top].dir = ray->dir;
	    ray_stack->rays[ray_stack->top].origin = ray->origin;
		ray_stack->refr[ray_stack->top] = refr;
		ray_stack->depth[ray_stack->top] = depth;
		ray_stack->top++;
	}
}





//----------------------------------------------------------------//