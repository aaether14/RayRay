#version 330 core



layout(location = 0) out vec4 color;
uniform sampler2D mult_tex1;
uniform sampler2D mult_tex2;
in vec2 UV;


void main(){


	color = texture(mult_tex1, UV) * texture(mult_tex2, UV).r;


}

