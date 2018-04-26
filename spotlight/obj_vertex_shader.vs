#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 Pos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(pos, 1.0);
    Pos = vec3(model * vec4(pos, 1.0)); //vertex pos in world space
    Normal = mat3(transpose(inverse(model))) * normal;
    TexCoords = texCoords;
}
