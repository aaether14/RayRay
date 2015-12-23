//--------------------------------------------------Aaether Engine Raytracing kernel-------------------------------------------//





#define STACK_DEPTH 20
#define TRACE_DEPTH 10



#define MAX_PLANES 10
#define MAX_SPHERES 10
#define MAX_LIGHTS 10
#define MAX_MATERIALS 10




#define EPSILON 0.001f




//---------------------------------------Data structures------------------------------//



struct Ray
{
	float4 origin;
	float4 dir;
};



struct Sphere
{
	uint  material;
	float4 center;
	float sqradius;
};



struct Plane
{
	uint material;
	float4 normal;
	float dist;
};




struct Light
{
	uint  material;
	float4 center;
};




struct Material
{
	float refl;
	float refr;
	float diff;
	float spec;
	float4 amb;
};




struct Scene
{
	struct Plane planes[MAX_PLANES];
	struct Sphere spheres[MAX_SPHERES];
	struct Light  lights[MAX_LIGHTS];
	struct Material materials[MAX_MATERIALS];

	uint numPlanes;
	uint numSpheres;
	uint numLights;
	uint numMaterials;
};



struct RayStack
{
	struct Ray r[STACK_DEPTH];
	int depth[STACK_DEPTH];
	float refr[STACK_DEPTH];
	int top;
};


//--------------------------------------Useful functions---------------------------------//




float4 matrixVectorMultiply(__global float* matrix, float4* vector)
{


	//  0  4  8 12
	//  1  5  9 13
	//  2  6 10 14
	//  3  7 11 15


	float4 result;
	result.x = matrix[0] * ((*vector).x) + matrix[4] * ((*vector).y) + matrix[8] * ((*vector).z) + matrix[12] * ((*vector).w);
	result.y = matrix[1] * ((*vector).x) + matrix[5] * ((*vector).y) + matrix[9] * ((*vector).z) + matrix[13] * ((*vector).w);
	result.z = matrix[2] * ((*vector).x) + matrix[6] * ((*vector).y) + matrix[10] * ((*vector).z) + matrix[14] * ((*vector).w);
	result.w = matrix[3] * ((*vector).x) + matrix[7] * ((*vector).y) + matrix[11] * ((*vector).z) + matrix[15] * ((*vector).w);
	return result;


}




//------------------------------------------Ray tracing functions------------------------------------------//



void buildscene(struct Scene *s, __global float *data)
{


	s->numSpheres = s->numLights = s->numMaterials = s->numPlanes = 0;



    

	//Build sphere data
	for (int i = data[0]; i < data[1]; i += 6)
	{
	s->spheres[s->numSpheres].center = (float4)(data[i], data[i + 1], data[i + 2], data[i + 3]);
	s->spheres[s->numSpheres].sqradius = data[i + 4];
	s->spheres[s->numSpheres].material = (int)data[i + 5];
	s->numSpheres++;
	}



	
	//Build plane data
	for (int i = data[1]; i < data[2]; i += 6)
	{
	s->planes[s->numPlanes].normal = (float4)(data[i], data[i + 1], data[i + 2], data[i + 3]);
	s->planes[s->numPlanes].dist = data[i + 4];
	s->planes[s->numPlanes].material = (int)data[i + 5];
	s->numPlanes++;
	}



	//Build material data
	for (int i = data[2]; i < data[3]; i += 8)
	{
	
	s->materials[s->numMaterials].refl = data[i];
	s->materials[s->numMaterials].refr = data[i + 1];
	s->materials[s->numMaterials].spec = data[i + 2];
	s->materials[s->numMaterials].amb  = (float4)(data[i + 3], data[i + 4], data[i + 5], data[i + 6]);
	s->materials[s->numMaterials].diff = data[i + 7];
	s->numMaterials++;
	
	}
	



	//Build light data
	for (int i = data[3]; i < data[4]; i += 5)
	{
	
    s->lights[s->numLights].center = (float4)(data[i], data[i + 1], data[i + 2], data[i + 3]);
	s->lights[s->numLights].material = (int)(data[i + 4]);
	s->numLights++;
	
	}



}




float4 planenormal(struct Plane *p)
{
	return p->normal;
}





int planeintersect(struct Plane *p, struct Ray *r, float *dist)
{
	float d = (-dot(p->normal, r->origin) + p->dist) / dot(p->normal, r->dir);

	if(d > 0 && d < *dist)
	{
		*dist = d; 
		return 1;
	}

	return 0;
}




float4 spherenormal(struct Sphere *s, float4 poi)
{
	return normalize(poi - s->center);
}



