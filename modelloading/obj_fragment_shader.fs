#version 330 core

struct Light
{
    vec3 position;
    vec3 direction;
    float cutoff;
    float outerCutoff;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

in vec3 Pos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPos;
uniform Light light;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main()
{
    //soft edge
    vec3 lightDir = normalize(light.position - Pos);
    float theta = dot(lightDir, -light.direction);
    float epsilon = light.cutoff - light.outerCutoff;
    float intensity = clamp(((theta - light.outerCutoff) / epsilon), 0.0, 1.0);

    //ambient
    vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoords));

    //diffuse
    vec3 normal = normalize(Normal);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * (vec3(texture(texture_diffuse1, TexCoords)));
    diffuse *= intensity;

    //specular
    vec3 viewDir = normalize(viewPos - Pos);
    vec3 reflectDir = reflect(-lightDir, normal); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 0.5);
    vec3 specular = light.specular * spec * (vec3(texture(texture_specular1, TexCoords)));
    specular *= intensity;

    //attenuation
    float distance = length(light.position - Pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    color = vec4((ambient + diffuse + specular), 1.0);
}
