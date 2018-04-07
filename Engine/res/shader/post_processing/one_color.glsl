#VERTEX_SHADER
#version 330 core

layout (location = 0) in vec3 vPosition;

uniform mat4 proj_matrix = mat4(1.0);
uniform mat4 view_matrix = mat4(1.0);
uniform mat4 model_matrix = mat4(1.0);

void main()
{
	vec4 worldPosition = model_matrix * vec4(vPosition, 1.0);
	vec4 positionRelativeToCam = view_matrix * worldPosition;
	gl_Position = proj_matrix * positionRelativeToCam;
}

#FRAGMENT_SHADER
#version 330 core

void main()
{
	gl_FragColor = vec4(1.0, 0.53, 0.0, 1.0);
}