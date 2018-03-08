#version 330 core

in vec3 pos;

out vec4 fragColor;

vec4 color = vec4(0.0, 1.0, 0.0, 1.0);
vec3 light = vec3(10, 0, 10);

void main(){
	float intensity = 1.0 / length(light - pos) * 10;
	fragColor = color * intensity;
}