#version 330 core



layout(location = 0) out vec4 color;
uniform sampler2D texture;
uniform vec3 blur_scale;
in vec2 UV;


void main(){

    color = vec4(0.0);
    color += texture2D(texture, UV + (vec2(-3.0) * blur_scale.xy)) * 0.015625;
	color += texture2D(texture, UV + (vec2(-2.0) * blur_scale.xy)) * 0.09375;
	color += texture2D(texture, UV + (vec2(-1.0) * blur_scale.xy)) * 0.234375;
	color += texture2D(texture, UV + (vec2(0.0) * blur_scale.xy)) * 0.3125;
	color += texture2D(texture, UV + (vec2(1.0) * blur_scale.xy)) * 0.234375;
	color += texture2D(texture, UV + (vec2(2.0) * blur_scale.xy)) * 0.09375;
	color += texture2D(texture, UV + (vec2(3.0) * blur_scale.xy)) * 0.015625;



}