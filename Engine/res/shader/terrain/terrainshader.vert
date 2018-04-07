#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 view_matrix = mat4(1.0);

out vec3 pos;

void main()
{
	gl_Position = pr_matrix * view_matrix * vec4(position, 1.0);	
	pos = position;
}