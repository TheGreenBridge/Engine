#VERTEX_SHADER
#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec3 vUV;

uniform mat4 proj_matrix = mat4(1.0);
uniform mat4 view_matrix = mat4(1.0);
uniform mat4 model_matrix = mat4(1.0);

void main()
{
	gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
}

#FRAGMENT_SHADER
#version 330 core

void main()
{
	gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}