#VERTEX_SHADER
#version 330 core

layout(location = 0) in vec2 position;

void main(){
	gl_Position = vec4(position, 0.0, 1.0);
}

#FRAGMENT_SHADER
#version 330 core

out vec4 fragColor;

vec4 color = vec4(1.0, 0.0, 0.0, 1.0);

void main(){
	fragColor = color;
}
