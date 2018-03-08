#version 330 core

in vec2 pass_uv;
in vec3 SurfaceNormal;
in vec3 ToLightVector;


out vec4 fragColor;

vec3 unitNormal = normalize(SurfaceNormal);
vec3 unitLightVector = normalize(ToLightVector);

void main(){
	vec4 baseColor = vec4(0.0, 0.0, 1.0, 1.0);
	vec3 lightColour = vec3(1.0, 1.0, 1.0);
	

	// Diffuse
	float nDotl = dot(unitNormal, unitLightVector);
    float brightness = max(nDotl, 0.0);
    vec3 totalDiffuse = max(brightness * lightColour, 0.2);
    
	vec4 diffuse = vec4(totalDiffuse, 1.0) * baseColor ;

	fragColor = diffuse;

}