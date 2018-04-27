#version 330 core

struct Material
{
    sampler2D diffuse;
    sampler2D specular; 
    float shininess;
};

struct DirectionLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};


struct SpotLight
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

#define NUM_OF_POINT_LIGHT 4
uniform vec3 viewPos;
uniform Material material;
uniform DirectionLight directionLight;
uniform PointLight pointLight[NUM_OF_POINT_LIGHT];
uniform SpotLight spotLight;

vec3 calculateDirectionLight(DirectionLight directionLight, vec3 normal, vec3 viewDir);
vec3 calculatePointLight(PointLight pointLight, vec3 normal, vec3 viewDir, vec3 viewPos);
vec3 calculateSpotLight(SpotLight spotLight, vec3 normal, vec3 viewDir, vec3 viewPos);


void main()
{
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - Pos);

    vec3 result;
    result = calculateDirectionLight(directionLight, normal, viewDir);

    for (int i = 0; i < NUM_OF_POINT_LIGHT; i++)
    {
        result += calculatePointLight(pointLight[i], normal, viewDir, viewPos);
    }

    result += calculateSpotLight(spotLight, normal, viewDir, viewPos);
    color = vec4(result, 1.0);
}


vec3 calculateDirectionLight(DirectionLight directionLight, vec3 normal, vec3 viewDir)
{
    //ambient
    vec3 ambient = directionLight.ambient * vec3(texture(material.diffuse, TexCoords));
    
    //diffuse
    vec3 directionLightDir = normalize(-directionLight.direction);
    float diff = max(dot(normal, directionLightDir), 0.0);
    vec3 diffuse = directionLight.diffuse * diff * (vec3(texture(material.diffuse, TexCoords)));

    //specular
    vec3 reflectDir = reflect(-directionLightDir, normal); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = directionLight.specular * spec * (vec3(texture(material.specular, TexCoords)));
    
    return ambient + diffuse + specular;
}

vec3 calculatePointLight(PointLight pointLight, vec3 normal, vec3 viewDir, vec3 viewPos)
{
    //ambient
    vec3 ambient = pointLight.ambient * vec3(texture(material.diffuse, TexCoords));
    
    //diffuse
    vec3 pointLightDir = normalize(pointLight.position - Pos);
    float diff = max(dot(normal, pointLightDir), 0.0);
    vec3 diffuse = pointLight.diffuse * diff * (vec3(texture(material.diffuse, TexCoords)));

    //specular
    vec3 reflectDir = reflect(-pointLightDir, normal); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = pointLight.specular * spec * (vec3(texture(material.specular, TexCoords)));

    //attenuation
    float distance = length(pointLight.position - Pos);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * distance * distance);

    return ambient + diffuse + specular;
}

vec3 calculateSpotLight(SpotLight spotLight, vec3 normal, vec3 viewDir, vec3 viewPos)
{
    //soft edge
    vec3 spotLightDir = normalize(spotLight.position - Pos);
    float theta = dot(spotLightDir, -spotLight.direction);
    float epsilon = spotLight.cutoff - spotLight.outerCutoff;
    float intensity = clamp(((theta - spotLight.outerCutoff) / epsilon), 0.0, 1.0);

    //ambient
    vec3 ambient = spotLight.ambient * vec3(texture(material.diffuse, TexCoords));

    //diffuse
    float diff = max(dot(normal, spotLightDir), 0.0);
    vec3 diffuse = spotLight.diffuse * diff * (vec3(texture(material.diffuse, TexCoords)));
    diffuse *= intensity;

    //specular
    vec3 reflectDir = reflect(-spotLightDir, normal); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spotLight.specular * spec * (vec3(texture(material.specular, TexCoords)));
    specular *= intensity;

    //attenuation
    float distance = length(spotLight.position - Pos);
    float attenuation = 1.0 / (spotLight.constant + spotLight.linear * distance + spotLight.quadratic * distance * distance);
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}
