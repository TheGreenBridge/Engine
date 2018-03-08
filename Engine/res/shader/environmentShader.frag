#version 330 core

in vec3 pass_reflection;
in vec3 pass_position;
//in vec3 Position;

out vec4 FragColor;

uniform samplerCube environment;


void main(){

	//if(pass_position.y < 3.0) {
	//	discard;
	//}
	FragColor = mix(vec4(texture(environment, pass_reflection).rgb, 1.0), vec4(0.0 , 0.5, 0.0, 1.0), 0.0);

}
