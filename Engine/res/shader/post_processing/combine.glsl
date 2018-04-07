#VERTEX_SHADER
#version 330 core

layout (location = 0) in vec2 vPosition;

out vec2 texCoord;

void main()
{	
	texCoord = vPosition * 0.5 + 0.5;
	gl_Position = vec4(vPosition, 0.0, 1.0);
}

#FRAGMENT_SHADER
#version 330 core

in vec2 texCoord;

uniform sampler2D baseMap;
uniform sampler2D overlayMap;

void main()
{
    vec4 t0 = texture2D(baseMap, texCoord);
    vec4 t1 = texture2D(overlayMap, texCoord);
    gl_FragColor = mix(t0, t1, t1.a);
}