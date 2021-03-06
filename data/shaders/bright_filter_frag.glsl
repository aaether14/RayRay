#version 330 core



layout(location = 0) out vec4 color;


uniform sampler2D texture;
uniform float white_point;


in vec2 UV;


float luminance(vec3 rgb)
 {
	const vec3 kLum = vec3(0.2126, 0.7152, 0.0722);
	return max(dot(rgb, kLum), 0.0001);
}


void main(){


    if (luminance(texture2D(texture, UV).rgb) > white_point)
	color = vec4(1.0, 1.0, 1.0, 1.0);
	else
	color = vec4(0.0, 0.0, 0.0, 1.0);


}