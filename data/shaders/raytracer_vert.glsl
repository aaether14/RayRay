#version 330


layout (location = 0) in vec3 Position;



uniform float gAspectRatio;
uniform float gTanHalfFOV;
uniform mat4 ViewMatrix;






out vec2 TexCoord;
out vec3 ViewRay;





void main()
{


    gl_Position = vec4(Position, 1.0);
    TexCoord = (Position.xy + vec2(1.0)) / 2.0;


    ViewRay = vec3(ViewMatrix * vec4(Position.x * gAspectRatio * gTanHalfFOV,
	Position.y * gTanHalfFOV,
	-1.0, 0.0));






}