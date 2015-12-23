#version 330 core



layout(location = 0) out vec4 color;
uniform sampler2D add_tex1;
uniform sampler2D add_tex2;
in vec2 UV;


void main()
{


	color = texture(add_tex1, UV) + texture(add_tex2, UV);


}

