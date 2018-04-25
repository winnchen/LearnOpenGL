#version 330 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular; 
    float shininess;
};

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 Pos;
in vec3 Normal;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    //ambient
    vec3 ambient = light.ambient * material.ambient;
    
    //diffuse
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(light.position - Pos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    //specular
    vec3 viewDir = normalize(viewPos - Pos);
    vec3 reflectDir = reflect(-lightDir, normal); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);
    color = vec4(ambient + diffuse + specular, 1.0);
}