int sphereintersect(struct Sphere *s, struct Ray *r, float *dist)
{
	float4 v = r->origin - s->center;
	float b = -dot(v, r->dir);
	float det = (b * b) - dot(v, v) + s->sqradius;

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

float4 reflect(float4 A, float4 B)
{
	return B - ((float4)2) * (float4)dot(A, B) * A;
}



void push(struct RayStack *s, struct Ray *r, float refr, int depth)
{
	if(s->top < STACK_DEPTH)
	{
		s->r[s->top].dir = r->dir;
		s->r[s->top].origin = r->origin;
		s->refr[s->top] = refr;
		s->depth[s->top] = depth;
		s->top++;
	}
}

struct IntersectionResult
{
	int result;
	float4 normal;
	float4 position;
	float distance;
	struct Material *material;
};

int findintersection(struct Scene *s, struct Ray *r, struct IntersectionResult *intersection)
{
	int result = 0;
	float dist = MAXFLOAT;
	int sphere = -1;
	int plane  = -1;

	for(uint i = 0; i < s->numSpheres; i++)
	{
		int res = sphereintersect(&s->spheres[i], r, &dist);
		if(res) result = res, sphere = i;
		if(res && !intersection) return res;
	}

	for(uint i = 0; i < s->numPlanes; i++)
	{
		int res = planeintersect(&s->planes[i], r, &dist);
		if(res) result = res, plane = i;
		if(res && !intersection) return res;
	}

	if(intersection)
	{
		intersection->result = result;
		intersection->distance = dist;
		intersection->position = r->origin + r->dir * dist;

		if(plane != -1)
		{
			intersection->normal = planenormal(&s->planes[plane]);
			intersection->material = &s->materials[s->planes[plane].material];
		}
		else if(sphere != -1)
		{
			intersection->normal = spherenormal(&s->spheres[sphere], intersection->position);
			intersection->material = &s->materials[s->spheres[sphere].material];
		}
	}

	return result;
}




float shadowray(struct Scene *s, float4 L, float4 P)
{
	float t = length(L);
	L *= 1.f / t;

	struct Ray light;
	light.origin = P + L * EPSILON;
	light.dir = L;

	return findintersection(s, &light, 0) ? 0.0f : 1.0f;
}








float4 raytrace(struct Scene *s, struct RayStack *stack, struct Ray *r, float refr, int depth)
{




	float4 color = (float4)(0, 0, 0, 0);

	if(depth > TRACE_DEPTH) return color;


	struct IntersectionResult intersection;
	int result = findintersection(s, r, &intersection);

	if(result == 0) return color;

	struct Material *m  = intersection.material;
	float4 P = intersection.position;
	float4 N = intersection.normal;




	//Handle scene lights
	for(uint i = 0; i < s->numLights; i++)
	{
		struct Material *lm = &s->materials[s->lights[i].material];
		float4 L = s->lights[i].center - P;

		float shade = shadowray(s, L, P);

		L = normalize(L);

		float angle = fmax(0.f, dot(N, L)) * shade;
		float s = dot(r->dir, reflect(N, L)) * shade;

		color += angle * m->diff * m->amb * lm->amb 
			+ powr(fmax(0.f, s), m->spec) * lm->amb;
	}




	//Handle reflection
	if(m->refl > 0)
	{
		float4 refl = reflect(N, r->dir);

		struct Ray R;
		R.origin = P + refl * EPSILON;
		R.dir = refl;

		push(stack, &R, refr, depth + 1);
	}



	//Handle refraction
	if(m->refr > 0)
	{
		float4 refrN = N * (float)result;
		float n = refr / m->refr;
		float cos_i = -dot(refrN, r->dir);
		float cos_t2 = 1.f - n * n * (1 - cos_i * cos_i);

		if(cos_t2 > 0)
		{
			float4 T = n * r->dir + (n * cos_i - sqrt(cos_t2)) * refrN;

			struct Ray R;
			R.origin = P + T * EPSILON;
			R.dir = T;

			push(stack, &R, m->refr, depth + 1);
		}
	}


	return color;




}






float4 recursivetrace(struct Scene *s, struct Ray *r)
{


	struct RayStack stack;
	stack.top = 0;
	push(&stack, r, 1.f, 0);

	float4 c = (float4)(0, 0, 0, 0);

	while(stack.top > 0)
	{
		stack.top--;
		c += raytrace(s, &stack, &stack.r[stack.top], stack.refr[stack.top], stack.depth[stack.top]);
	}

	return c;



}




//---------------------------------Main body----------------------------------------------------------//



__kernel void GodRays(__global float4* output, __global float* view_matrix, const int width, const int height, const float tan_half_fov, __global float* scene_data)
{



    //-----------------Scene Initialization-------------//



	struct Scene scene;
	buildscene(&scene, scene_data);



	//-----------------------------------------//


	float x = (float)(get_global_id(0) % width) / (float)(width) * 2.0 - 1.0;
	float y = (float)(get_global_id(0) / width) / (float)(height) * 2.0 - 1.0;


	float aspect_ratio = (float)(width) / (float)(height);


	//-----------------------------------------//



	float4 dir_vector = matrixVectorMultiply(view_matrix, &(float4)(x * aspect_ratio * tan_half_fov, y * tan_half_fov, -1.0, 0.0));



	struct Ray ray;
	ray.origin = (float4)(view_matrix[12], view_matrix[13], view_matrix[14], 0.0);
	ray.dir = normalize(dir_vector);



	//-----------------------------------------//





	float4 pixel = recursivetrace(&scene, &ray);






	//----------------------------------------//



	pixel = clamp(pixel, 0.0, 1.0);
	output[get_global_id(0)] = pixel;





}
