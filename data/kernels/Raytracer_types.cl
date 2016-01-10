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
	float3 normal;
	float3 position;
	int material_index;
};





//----------------------------------------------------------//




float planeintersect(float3 plane_normal, float plane_distance, struct Ray *ray)
{


	float d = (-dot(plane_normal, ray->origin) + plane_distance) / dot(plane_normal, ray->dir);

	if(d > 0.0f)
	return d;


	return 0.0f;
}






//-------------------------------------------------------------------------//




float sphereintersect(float3 sphere_center, float sphere_radius, struct Ray *r)
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
				return i2;
			else
				return i1;



		}
	}

	return 0.0f;



}





//-----------------------------------------------------------------//



float cubeintersect(float3 near_point, float3 far_point, struct Ray * ray)
{


   float tx1 = (near_point.x - ray->origin.x) / ray->dir.x;
   float tx2 = (far_point.x - ray->origin.x) / ray->dir.x;

   float tmin = fmin(tx1, tx2);
   float tmax = fmax(tx1, tx2);

	 float ty1 = (near_point.y - ray->origin.y) / ray->dir.y;
	 float ty2 = (far_point.y - ray->origin.y) / ray->dir.y;

   tmin = fmax(tmin, fmin(ty1, ty2));
   tmax = fmin(tmax, fmax(ty1, ty2));

	 float tz1 = (near_point.z - ray->origin.z) / ray->dir.z;
	 float tz2 = (far_point.z - ray->origin.z) / ray->dir.z;

	 tmin = fmax(tmin, fmin(tz1, tz2));
	 tmax = fmin(tmax, fmax(tz1, tz2));


   if (tmax >= tmin)
	 return tmin;
	 else
	 return 0.0f;



}




//-----------------------------------------------------------------//


float3 cube_normal(float3 position, float3 near_point, float3 far_point)
{


       if(fabs(position.x - near_point.x) < BOX_NORMAL_EPSILON)
       return (float3)(-1,0,0);
			 if(fabs(position.x - far_point.x) < BOX_NORMAL_EPSILON)
			 return (float3)(1,0,0);
			 if(fabs(position.y - near_point.y) < BOX_NORMAL_EPSILON)
			 return (float3)(0,-1,0);
			 if(fabs(position.y - far_point.y) < BOX_NORMAL_EPSILON)
			 return (float3)(0,1,0);
			 if(fabs(position.z - near_point.z) < BOX_NORMAL_EPSILON)
			 return (float3)(0,0,-1);
			 if(fabs(position.z - far_point.z) < BOX_NORMAL_EPSILON)
		   return (float3)(0,0,1);



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
