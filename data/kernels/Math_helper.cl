//--------------------------------------Useful functions---------------------------------//




float4 matrixVectorMultiply(__global float* matrix, float4 vector)
{



	float4 result;
	result.x = matrix[0] * vector.x + matrix[4] * vector.y + matrix[8] * vector.z + matrix[12] * vector.w;
	result.y = matrix[1] * vector.x + matrix[5] * vector.y + matrix[9] * vector.z + matrix[13] * vector.w;
	result.z = matrix[2] * vector.x + matrix[6] * vector.y + matrix[10] * vector.z + matrix[14] * vector.w;
	result.w = matrix[3] * vector.x + matrix[7] * vector.y + matrix[11] * vector.z + matrix[15] * vector.w;
	return result;


}




//-------------------------------------------------------------------------//




float3 reflect(float3 A, float3 B)
{
	return B - ((float3)2) * (float3)dot(A, B) * A;
}




//-------------------------------------------------------------------------//