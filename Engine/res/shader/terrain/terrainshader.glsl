#VERTEX_SHADER
#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;


layout (std140) uniform vs_uniforms
{
	mat4 view_matrix;
	mat4 transformation_matrix;
	vec3 lightPosition;	
};

out VS_OUT
{
	vec3 Pos;
	vec3 SurfaceNormal;
	vec3 LightPos;
} vs_out;

void main()
{
	vec4 worldPosition = transformation_matrix * vec4(vPosition, 1.0);
	gl_Position = view_matrix * worldPosition;	

	vs_out.LightPos = lightPosition;
	vs_out.Pos = worldPosition.xyz;
	vs_out.SurfaceNormal = (transformation_matrix * vec4(vNormal, 0.0)).xyz;
}

#FRAGMENT_SHADER
#version 330 core

in VS_OUT
{
	vec3 Pos;
	vec3 SurfaceNormal;
	vec3 LightPos;
} fs_int;

out vec4 fragColor;

vec3 color = vec3(1.0, 1.0, 1.0);

void main(){
	float intensity = 1.0 / length(fs_int.LightPos - fs_int.Pos) * 10;
	fragColor = vec4(color * intensity, 1.0);
}
