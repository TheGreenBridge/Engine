#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;


out vec3 pass_reflection;
out vec3 pass_position;

uniform mat4 trans_matrix;
uniform mat4 proj_matrix;
uniform mat4 view_matrix;

uniform vec3 camera_position;


void main(){
	
	vec4 worldPosition = trans_matrix * vec4(aPosition, 1.0);
	
	pass_position = worldPosition.xyz;
	
	gl_Position = proj_matrix * view_matrix  * worldPosition;
	
	//vec4 normal = view_matrix * trans_matrix * vec4(aNormal, 1.0);
	vec4 normal = trans_matrix * vec4(aNormal, 1.0);
	vec3 position = vec3(trans_matrix * vec4(aPosition, 1.0));
	vec3 I = normalize(worldPosition.xyz - (-camera_position));

	pass_reflection = reflect(I, normalize(normal.xyz));

}
