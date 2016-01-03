//--------------------------------------Useful functions---------------------------------//




float4 matrixVectorMultiply(__global float* matrix, float4 vector)
{


	//  0  4  8 12
	//  1  5  9 13
	//  2  6 10 14
	//  3  7 11 15


	float4 result;
	result.x = matrix[0] * vector.x + matrix[4] * vector.y + matrix[8] * vector.z + matrix[12] * vector.w;
	result.y = matrix[1] * vector.x + matrix[5] * vector.y + matrix[9] * vector.z + matrix[13] * vector.w;
	result.z = matrix[2] * vector.x + matrix[6] * vector.y + matrix[10] * vector.z + matrix[14] * vector.w;
	result.w = matrix[3] * vector.x + matrix[7] * vector.y + matrix[11] * vector.z + matrix[15] * vector.w;
	return result;


}




//-------------------------------------------------------------------------//




float4 reflect(float4 A, float4 B)
{
	return B - ((float4)2) * (float4)dot(A, B) * A;
}