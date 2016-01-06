//--------------------------------------Useful functions---------------------------------//




float3 cameraTransform(__global float* matrix, float3 vector)
{



	float3 result;
	result.x = matrix[0] * vector.x + matrix[4] * vector.y + matrix[8] * vector.z;
	result.y = matrix[1] * vector.x + matrix[5] * vector.y + matrix[9] * vector.z;
	result.z = matrix[2] * vector.x + matrix[6] * vector.y + matrix[10] * vector.z;
	return result;


}




//-------------------------------------------------------------------------//




float3 reflect( float3 n, float3 i )
{
  return i - (float3)(2.0) * n * dot(n,i);
}




//-------------------------------------------------------------------------//




float3 refract( float3 n, float3 i, float eta )
{
  float cosi = dot(-i, n);
  float cost2 = 1.0f - eta * eta * (1.0f - cosi*cosi);
  float3 t = eta*i + ((eta*cosi - sqrt(fabs(cost2))) * n);
  return t * (float3)(cost2 > 0);
}




//--------------------------------------------------------------------------//
