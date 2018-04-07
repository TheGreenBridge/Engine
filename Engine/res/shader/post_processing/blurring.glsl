#VERTEX_SHADER
#version 330 core

uniform sampler2D tex0;
uniform sampler2D tex1;

void main()
{
    vec4 t0 = texture2D(tex0, gl_TexCoord[0].st);
    vec4 t1 = texture2D(tex1, gl_TexCoord[0].st);
    gl_FragColor = (1.0 - t1.a) * t0 + t1.a * t1;
}

#FRAGMENT_SHADER
#version 330 core
uniform sampler2D tex0;
uniform sampler2D tex1;

void main()
{
    vec4 t0 = texture2D(tex0, gl_TexCoord[0].st);
    vec4 t1 = texture2D(tex1, gl_TexCoord[0].st);
    gl_FragColor = mix(t0, t1, t1.a);
}