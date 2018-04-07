#version 330 core

in vec3 SurfaceNormal;
in vec3 ToLightVector;
in vec3 FragPos;

//in vec3 Normal;
//in vec3 Position;

out vec4 fragColor;

//uniform Light light;
uniform vec3 viewPos;
uniform sampler2D modelTexture;

vec3 lightColour = vec3(1.0, 1.0, 1.0);
vec3 unitNormal = normalize(SurfaceNormal);
vec3 unitLightVector = normalize(ToLightVector);

void main(){
	
	// Diffuse
	float nDotl = dot(unitNormal, unitLightVector);
    float brightness = max(nDotl, 0.0);
    vec3 totalDiffuse = max(brightness * lightColour, 0.2);
    vec4 textureColour = vec4(1,0,0,1);
	vec4 diffuse = vec4(totalDiffuse, 1.0) * textureColour;
	
	// Specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(FragPos-viewPos); // The viewer is at (0,0,0) so viewDir is (0,0,0) - Position => -Position
    vec3 reflectDir = reflect(-unitLightVector, unitNormal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec4 specular = vec4(specularStrength * spec * lightColour, 1.0); 
	
	fragColor = diffuse + specular;
	//vec3 I = normalize(Position - cameraPos);
    //vec3 R = reflect(I, normalize(Normal));
    //vec4 reflection = vec4(texture(skybox, R), 1.0);
	
	//fragColor = mix(reflection,phong,0.5);
}