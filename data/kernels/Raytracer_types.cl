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



float cubeintersect(float* near_point, float* far_point, float* ray_origin, float* ray_dir)
{



 float t1,t2,tnear = -MAXFLOAT,tfar = MAXFLOAT, temp;
 bool intersectFlag = true;




  for(int i = 0 ;i < 3; i++)
  {


				  if(ray_dir[i] == 0)
					{


				   if(ray_origin[i] < near_point[i] || ray_origin[i] > far_point[i])
				    intersectFlag = false;


				  }
				  else
					{


							   t1 = (near_point[i] - ray_origin[i])/ray_dir[i];
							   t2 = (far_point[i] - ray_origin[i])/ray_dir[i];


							  if(t1 > t2)
							   swap(t1, t2);



							  tnear = fmax(tnear, t1);
								tfar = fmin(tfar, t2);



							  if(tnear > tfar)
							   intersectFlag = false;
							  if(tfar < 0)
							   intersectFlag = false;



				  }




 }




 if(intersectFlag == false)
  return 0.0f;
 else
  return tnear;




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
