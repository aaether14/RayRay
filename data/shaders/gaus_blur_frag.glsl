#version 330 core



layout(location = 0) out float color;
uniform sampler2D texture;
uniform vec3 blur_scale;
in vec2 UV;


float vGaussianBlur[10] ;

//= { 0.0882357, 0.0957407, 0.101786, 0.106026, 0.108212, 0.108212, 0.106026, 0.101786, 0.0957407, 0.0882357 };

float log_conv ( float x0, float X, float y0, float Y )
{
    return ( X + log( x0 + (y0 * exp(Y - X) ) ) );
}

float LogGaussianFilter()
{
	
	vGaussianBlur[0] = 0.0882357;
	vGaussianBlur[1] = 0.0957407;
	vGaussianBlur[2] = 0.101786;
	vGaussianBlur[3] = 0.106026;
	vGaussianBlur[4] = 0.108212;
	vGaussianBlur[5] = 0.108212;
	vGaussianBlur[6] = 0.106026;
	vGaussianBlur[7] = 0.101786;
	vGaussianBlur[8] = 0.0957407;
	vGaussianBlur[9] = 0.0882357;
	
	float vSample[ 10 ];

    for (int i = 0; i < 10; i++)
    {
		float fOffSet = i - 4.5;		
		vec2 vTexCoord = vec2( UV.x + fOffSet * blur_scale.x, UV.y + fOffSet * blur_scale.y );
		vSample[i] = texture2D( texture, vTexCoord ).r;
	}
 
    float fAccum;
    fAccum = log_conv( vGaussianBlur[0], vSample[0], vGaussianBlur[1], vSample[1] );
    for (int i = 2; i < 10; i++)
    {
        fAccum = log_conv( 1.0, fAccum, vGaussianBlur[i], vSample[i] );
    }        
    
    return fAccum;
}

void main()
{
	color = LogGaussianFilter();
}
