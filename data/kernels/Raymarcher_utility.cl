//way too slow...




float sdSphere( float3 p, float s )
{
  return fast_length(p)-s;
}





float sdPlane( float3 p, float4 n )
{
return dot(p,n.xyz) + n.w;
}









float distanceField(__global float * data, float3 position, int * material_index)
{


    float min_distance = MAXFLOAT, current_distance;



  	for(int i = data[SPHERE_POINTER]; i < data[SPHERE_POINTER + 1]; i += SPHERE_DATA)
  	{

        current_distance = sdSphere(position - (float3)(data[i], data[i + 1], data[i + 2]), data[i + 3]);
        if (current_distance < min_distance)
        {
          min_distance = current_distance;
          if (material_index)
          *material_index = data[i + 4] * MATERIAL_DATA + data[MATERIAL_POINTER];
        }


    }







return min_distance;






}






float3 compute_normal(__global float *data, float3 pos)
{

	float3 eps = (float3)( 0.001, 0.0, 0.0 );
	return fast_normalize((float3)(
	    distanceField(data, pos+eps.xyy, 0) - distanceField(data, pos-eps.xyy, 0),
	    distanceField(data, pos+eps.yxy, 0) - distanceField(data, pos-eps.yxy, 0),
	    distanceField(data, pos+eps.yyx, 0) - distanceField(data, pos-eps.yyx, 0)));


}











int raymarch(__global float* data, struct Ray *ray, struct IntersectionResult *intersection)
{
        float t = 0.0f;
        for(int i = 0; i < 32; i++)
        {


           float h = distanceField(data, ray->origin + ray->dir * t, &intersection->material_index);
           if(h < 0.0001f)
           {
             intersection->position = ray->origin + ray->dir * t;
             intersection->normal = compute_normal(data, intersection->position);
             return true;
           }
           t += h;



        }

       return false;



}
