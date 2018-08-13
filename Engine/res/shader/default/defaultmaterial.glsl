#VERTEX_SHADER
#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;

//layout (std140) uniform vs_uniforms
//{
//	mat4 pr_matrix;
//	mat4 view_matrix;
//	mat4 transformation_matrix;	
//};

uniform mat4 pr_matrix = mat4(1.0);
uniform	mat4 view_matrix = mat4(1.0);
uniform mat4 transformation_matrix = mat4(1.0);	

vec3 lightPosition = vec3(3.0, 3.0, 0.0);

out VS_OUT
{
	vec2 TexCoord;
	vec3 SurfaceNormal;
	vec3 ToLightVector;
	vec3 FragPos;
} vs_out;

//out	vec2 TexCoord;
//out	vec3 SurfaceNormal;
//out	vec3 ToLightVector;
//out	vec3 FragPos;

void main(){
	vec4 worldPosition = transformation_matrix * vec4(vPosition, 1.0);
	vec4 positionRelativeToCam = view_matrix * worldPosition;

	gl_Position = pr_matrix * positionRelativeToCam;

	// output
	vs_out.ToLightVector = lightPosition - worldPosition.xyz;
	vs_out.SurfaceNormal = (transformation_matrix * vec4(vNormal, 0.0)).xyz;
	vs_out.TexCoord = vTexCoord;
	vs_out.FragPos = vec3(view_matrix * transformation_matrix * vec4(vPosition, 1.0f));	
	
	//Normal = mat3(transpose(inverse(transformation_matrix)) * vNormal;
	//Position = vec3(transformation_matrix * vec4(vPosition, 1.0f));
}

#FRAGMENT_SHADER
#version 330 core


in VS_OUT
{
	vec2 TexCoord;
	vec3 SurfaceNormal;
	vec3 ToLightVector;
	vec3 FragPos;
} fs_in;


in vec2 TexCoord;
in vec3 SurfaceNormal;
in vec3 ToLightVector;
in vec3 FragPos;

out vec4 fragColor;

//uniform sampler2D modelTexture;
uniform vec3 viewPos;


//layout (std140) uniform fs_uniforms
//{
//	vec3 viewPos;
//};



vec3 lightColour = vec3(1.0, 1.0, 1.0);
vec3 unitNormal = normalize(fs_in.SurfaceNormal);
vec3 unitLightVector = normalize(fs_in.ToLightVector);

void main(){
	
	// Diffuse
	float nDotl = dot(unitNormal, unitLightVector);
    float brightness = max(nDotl, 0.0);
	if(brightness < 0.5) 
	{
		brightness = 0.5;
	}
	else 
	{
		brightness = 1.0;
	}

    vec3 totalDiffuse = max(brightness * lightColour, 0.2);
    vec4 textureColour = vec4(1,0,0,1);
	vec4 diffuse = vec4(totalDiffuse, 1.0) * textureColour;
	
	// Specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(fs_in.FragPos-viewPos); // The viewer is at (0,0,0) so viewDir is (0,0,0) - Position => -Position
    vec3 reflectDir = reflect(-unitLightVector, unitNormal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

	if(spec < 0.5)
	{
		spec = 0.5;
	}
	else
	{
		spec = 1.0;
	}

    vec4 specular = vec4(specularStrength * spec * lightColour, 1.0); 
	
	fragColor = diffuse + specular;

	//fragColor = vec4(1.0, 1.0, 1.0, 1.0);

	//vec3 I = normalize(Position - cameraPos);
    //vec3 R = reflect(I, normalize(Normal));
    //vec4 reflection = vec4(texture(skybox, R), 1.0);
	
	//fragColor = mix(reflection,phong,0.5);
}