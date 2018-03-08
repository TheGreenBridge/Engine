#version 330 core

layout (location = 0) in vec3 vPosition;

uniform mat4 view_matrix = mat4(1.0);
uniform mat4 pr_matrix = mat4(1.0);

void main(){
	
	gl_Position = pr_matrix * view_matrix * vec4(vPosition, 1.0);
}