#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;

uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 view_matrix = mat4(1.0);
uniform mat4 transformation_matrix = mat4(1.0);
uniform vec3 lightPosition;

out vec2 TexCoord;
out vec3 SurfaceNormal;
out vec3 ToLightVector;
out vec3 FragPos;

//out vec3 Normal;
//out vec3 Position;

void main(){
	vec4 worldPosition = transformation_matrix * vec4(vPosition, 1.0);
	vec4 positionRelativeToCam = view_matrix * worldPosition;

	gl_Position = pr_matrix * positionRelativeToCam;

	ToLightVector = lightPosition - worldPosition.xyz;
	SurfaceNormal = (transformation_matrix * vec4(vNormal, 0.0)).xyz;
	TexCoord = vTexCoord;
	FragPos = Vec3(view_matrix * transformation_matrix * vec4(vPosition, 1.0f));	
	
	//Normal = mat3(transpose(inverse(transformation_matrix)) * vNormal;
	//Position = Vec3(transformation_matrix * vec4(vPosition, 1.0f));
}
