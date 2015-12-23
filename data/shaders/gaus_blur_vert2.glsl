#version 330 core


layout(location = 0) in vec2 Positions;


out vec2 UV;


void main(){


	gl_Position =  vec4(Positions, 0 ,1);
	UV = (Positions.xy + vec2(1.0, 1.0)) / 2.0;


}


