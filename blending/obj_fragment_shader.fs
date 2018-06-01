#version 330 core
out vec4 color;

in vec2 TexCoords;

uniform sampler2D texture0;

void main()
{
    vec4 texColor = texture(texture0, TexCoords);
    if(texColor.a < 0.1)
        discard;
    color = texColor;
}
