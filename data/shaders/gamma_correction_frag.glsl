#version 330 core



layout(location = 0) out vec4 color;
uniform sampler2D texture;
in vec2 UV;


void main(){


    float e = 1.0 / 2.2;
	color = texture2D(texture, UV);
	color = pow(color, vec4(e));


}