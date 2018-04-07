#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 view_matrix = mat4(1.0);
uniform mat4 transformation_matrix = mat4(1.0);

void main(){
	vec4 worldPosition = transformation_matrix * vec4(position, 1.0);
	vec4 positionRelativeToCam = view_matrix * worldPosition;

	gl_Position = pr_matrix * positionRelativeToCam;
	
}
