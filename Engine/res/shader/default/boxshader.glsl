#VERTEX_SHADER
#version 330 core

layout (location = 0) in vec3 position;
out vec3 TexCoords;

uniform mat4 projection = mat4(1.0);
uniform mat4 view = mat4(1.0);

void main()
{
    gl_Position =   projection * view * vec4(position, 1.0);  
    TexCoords = position;
} 

#FRAGMENT_SHADER
#version 330 core

in vec3 TexCoords;
out vec4 color;

uniform samplerCube cubemap;

void main(){
	color = texture(cubemap, TexCoords);
} 